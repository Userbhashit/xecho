# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and language
project(xecho C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Enable warnings
add_compile_options(-Wall -Wextra)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Automatically collect all .c files in src/
# Use a variable that updates when CMake is re-run
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.c")

# Define the executable
add_executable(xecho ${SOURCES})

# Put binary in build/ directory
set_target_properties(xecho PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

# Generate compile_commands.json for LSP/clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
