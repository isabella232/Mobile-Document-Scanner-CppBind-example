cmake_minimum_required(VERSION 3.22.0)

project(document_scanner)

set(CMAKE_CXX_STANDARD 14)


if (NOT EXISTS $ENV{OPENCV_DIR})
    message(FATAL_ERROR "Please specify OpenCV dir with OPENCV_DIR environment variable.")
endif ()

set(OpenCV_DIR $ENV{OPENCV_DIR} CACHE STRING "OpenCV directory")

find_package(OpenCV REQUIRED)

include_directories(
        ${OpenCV_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}
)

add_subdirectory(document_scanner)
add_subdirectory(apps)
