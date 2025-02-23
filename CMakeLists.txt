cmake_minimum_required(VERSION 3.10)
project(GraphicEngineOpenGL)

# Set C++ standard (adjust if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the headers directory so we can use #include <...>
include_directories(include)

# Gather all source files .cpp in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# add all source files and the glad.c file to the executable
add_executable(GraphicEngineOpenGL ${SOURCES} src/glad.c "src/texture.cpp")

# Link libraries
target_link_libraries(GraphicEngineOpenGL ${CMAKE_SOURCE_DIR}/lib/glfw3.lib)

# Copy resources to the build directory
add_custom_command(TARGET GraphicEngineOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/ressources
        ${CMAKE_BINARY_DIR}/ressources
)