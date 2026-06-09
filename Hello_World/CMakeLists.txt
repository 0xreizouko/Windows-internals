cmake_minimum_required(VERSION 4.0)
project(Hello_World)

include(${CMAKE_SOURCE_DIR}/cmake/common.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/windows_manifest.cmake)

enable_language(ASM_MASM)
add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/syscall.asm
)

enable_optional_manifest(${PROJECT_NAME})
