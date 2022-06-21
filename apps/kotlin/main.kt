package doc_scanner
import cppbind.exception_helpers.StdRangeError
import cv.*

class DocumentScannerApp {

    companion object {

        init {
            System.loadLibrary("document_scanner")
        }

        @JvmStatic
        fun main(args: Array<String>) {
            // Get image path from the command line arguments or use the default image
            val imagePath = args.getOrElse(0) { "data/img/paper.jpeg" }
            // Get output dir from the command line arguments or use the default dir
            val outDir = args.getOrElse(1) { "/tmp" }
            // Read image from the given path
            val image = imread(imagePath)
            // Create document corner points extractor object
            val docCornersExtractor = DocCornerPointsExtractor()
            // Set image
            docCornersExtractor.image = image
            try{
                // Compute corner points
                docCornersExtractor.computeCornerPoints()
            } catch(e: StdRangeError){
                println("Invalid corner points detected, please try a different image!")
                return
            }
            // Create document extractor object
            val docExtractor = DocExtractor(docCornersExtractor.image, docCornersExtractor.points)
            // Draw contour points on document
            val cornerPoints = docExtractor.drawPoints(255, 0, 0)
            // Do image warp on the extracted image
            val imgWarp = docExtractor.warp()
            // Save contour points image
            saveImage(outDir + "/cornerPoints.jpeg", cornerPoints)
            // Save final cropped document image
            saveImage(outDir + "/croppedDoc.jpeg", imgWarp)
        }
    }
}
