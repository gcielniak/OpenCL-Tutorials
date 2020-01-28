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

FROM nvidia/opencl

# setting up the place, making sure everything is installed, and getting the
# pesky CL/cl2.hpp
RUN mkdir -p /opencl_tutorials && \
    apt update -y && \
    apt install -y cmake make gcc git build-essential ocl-icd-opencl-dev && \
    git clone https://github.com/KhronosGroup/opencl-clhpp && \
    cp opencl-clhpp/include/CL/cl2.hpp /usr/include/CL/cl2.hpp && \
    rm -r /opencl-clhpp && \
    echo "cd /opencl_tutorials" >> /root/.bashrc

COPY . /opencl_tutorials/
