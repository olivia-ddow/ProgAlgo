# Cmake version 3.11 in for FetchContent
cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(ProgAlgo VERSION 0.1.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set directory paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===========================================================================================
# GLAD CONFIGURATION
#
# Configure GLAD loader generation variables (lines below pulled from the GLAD top-level
# CMakeLists.txt file, with slight modifications.
# Refer to https://github.com/Dav1dde/glad for more information)

set(GLAD_OUT_DIR        "${CMAKE_CURRENT_BINARY_DIR}" CACHE STRING "Output directory" FORCE)
# set(GLAD_PROFILE        "core" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_PROFILE        "compatibility" CACHE STRING "OpenGL profile" FORCE)
set(GLAD_API            "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest" FORCE)
set(GLAD_GENERATOR      "c" CACHE STRING "Language to generate the binding for" FORCE)
set(GLAD_EXTENSIONS     "" CACHE STRING "Path to extensions file or comma separated list of extensions, if missing all extensions are included" FORCE)
set(GLAD_SPEC           "gl" CACHE STRING "Name of the spec" FORCE)
set(GLAD_ALL_EXTENSIONS OFF CACHE BOOL "Include all extensions instead of those specified by GLAD_EXTENSIONS" FORCE)
set(GLAD_NO_LOADER      OFF CACHE BOOL "No loader" FORCE)
set(GLAD_REPRODUCIBLE   OFF CACHE BOOL "Reproducible build" FORCE)
#===========================================================================================

set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME})


# Get source files
file(GLOB SRC_FILES CONFIGURE_DEPENDS "./*.cpp")
# link files to project target
target_sources(${TARGET_NAME} PRIVATE ${SRC_FILES})
# target_include_directories(${TARGET_NAME} PRIVATE "src/")


# Enable C++17
set_target_properties(${TARGET_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Enable good warnings
if (MSVC)
   target_compile_options(${TARGET_NAME} PRIVATE /W3)
else()
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()

# Set the project folder
set_target_properties(${TARGET_NAME} PROPERTIES FOLDER ${PROJECT_NAME})
# Set the folder where the executable will be created
set_target_properties(${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)


find_package(OpenGL REQUIRED)
if (OpenGL_FOUND)
    target_include_directories(${TARGET_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} PRIVATE ${OPENGL_LIBRARIES})
else()
    message(FATAL_ERROR "OpenGL was not found on the system")
endif()


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

if (SDL2_FOUND)
    target_include_directories(${TARGET_NAME} PRIVATE ${OPENGL_INCLUDE_DIRS})
    target_link_libraries(${TARGET_NAME} PRIVATE ${SDL2_LIBRARIES})
else()
    message(FATAL_ERROR "SDL2 was not found on the system")
endif()