cmake_minimum_required(VERSION 2.6)

project("Tutorial 3")

set(TARGET_NAME Tutorial_3)

set(CMAKE_CXX_STANDARD 11)

set(EXTRA_INCLUDE_DIRS ../include)
set(EXTRA_LIBRARY_DIRS "")
set(EXTRA_LIBRARIES "")

find_package(OpenCL REQUIRED)

set (EXTRA_INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARY_DIRS} ${OPENCL_LIBRARY})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${OpenCL_LIBRARIES})

set (SOURCES
	../include/Utils.h
	"src/Tutorial 3.cpp"
	src/kernels/my_kernels_3.cl)

include_directories(${EXTRA_INCLUDE_DIRS})
link_directories(${EXTRA_LIBRARY_DIRS})

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries (${TARGET_NAME} ${EXTRA_LIBRARIES})

#copy kernel files to target directory
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/kernels/"
                   $<TARGET_FILE_DIR:${TARGET_NAME}>/kernels/)

#additional command to copy kernels into a working directory allowing debugging directly from VS				   
if (MSVC)
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/kernels/"
                   kernels)
endif(MSVC)
