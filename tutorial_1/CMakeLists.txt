# sets versions and names of project
cmake_minimum_required(VERSION 3.7)
project(opencl_tutorial_1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# specify our compiled binaries name
set(BINARY_NAME tut1)
# specify all our cpp files names
set(CPP_FILES tut1.cpp)

# build our project executable, and link opencl lib
find_package(OpenCL REQUIRED)
add_executable(${BINARY_NAME} ${CPP_FILES})
target_link_libraries(tut1 OpenCL::OpenCL)
