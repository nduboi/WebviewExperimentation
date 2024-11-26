cmake_minimum_required(VERSION 3.29)
project(WebViewExperimentation)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-D__x86_64__)

add_subdirectory(webview)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_executable(${CMAKE_PROJECT_NAME})
else ()
    add_executable(${CMAKE_PROJECT_NAME} WIN32)
endif ()

target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        webview::core
)
