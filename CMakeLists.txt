cmake_minimum_required(VERSION 2.8)

project(OpenCLTutorials)

find_package(OPENCL)

include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(OpenCLTutorials src/Tutorial1.cpp)

target_link_libraries(OpenCLTutorials ${OpenCL_LIBRARIES})

