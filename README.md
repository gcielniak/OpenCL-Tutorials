# Dependencies

## Ubuntu
 - OpenCL development libs: `sudo apt install ocl-icd-opencl-dev`
 - OpenCL runtime drivers
 - Boost.Compute: from boost-1.61.0, it is part of the library. In particular situations, when you need to keep the older versions of boost (e.g. Ubuntu 16 + ROS Kinetic) you may need to apply the following ugly hack:
 ```
 cd /tmp/
 git clone git://github.com/kylelutz/compute.git
 sudo mv /tmp/compute/include/boost/compute /usr/include/boost
 sudo mv /tmp/compute/include/boost/compute.hpp /usr/include/boost/
```
