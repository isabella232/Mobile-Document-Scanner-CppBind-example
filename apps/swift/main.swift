//
//  main.swift
//  DocumentScanner
//
//  Created by liana.karapetyan on 26.04.22.
//

import DocumentScanner
import cppbind.exception_helpers.StdRangeError


@main
class HelloUser {

    static func main() {

        let args = CommandLine.arguments
        // Get image path from the command line arguments or use the default image
        let imagePath = args.count >= 2 ? args[1] : "data/img/paper.jpeg"
        // Get output dir from the command line arguments or use the default dir
        let outDir = args.count >= 3 ? args[2] : "/tmp"
        // Read image from the given path
        let image = imread(filename: imagePath)
        // Create document corner points extractor object
        let docCornersExtractor = DocCornerPointsExtractor()
        // Set image
        docCornersExtractor.image = image
        do {
            try docCornersExtractor.computeCornerPoints();
        } catch is StdRangeError {
            println("Invalid corner points detected, please try a different image!")
            return
        } catch {}
        // Create document extractor object
        let docExtractor = DocExtractor(image: docCornersExtractor.image, docCornerPoints: docCornersExtractor.points)
        // Draw contour points on document
        let drawCornerPoints = docExtractor.drawPoints(R: 255, G: 0, B: 0)
        // Do image warp on the extracted image
        let imgWarp = docExtractor.warp()
        // Save contour points image
        saveImage(filename: outDir + "/cornerPoints.jpeg", img: drawCornerPoints)
        // Save final cropped image
        saveImage(filename: outDir + "/croppedDoc.jpeg", img: imgWarp)

    }
}

