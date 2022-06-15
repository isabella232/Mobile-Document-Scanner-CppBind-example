#include "document_scanner/document_scanner_lib/document_scanner_cv.cpp"

int main(int argc, char *argv[]) {
    // Initialise image variable
    cv::Mat image;
    // Get image path from the command line arguments or use the default image
    std::string image_path = argc >= 2 ? argv[1] : "data/img/paper.jpeg";
    // Get output dir from the command line arguments or use the default dir
    std::string out_dir = argc >= 3 ? argv[2] : "/tmp";
    // Read image from the given path
    image = cv::imread(image_path);
    // Create document corner points extractor object
    auto docCornersExtractor = DocCornerPointsExtractor();
    // Set image
    docCornersExtractor.setImage(image);
    // Compute corner points
    docCornersExtractor.computeCornerPoints();
    // Create document extractor object
    auto docExtractor = DocExtractor(docCornersExtractor.image(), docCornersExtractor.points());
    // Draw contour points on document
    auto imageWithCornerPoints = docExtractor.drawPoints(255, 0, 0);
    // Do image warp on the extracted image
    cv::Mat imgWarp = docExtractor.warp();
    // Save contour points image
    imwrite(out_dir + "/cornerPoints.jpeg", imageWithCornerPoints);
    // Save final cropped image
    imwrite(out_dir + "/croppedDoc.jpeg", imgWarp);
    return 0;
}
