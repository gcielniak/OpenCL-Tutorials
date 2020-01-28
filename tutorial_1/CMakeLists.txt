# MIT License
# ===========
#
# Copyright (c) 2019 George Onoufriou (GeorgeRaven, archer, DreamingRaven)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# sets versions and names of project
cmake_minimum_required(VERSION 3.7)
project(opencl_tutorial_1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# specify our compiled binaries name
set(BINARY_NAME tut1)
# specify all our cpp files names
set(CPP_FILES tut1.cpp utils.h)

# build our project executable, and link opencl lib
find_package(OpenCL 2 REQUIRED)
add_executable(${BINARY_NAME} ${CPP_FILES})
target_link_libraries(tut1 OpenCL::OpenCL)

# copy kernel files over to binary directory so it can access them
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/kernels/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/kernels/)
