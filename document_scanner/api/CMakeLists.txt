if (UNIX
        AND NOT IOS
        AND NOT ANDROID)
add_subdirectory(python)
endif ()

add_subdirectory(android)
