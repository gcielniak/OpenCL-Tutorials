cmake_minimum_required(VERSION 2.6)

project("Tutorial 1")

set(CMAKE_CXX_STANDARD 11)

set(EXTRA_INCLUDE_DIRS ../include)
set(EXTRA_LIBRARY_DIRS "")
set(EXTRA_LIBRARIES "")

find_package(OpenCL REQUIRED)

set (EXTRA_INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARY_DIRS} ${OPENCL_LIBRARY})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${OpenCL_LIBRARIES})

include_directories(${EXTRA_INCLUDE_DIRS})
link_directories(${EXTRA_LIBRARY_DIRS})

set (SOURCES
	../include/Utils.h
	"src/Tutorial 1.cpp"
	src/kernels/my_kernels_1.cl)

add_executable(Tutorial_1 ${SOURCES})

target_link_libraries (Tutorial_1 ${EXTRA_LIBRARIES})

#copy kernel files to target directory
add_custom_command(TARGET Tutorial_1 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/Tutorial 1/src/kernels/"
                   $<TARGET_FILE_DIR:Tutorial_1>/kernels/)

#additional command to copy kernels into a working directory allowing debugging directly from VS				   
if (MSVC)
add_custom_command(TARGET Tutorial_1 PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/Tutorial 1/src/kernels/"
                   kernels)
endif(MSVC)