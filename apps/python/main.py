import os
import sys

from cv.imgcodecs import imread
from doc_scanner import DocCornerPointsExtractor, DocExtractor, save_image
import logging


def scan():
    # Get image path from the command line arguments or use the default image
    image_path = sys.argv[1] if len(sys.argv) >= 2 else 'data/img/paper.jpeg'
    # Get output dir from the command line arguments or use the default dir
    out_dir = sys.argv[2] if len(sys.argv) >= 3 else '/tmp'
    # Read image from the given path
    image = imread(image_path)
    # Create document corner points extractor object
    doc_corners_extractor = DocCornerPointsExtractor()
    # Set image
    doc_corners_extractor.image = image
    try:
        # Compute corner points
        doc_corners_extractor.compute_corner_points()
    except ValueError as error:
        logging.error("Invalid corner points detected, please try a different image!")
    else:
        # Create document extractor object
        docExtractor = DocExtractor(doc_corners_extractor.image, doc_corners_extractor.points)
        # Draw contour points on document
        corner_points = docExtractor.draw_points(255, 0, 0)
        # Do image warp on the extracted image
        img_warp = docExtractor.warp()
        # Save contour points image
        save_image(os.path.join(out_dir, "cornerPoints.jpeg"), corner_points)
        # Save final cropped image
        save_image(os.path.join(out_dir, "croppedDoc.jpeg"), img_warp)


if __name__ == '__main__':
    scan()
