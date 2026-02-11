cmake_minimum_required(VERSION 4.0)
project(SimpleLibrary)

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/windows_manifest.cmake)

add_library(${PROJECT_NAME} SHARED 
    src/SimpleLibrary.cpp
)

target_include_directories(${PROJECT_NAME} 
     PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/headers 
)

target_compile_definitions(${PROJECT_NAME}  
    PRIVATE ${PROJECT_NAME}_EXPORTS
)

enable_optional_manifest(${PROJECT_NAME})
