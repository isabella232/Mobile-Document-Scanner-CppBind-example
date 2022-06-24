/**
 *   ______ .______   .______   .______    __  .__   __.  _______  
 *  /      ||   _  \  |   _  \  |   _  \  |  | |  \ |  | |       \ 
 * |  ,----'|  |_)  | |  |_)  | |  |_)  | |  | |   \|  | |  .--.  |
 * |  |     |   ___/  |   ___/  |   _  <  |  | |  . `  | |  |  |  |
 * |  `----.|  |      |  |      |  |_)  | |  | |  |\   | |  '--'  |
 *  \______|| _|      | _|      |______/  |__| |__| \__| |_______/ 
 * 
 * This file is generated by cppbind on 06/21/2022-09:31.
 * Please do not change it manually.
 */

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cxxabi.h>
#include <memory>
#include <type_traits>
#include "document_scanner/api/ios/DocumentScannerFramework/DocumentScannerFramework/Cpp/doc_scanner/c_document_scanner_cv.h"
#include "document_scanner/document_scanner_lib/document_scanner_cv.cpp"

extern const char* CPPBIND_STD_STDEXCEPTION;
extern const char* CPPBIND_CV_MAT;
extern const char* CPPBIND_STD_STDRANGEERROR;
extern const char* CPPBIND_CV_POINTINT;

const char* CPPBIND_DOCCORNERPOINTSEXTRACTOR = "DocCornerPointsExtractor";
const char* CPPBIND_DOCEXTRACTOR = "DocExtractor";


void release_DocCornerPointsExtractor(CppBindCObject cself, bool owner) {
    if (owner) {
        delete static_cast<DocCornerPointsExtractor*>(cself.ptr);
    }
    free(cself.type);
}

CppBindCObject create_DocCornerPointsExtractor(CppBindCObject* _Nonnull cppbind_err) {
    try {
        auto this_object = new DocCornerPointsExtractor();
        return {strdup(CPPBIND_DOCCORNERPOINTSEXTRACTOR), this_object};
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

CppBindCObject create_DocCornerPointsExtractor_1(CppBindCObject image, CppBindCObject* _Nonnull cppbind_err) {
    
    auto& ctocxximage = *static_cast<cv::Mat*>(image.ptr);
    try {
        auto this_object = new DocCornerPointsExtractor(ctocxximage);
        return {strdup(CPPBIND_DOCCORNERPOINTSEXTRACTOR), this_object};
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

CppBindCObject _prop_get_DocCornerPointsExtractor_image(CppBindCObject cself, CppBindCObject* _Nonnull cppbind_err) {
    auto ctocxxcself = static_cast<DocCornerPointsExtractor*>(cself.ptr);
    try {
        const auto& result = ctocxxcself->image();
        
        char* type_result = strdup(CPPBIND_CV_MAT);
        auto value_ptr_result = const_cast<cv::Mat*>(new cv::Mat(result));
        CppBindCObject cxxtocresult = {type_result, value_ptr_result};
        return cxxtocresult;
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

void _prop_set_DocCornerPointsExtractor_image(CppBindCObject cself, CppBindCObject image, CppBindCObject* _Nonnull cppbind_err) {
    
    auto ctocxxcself = static_cast<DocCornerPointsExtractor*>(cself.ptr);
    
    auto& ctocxximage = *static_cast<cv::Mat*>(image.ptr);
    try {
        ctocxxcself->setImage(ctocxximage);
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
}

void _func_DocCornerPointsExtractor_computeCornerPoints(CppBindCObject cself, CppBindCObject* _Nonnull cppbind_err) {
    auto ctocxxcself = static_cast<DocCornerPointsExtractor*>(cself.ptr);
    try {
        ctocxxcself->computeCornerPoints();
    } catch (const std::range_error& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDRANGEERROR);
        cppbind_err->ptr = new std::range_error(e);
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
}

CppBindCDataArray _prop_get_DocCornerPointsExtractor_points(CppBindCObject cself, CppBindCObject* _Nonnull cppbind_err) {
    auto ctocxxcself = static_cast<DocCornerPointsExtractor*>(cself.ptr);
    try {
        const auto& result = ctocxxcself->points();
        auto _data_cxxtocresult = new CppBindCObject [result.size()];
        CppBindCDataArray cxxtocresult = { _data_cxxtocresult, static_cast<long long>(result.size()) };
        for (int _i_result = 0; _i_result < result.size(); ++_i_result) {
            auto& value_result = result[_i_result];
            
            char* type_value_result = strdup(CPPBIND_CV_POINTINT);
            auto value_ptr_value_result = const_cast<cv::Point*>(new cv::Point(value_result));
            CppBindCObject cxxtocvalue_result = {type_value_result, value_ptr_value_result};
            _data_cxxtocresult[_i_result] = cxxtocvalue_result;
        }
        return cxxtocresult;
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCDataArray result {};
    return result;
}

void release_DocExtractor(CppBindCObject cself, bool owner) {
    if (owner) {
        delete static_cast<DocExtractor*>(cself.ptr);
    }
    free(cself.type);
}

CppBindCObject create_DocExtractor(CppBindCObject image, CppBindCDataArray doc_corner_points, float w, float h, int margin, CppBindCObject* _Nonnull cppbind_err) {
    
    auto& ctocxximage = *static_cast<cv::Mat*>(image.ptr);
    std::vector<cv::Point> ctocxxdoc_corner_points;

    auto data_doc_corner_points = reinterpret_cast<CppBindCObject*>(doc_corner_points.data);

    for (size_t _i_doc_corner_points = 0; _i_doc_corner_points < doc_corner_points.size; ++_i_doc_corner_points) {
        auto& value_doc_corner_points = data_doc_corner_points[_i_doc_corner_points];
        
        auto& ctocxxvalue_doc_corner_points = *static_cast<cv::Point*>(value_doc_corner_points.ptr);
        ctocxxdoc_corner_points.emplace_back(ctocxxvalue_doc_corner_points);
    }
    try {
        auto this_object = new DocExtractor(ctocxximage, ctocxxdoc_corner_points, w, h, margin);
        return {strdup(CPPBIND_DOCEXTRACTOR), this_object};
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

CppBindCObject _prop_get_DocExtractor_image(CppBindCObject cself, CppBindCObject* _Nonnull cppbind_err) {
    auto ctocxxcself = static_cast<DocExtractor*>(cself.ptr);
    try {
        const auto& result = ctocxxcself->image();
        
        char* type_result = strdup(CPPBIND_CV_MAT);
        auto value_ptr_result = const_cast<cv::Mat*>(new cv::Mat(result));
        CppBindCObject cxxtocresult = {type_result, value_ptr_result};
        return cxxtocresult;
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

void _prop_set_DocExtractor_image(CppBindCObject cself, CppBindCObject image, CppBindCObject* _Nonnull cppbind_err) {
    
    auto ctocxxcself = static_cast<DocExtractor*>(cself.ptr);
    
    auto& ctocxximage = *static_cast<cv::Mat*>(image.ptr);
    try {
        ctocxxcself->setImage(ctocxximage);
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
}

CppBindCObject _func_DocExtractor_warp(CppBindCObject cself, CppBindCObject* _Nonnull cppbind_err) {
    auto ctocxxcself = static_cast<DocExtractor*>(cself.ptr);
    try {
        const auto& result = ctocxxcself->warp();
        
        char* type_result = strdup(CPPBIND_CV_MAT);
        auto value_ptr_result = const_cast<cv::Mat*>(new cv::Mat(result));
        CppBindCObject cxxtocresult = {type_result, value_ptr_result};
        return cxxtocresult;
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

CppBindCObject _func_DocExtractor_drawPoints(CppBindCObject cself, int r, int g, int b, CppBindCObject* _Nonnull cppbind_err) {
  
  
  
    auto ctocxxcself = static_cast<DocExtractor*>(cself.ptr);
    try {
        const auto& result = ctocxxcself->drawPoints(r, g, b);
        
        char* type_result = strdup(CPPBIND_CV_MAT);
        auto value_ptr_result = const_cast<cv::Mat*>(new cv::Mat(result));
        CppBindCObject cxxtocresult = {type_result, value_ptr_result};
        return cxxtocresult;
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    CppBindCObject result {};
    return result;
}

bool _func__saveImage(char* _Nonnull filename, CppBindCObject img, CppBindCObject* _Nonnull cppbind_err) {
    auto ctocxxfilename = std::string(filename);
    free(filename);
    
    auto& ctocxximg = *static_cast<cv::Mat*>(img.ptr);
    try {
        const auto& result = ::saveImage(ctocxxfilename, ctocxximg);
        
        return result;
    } catch (const std::exception& e) {
        cppbind_err->type = strdup(CPPBIND_STD_STDEXCEPTION);
        cppbind_err->ptr = new std::exception(e);
    } catch (...) {
        cppbind_err->type = strdup("Uncaught Exception");
    }
    bool result {};
    return result;
}

