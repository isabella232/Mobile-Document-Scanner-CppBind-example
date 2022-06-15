//
//  ImageUtils.swift
//  DocumentScanner
//
//  Created by Vahagn Sirunyan on 01.06.2022.
//

import Foundation
import UIKit

struct ImageUtils {
    let unhandledPhotoJpgName = "tmp.jpg"
    let croppedDocumentJpgName = "croppedDoc.jpg"
    let cornerPointsJpgName = "cornerPoints.jpg"

    func saveImage(image: UIImage, jpgFileName: String) -> Bool {
        guard let data = image.jpegData(compressionQuality: 1.0) else {
            return false
        }
        let directory = FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)[0]
        do {
            try data.write(to: directory.appendingPathComponent(jpgFileName))
            print("image saved to")
            print(directory)
            return true
        } catch {
            print(error.localizedDescription)
            return false
        }
    }

    func loadSavedImage(named: String) -> UIImage? {
        if let dir = try? FileManager.default.url(for: .documentDirectory, in: .userDomainMask, appropriateFor: nil, create: false) {
            return UIImage(contentsOfFile: URL(fileURLWithPath: dir.absoluteString).appendingPathComponent(named).path)
        }
        return nil
    }
}
