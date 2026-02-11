cmake_minimum_required(VERSION 4.0)
project(libTest)

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/windows_manifest.cmake)

add_executable(${PROJECT_NAME} 
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    SimpleLibrary
)

enable_optional_manifest(${PROJECT_NAME})
