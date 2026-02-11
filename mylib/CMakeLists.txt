cmake_minimum_required(VERSION 4.0)
project(mylib)

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/windows_manifest.cmake)

add_library(${PROJECT_NAME} SHARED 
    src/main.cpp
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/headers 
)

enable_optional_manifest(${PROJECT_NAME})
