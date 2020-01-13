# OpenCL Tutorials

## Requirements

The presented tutorials were developed and tested on Windows 10, Visual Studio 2019 and [Intel SDK for OpenCL](https://software.intel.com/en-us/intel-opencl) so that can be run on Windows PCs in the computing labs. Tutorial 4 also depends on the Boost library. If you would like to develop OpenCL programs on your computer you have two options:
 - replicate the [Windows setup](#windows-setup) from the computing labs;
 - use the [multi_os](https://github.com/gcielniak/OpenCL-Tutorials/tree/multi_os) branch, which should allow for running the tutorials on different operating systems, programming environments and OpenCL SDKs. There is limited documentation for this option, however, so you should only choose that option if you are comfortable with installing custom libraries on your specific OS.
 
## Windows Setup
 - OS + IDE: Windows 10, Visual Studio 2019
 - OpenCL SDK: the SDK enables you to develop and compile the OpenCL code. In our case, we use [Intel SDK for OpenCL Applications](https://software.intel.com/en-us/intel-opencl). You are not tied to that choice, however, and can use SDKs by NVidia or AMD - just remember to make modifications in the project include paths. Each SDK comes with a range of additional tools which make development of OpenCL programs easier.
 - OpenCL runtime: the runtime drivers are necessary to run the OpenCL code on your hardware. Both NVidia and AMD GPUs have OpenCL runtime included with their card drivers. For CPUs, you will need to install a dedicated driver by [Intel](https://software.intel.com/en-us/articles/opencl-drivers) or APP SDK for older AMD processors. It seems that AMD’s OpenCL support for newer CPU models was dropped unfortunately. You can check the existing OpenCL support on your PC using [GPU Caps Viewer](http://www.ozone3d.net/gpu_caps_viewer/).
 - Boost library: install the recent [Boost library Windows binaries](https://sourceforge.net/projects/boost/files/boost-binaries/) (e.g. [boost_1_72_0](https://sourceforge.net/projects/boost/files/boost-binaries/1.72.0/boost_1_72_0-msvc-14.2-64.exe/download) for VS2019). Then, add two environmental variables in the command line specifying the location of the include and lib Boost directories. For example, with boost_1_72_0 the commands would look as follows: `setx BOOST_INCLUDEDIR "C:\local\boost_1_72_0"` and `setx BOOST_LIBRARYDIR "C:\local\boost_1_72_0\lib64-msvc-14.2"`.
 - A useful reference if you are struggling to get going: [OpenCL on Windows](http://streamcomputing.eu/blog/2015-03-16/how-to-install-opencl-on-windows/).
