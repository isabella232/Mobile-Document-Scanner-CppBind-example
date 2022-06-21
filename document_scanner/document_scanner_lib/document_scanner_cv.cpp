#include <opencv2/opencv.hpp>
#include <iostream>


/**
 * Document Corner Points Extractor Class.
 * __API__
 * action: gen_class
 * package: doc_scanner
 */
class DocCornerPointsExtractor {

    public:
    /**
    * __API__
    * action: gen_constructor
    * throws: no_throw
    */
    DocCornerPointsExtractor() {};

    /**
    * __API__
    * action: gen_constructor
    * throws: no_throw
    */
    DocCornerPointsExtractor(cv::Mat image) :
        _image(image) {};

    /**
    * __API__
    * action: gen_setter
    * throws: no_throw
    */
    void setImage(cv::Mat image) {
        _image = image;
        _docCornerPoints.clear();
    }

    /**
    * __API__
    * action: gen_getter
    * throws: no_throw
    */
    cv::Mat image() {
        return _image;
    }

    /**
    * __API__
    * action: gen_method
    * throws: std::range_error
    */
    void computeCornerPoints() {

        // detect edges

        cv::Mat imgGray, imgBlur, imgCanny, imgDil;
        cv::cvtColor(_image, imgGray, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(imgGray, imgBlur, cv::Size(3, 3), 3, 0);
        cv::Canny(imgBlur, imgCanny, 25, 75);
        cv::Mat kernel = getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::dilate(imgCanny, imgDil, kernel);
        // get contours

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        findContours(imgDil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        std::vector<std::vector<cv::Point>> conPoly(contours.size());
        std::vector<cv::Rect> boundRect(contours.size());

        std::vector<cv::Point> initialPoints;
        int maxArea=0;

        for (int i = 0; i < contours.size(); i++)
        {
            int area = contourArea(contours[i]);

            std::string objectType;

            if (area > 1000)
            {
                float peri = arcLength(contours[i], true);
                approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

                if (area > maxArea && conPoly[i].size()==4 ) {
                    initialPoints = { conPoly[i][0],conPoly[i][1] ,conPoly[i][2] ,conPoly[i][3] };
                    maxArea = area;
                }
            }
        }

        if(initialPoints.size() != corner_points){
            throw std::range_error("Invalid corner points detected!");
        }

        // reorder

        std::vector<cv::Point> finalPoints;
        std::vector<int>  sumPoints, subPoints;

        for (int i = 0; i < corner_points; i++)
        {
            sumPoints.push_back(initialPoints[i].x + initialPoints[i].y);
            subPoints.push_back(initialPoints[i].x - initialPoints[i].y);
        }

        finalPoints.push_back(initialPoints[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // 0
        finalPoints.push_back(initialPoints[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //1
        finalPoints.push_back(initialPoints[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); //2
        finalPoints.push_back(initialPoints[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); //3

        _docCornerPoints = finalPoints;

    }

    /**
    * __API__
    * action: gen_getter
    * throws: no_throw
    */
    std::vector<cv::Point> points() {
        return _docCornerPoints;
    }

    private:
        cv::Mat _image;
        std::vector<cv::Point> _docCornerPoints;
        int corner_points = 4;

};


/**
 * Document Extractor Class.
 * __API__
 * action: gen_class
 * package: doc_scanner
 */
class DocExtractor {

    public:
    /**
    * __API__
    * action: gen_constructor
    * throws: no_throw
    */
    DocExtractor(const cv::Mat& image, std::vector<cv::Point> docCornerPoints, float w=420, float h=596, int margin=5)
            : _image(image),
              _docCornerPoints(std::move(docCornerPoints)),
              _margin(margin),
              _w(w),
              _h(h) {};

    /**
    * __API__
    * action: gen_setter
    * throws: no_throw
    */
    void setImage(cv::Mat image) {
        _image = image;
        _docCornerPoints.clear();
    }

    /**
    * __API__
    * action: gen_getter
    * throws: no_throw
    */
    cv::Mat image() {
        return _image;
    }

    /**
    * __API__
    * action: gen_method
    * throws: no_throw
    */
    cv::Mat warp() {
        cv::Mat imgWarp, imgCrop;
        cv::Point2f src[4] = { _docCornerPoints[0],_docCornerPoints[1],_docCornerPoints[2],_docCornerPoints[3] };
        cv::Point2f dst[4] = { {0.0f,0.0f},{_w,0.0f},{0.0f,_h},{_w,_h} };

        cv::Mat matrix = getPerspectiveTransform(src, dst);
        warpPerspective(_image, imgWarp, matrix, cv::Point(_w, _h));

        cv::Rect roi(_margin, _margin, _w - (2 * _margin), _h - (2 * _margin));
        imgCrop = imgWarp(roi);

        return imgCrop;
    }

    /**
    * __API__
    * action: gen_method
    * throws: no_throw
    */
    cv::Mat drawPoints(int R, int G, int B) {
        cv::Mat _image_copy = _image.clone();
        for (int i = 0; i < _docCornerPoints.size(); i++)
        {
            circle(_image_copy, _docCornerPoints[i], 10, cv::Scalar(B,G,R), cv::FILLED);
            putText(_image_copy, std::to_string(i), _docCornerPoints[i], cv::FONT_HERSHEY_PLAIN, 4, cv::Scalar(B,G,R), 4);
        }
        return _image_copy;
    }

    private:
        cv::Mat _image;
        std::vector<cv::Point> _docCornerPoints;
        int _margin;
        float _w;
        float _h;

};


/**
 * __API__
 * action: gen_function
 * package: doc_scanner
 * throws: no_throw
 */
bool saveImage(const std::string& filename, const cv::Mat& img) {
    return cv::imwrite(filename, img);
}
