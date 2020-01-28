# Tutorial 1

This directory "tutorial_1" is a completeley self contained OpenCL example. It has CMake to build itself and Docker to automate all the dependencies and building for you. To build this project without docker simply run the build.sh file.

Note: All following instructions are to be followed from the command line or terminal from inside this directory locally.

## universal Docker

Docker allows us to install everything consistently between all operating systems, platforms, etc, in a light weight virtual machine, so that we dont have to worry about installing anything other than docker itself.

To use docker for opencl you will need only two dependancies [docker](https://wiki.archlinux.org/index.php/Docker) and the docker [NVIDIA container toolkit](https://wiki.archlinux.org/index.php/Docker#With_NVIDIA_Container_Toolkit_(recommended)).

This docker can then be run on Linux by:
  ```sudo docker build -t archer/opencl .``` which will download, install, build everything for you. Then you can use it interactiveley by connecting to it ```sudo docker run --gpus all -it archer/opencl bash```. When you log in you will be in your current directory again but this time inside a container where you can build/ test all you like, and then it gets wiped when you close. Enjoy the consistent sandbox!

## Linux

On Linux simply: ```./build.sh``` to build the project in a folder called "build", and run it automatically for you for convenience.

(it has a shebang which means it knows what program to run as its specified at the top of the file)



If you would rather not have to install cmake or any other dependancies, or if you want to ensure it works consistently, or if you are forced to use windows but would like an actual useful OS in your hands, then simply use the Dockerfile.

## Windows

On windows in theory run ```cmake``` then ```make``` to build the project then run the file called ```tut1```. CMake can also build visual studio solutions for you if you still desire them. I believe the incantation will be ```cmake -G "Visual Studio 10 Win64"```
