cmake_minimum_required(VERSION 3.10)
project(GraphicEngineOpenGL)

# Set C++ standard (adjust if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the headers directory so you can use #include <...>
include_directories(include)

# Define the executable target using the gathered sources
add_executable(GraphicEngineOpenGL src/main.cpp)
