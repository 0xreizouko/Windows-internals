
cmake_minimum_required(VERSION 4.0)
project(internals)

add_subdirectory(getVersion)
add_subdirectory(messageBox)
add_subdirectory(CreateProcess)

add_subdirectory(SimpleLibrary)

add_subdirectory(libTest)

add_subdirectory(explicitLinking)

add_subdirectory(terminateProcess)

add_subdirectory(SegmentRegisters)

add_subdirectory(Hello_World)
