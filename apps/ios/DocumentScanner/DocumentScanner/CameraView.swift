//
//  CameraView.swift
//  DocumentScanner
//
//  Created by Vahagn Sirunyan on 24.05.2022.
//

import Foundation
import SwiftUI
import DocumentScannerFramework

class ImagePickerCoordinator : NSObject, UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    
    @Binding var isShown: Bool
    @Binding var documentImage: Image?
    @Binding var cornerPointsImage: Image?
    
    init(isShown: Binding<Bool>, documentImage: Binding<Image?>, cornerPointsImage: Binding<Image?>) {
        _isShown = isShown
        _documentImage = documentImage
        _cornerPointsImage = cornerPointsImage
    }
    
    func imagePickerControllerDidCancel(_ picker: UIImagePickerController) {
        print("Cancel pressed")
        isShown = false
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        if let _originalImage = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            let imageUtilsObject: ImageUtils = ImageUtils()
            if imageUtilsObject.saveImage(image: _originalImage, jpgFileName: imageUtilsObject.unhandledPhotoJpgName) {
                let directory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
                let image = imread(filename: directory.appendingPathComponent(imageUtilsObject.unhandledPhotoJpgName).path)
                let docCornersExtractor = DocCornerPointsExtractor()
                docCornersExtractor.image = image
                do {
                    try docCornersExtractor.computeCornerPoints()
                } catch is StdRangeError {
                    // Invalid corner points detected, skipping
                    // processing and showing the original image
                    documentImage = Image(uiImage: _originalImage)
                    cornerPointsImage = nil
                    isShown = false
                    return
                } catch{}
                let docExtractor = DocExtractor(image: docCornersExtractor.image, docCornerPoints: docCornersExtractor.points)
                let drawCornerPoints = docExtractor.drawPoints(R: 255, G: 0, B: 0)
                let imgWarp = docExtractor.warp()
                if saveImage(filename: directory.appendingPathComponent(imageUtilsObject.croppedDocumentJpgName).path, img: imgWarp), saveImage(filename: directory.appendingPathComponent(imageUtilsObject.cornerPointsJpgName).path, img: drawCornerPoints), let docImage = imageUtilsObject.loadSavedImage(named: imageUtilsObject.croppedDocumentJpgName), let cornerPoints = imageUtilsObject.loadSavedImage(named: imageUtilsObject.cornerPointsJpgName) {
                    documentImage = Image(uiImage: docImage)
                    cornerPointsImage = Image(uiImage: cornerPoints)
                } else {
                    print("failed to load final image")
                }
            }
            else {
                print("failed to save intermediate image")
            }
            isShown = false
        }
    }
}

struct CameraView: UIViewControllerRepresentable {
    
    typealias UIViewControllerType = UIImagePickerController
    
    @Binding var isShown: Bool
    @Binding var documentImage: Image?
    @Binding var cornerPointsImage: Image?
    
    func makeUIViewController(context: Context) -> UIViewControllerType {
        let viewController = UIViewControllerType()
        viewController.delegate = context.coordinator
        viewController.sourceType = .camera
        return viewController
    }
    
    func updateUIViewController(_ uiViewController: UIViewControllerType, context: Context) {
        
    }
    
    func makeCoordinator() -> ImagePickerCoordinator {
        return Coordinator(isShown: $isShown, documentImage: $documentImage, cornerPointsImage: $cornerPointsImage)
    }
}
