# CMakeList.txt : CMake project for hinfosvc

cmake_minimum_required (VERSION 3.16)

# Set the project name and version
project ("CAink" VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB_RECURSE srcs "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE hdrs "${PROJECT_SOURCE_DIR}/include/*.h")

# Add source to this project's executable.
add_executable ("${PROJECT_NAME}" ${srcs} ${hdrs})

# Add the header file directory
target_include_directories("${PROJECT_NAME}" PUBLIC ${PROJECT_SOURCE_DIR}/include)
