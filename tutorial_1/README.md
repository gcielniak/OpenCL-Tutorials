# Tutorial 1

This directory "tutorial_1" is a completeley self contained OpenCL example. It has CMake to build itself and Docker to automate all the dependencies and building for you. To build this project without docker simply run the build.sh file.

## universal Docker

Docker allows us to install everything consistently between all operating systems, platforms, etc, in a light weight virtual machine, so that we dont have to worry about installing anything other than docker itself.

This docker can be run on Linux by:
  ```sudo docker build -t archer/opencl .``` which will download, install, build everything for you. Then you can use it interactiveley by connecting to it ```sudo docker run --gpus all -it archer/opencl bash``` All the local files can be found in ```~/opencl-tutorials``` directory

## Linux

On Linux simply: ```./build.sh``` to build the project in a folder called "build", and run it automatically for you for convenience.

(it has a shebang which means it knows what program to run as its specified at the top of the file)



If you would rather not have to install cmake or any other dependancies, or if you want to ensure it works consistently, or if you are forced to use windows but would like an actual useful OS in your hands, then simply use the Dockerfile.

## Windows

On windows in theory run ```cmake``` then ```make``` to build the project then run the file called ```tut1```.
