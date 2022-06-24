if (NOT ANDROID)
    find_package(JNI REQUIRED)
    include_directories(${JNI_INCLUDE_DIRS})
endif ()



file(GLOB_RECURSE JNI_FILES jni/*.cpp)

add_library(
    document_scanner
    SHARED
    ${JNI_FILES}
)


target_link_libraries(
    document_scanner
    document_scanner_lib
    ${OpenCV_LIBS}
)

if (ANDROID)

    find_library(
        log-lib
        log
    )

    find_library(jnigraphics-lib jnigraphics)
    target_link_libraries(
        document_scanner
        ${jnigraphics-lib}
        ${log-lib}
    )
endif ()
