add_library(
    document_scanner_lib
    SHARED
    document_scanner_cv.cpp
)

target_link_libraries(document_scanner_lib PRIVATE ${OpenCV_LIBS})
