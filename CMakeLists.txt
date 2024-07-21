cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PVZ_HEROES VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the executable
add_executable(PVZ_HEROES 
    src/main.cpp
)

# Include directories for the target
target_include_directories(PVZ_HEROES PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)
