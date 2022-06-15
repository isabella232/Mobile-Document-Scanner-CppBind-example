add_executable(
    document_scanner_app
    main.cpp
)

target_link_libraries(document_scanner_app PRIVATE document_scanner_lib)
target_link_libraries(document_scanner_app PRIVATE ${OpenCV_LIBS})
