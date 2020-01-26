cmake_minimum_required(VERSION 3.7)
project(opencl_tutorial_1)

find_package(OpenCL REQUIRED)
add_executable(tut1 main.cpp)
target_link_libraries(tut1 OpenCL::OpenCL)
