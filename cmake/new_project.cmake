if (NOT DEFINED NAME)
    message(FATAL_ERROR "Usage: cmake -P cmake/new_project.cmake -DNAME=<project_name> [-DGUI=ON]")
endif()

set(PROJECT_NAME ${NAME})
set(PROJECT_DIR "${CMAKE_CURRENT_LIST_DIR}/../${PROJECT_NAME}")

if (EXISTS "${PROJECT_DIR}")
    message(FATAL_ERROR "Project '${PROJECT_NAME}' already exists")
endif()

if (DEFINED GUI AND GUI)
    set(CMAKE_TEMPLATE "CMakeLists.txt.gui.in")
    set(MAIN_TEMPLATE "main.gui.cpp.in")
    message(STATUS "Creating GUI project")
else()
    set(CMAKE_TEMPLATE "CMakeLists.txt.cli.in")
    set(MAIN_TEMPLATE "main.cli.cpp.in")
    message(STATUS "Creating cli project")
endif()

file(MAKE_DIRECTORY "${PROJECT_DIR}")
file(MAKE_DIRECTORY "${PROJECT_DIR}/src")

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/templates/${CMAKE_TEMPLATE}"
    "${PROJECT_DIR}/CMakeLists.txt"
    @ONLY
)

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/templates/${MAIN_TEMPLATE}"
    "${PROJECT_DIR}/src/main.cpp"
    @ONLY
)

message(STATUS "Project created at ${PROJECT_DIR}")
message(STATUS "Add this line to the root CMakeLists.txt:")
message(STATUS "  add_subdirectory(${PROJECT_NAME})")

# Root CMakeLists.txt
set(ROOT_CMAKELISTS
    "${CMAKE_CURRENT_LIST_DIR}/../CMakeLists.txt"
)

if (NOT EXISTS "${ROOT_CMAKELISTS}")
    message(FATAL_ERROR "Root CMakeLists.txt not found")
endif()

# Read root CMakeLists.txt
file(READ "${ROOT_CMAKELISTS}" ROOT_CONTENTS)

set(ADD_LINE "add_subdirectory(${PROJECT_NAME})")

# Check if already registered
string(FIND "${ROOT_CONTENTS}" "${ADD_LINE}" FOUND_INDEX)

if (FOUND_INDEX EQUAL -1)
    message(STATUS "Registering project in root CMakeLists.txt")
    file(APPEND "${ROOT_CMAKELISTS}"
        "\n${ADD_LINE}\n"
    )
else()
    message(STATUS "Project already registered in root CMakeLists.txt")
endif()
