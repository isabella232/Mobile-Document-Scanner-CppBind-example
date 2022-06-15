## About

Document Scanner is a sample application demonstrating the usage of [CppBind](https://github.com/PicsArt/cppbind) tool.
In this example, the tool allows the use of C++ OpenCV library in different platforms (iOS, Android), by generating wrappers over it.
The application captures a photo using the phone camera and extracts a document from it. The original Document Scanner app is written in C++ and uses [OpenCV](https://opencv.org).

This repository contains:
- CppBind-generated wrappers for functions and types from OpenCV used in Document Scanner for Kotlin, Python and Swift.
- apps with Document Scanner's functionality written in the languages listed above.

### Repository structure

- document_scanner - contains the original library(under `document_scanner_lib` subdirectory) and the generated APIs for Android, iOS and Python.
- *cppbind.yaml, cv.yaml - CppBind configuration files.
- apps - directory containing the sample applications.
- CMakeLists.txt - cmake files.

To regenerate the bindings use `cppbind run swift kotlin python` command.

### Running the applications

To build and run the sample applications, **CMake** and **OpenCV** should be installed.


#### To build the library run the following commands:

```
export OPENCV_DIR=<opencv_directory_here>
mkdir build_dir
cd build_dir
cmake .. 
cmake --build .
cd ..
```

#### To run the Python sample use the following commands

```
export PYTHONPATH=$PYTHONPATH:$(pwd)/document_scanner/api/python/generated/python:$(pwd)/build_dir/document_scanner/api/python
python3 apps/python/main.py data/img/paper.jpeg data/out
```

#### To compile and run the Kotlin sample use the following commands

Make sure Kotlin is installed and available on the path.

```
kotlinc document_scanner/api/android/docscanner/src/main/java/**/*.kt  apps/kotlin/main.kt  -include-runtime  -d apps/kotlin/libs/doc_scanner.jar                                        
kotlin -cp apps/kotlin/libs/doc_scanner.jar -Djava.library.path=build_dir/document_scanner/api/android/docscanner/src/main/cpp doc_scanner.DocumentScannerApp data/img/paper.jpeg data/out
```

#### To run the original sample in C++ use the following command:

```
build_dir/apps/document_scanner_app/document_scanner_app data/img/paper.jpeg data/out
```

You can also run the above commands with no arguments i.e. `build_dir/document_scanner/cxx/document_scanner_app`.
In this case `data/img/paper.jpeg` will be used and the outputs will be saved in `/tmp` directory.

For running the Android sample see [Android sample](apps/android/README.md).
For running the iOS sample see [iOS sample](apps/ios/README.md)
