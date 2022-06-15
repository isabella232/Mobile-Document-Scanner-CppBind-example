find_package(pybind11 REQUIRED)

include_directories(${pybind11_INCLUDE_DIRS})

pybind11_add_module(
        document_scanner_pybind
        SHARED
        THIN_LTO
        generated/wrappers/document_scanner_pybind_module.cpp
        generated/wrappers/document_scanner_pybind.cpp
        generated/wrappers/document_scanner_pybind.hpp
        generated/wrappers/cv/imgcodecs.cpp
        generated/wrappers/cv/imgcodecs.hpp
        generated/wrappers/cv/mat.cpp
        generated/wrappers/cv/mat.hpp
        generated/wrappers/cv/types.cpp
        generated/wrappers/cv/types.hpp
        generated/wrappers/doc_scanner/document_scanner_cv.cpp
        generated/wrappers/doc_scanner/document_scanner_cv.hpp
)


target_link_libraries(document_scanner_pybind PRIVATE document_scanner_lib)
target_link_libraries(document_scanner_pybind PRIVATE ${OpenCV_LIBS})

target_compile_definitions(
        document_scanner_pybind
        PRIVATE VERSION_INFO=0.0.1
)
