cmake_minimum_required(VERSION 2.6)

project("Tutorial 2")

set(TARGET_NAME Tutorial_2)

set(CMAKE_CXX_STANDARD 11)

set(EXTRA_INCLUDE_DIRS ../include)
set(EXTRA_LIBRARY_DIRS "")
set(EXTRA_LIBRARIES "")

find_package(OpenCL REQUIRED)

set (EXTRA_INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
set (EXTRA_LIBRARY_DIRS ${EXTRA_LIBRARY_DIRS} ${OPENCL_LIBRARY})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${OpenCL_LIBRARIES})

if (NOT MSVC)
find_package(Threads REQUIRED)
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

find_package(X11 REQUIRED)
set (EXTRA_INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS} ${X11_INCLUDE_DIR})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${X11_LIBRARIES})
endif (NOT MSVC)

set (SOURCES
	../include/Utils.h
	"src/Tutorial 2.cpp"
	src/kernels/my_kernels_2.cl)

include_directories(${EXTRA_INCLUDE_DIRS})
link_directories(${EXTRA_LIBRARY_DIRS})

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries (${TARGET_NAME} ${EXTRA_LIBRARIES})

#copy kernel files to target directory
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/kernels/"
                   $<TARGET_FILE_DIR:${TARGET_NAME}>/kernels/)

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/images"
                   $<TARGET_FILE_DIR:${TARGET_NAME}>)

#additional command to copy kernels into a working directory allowing debugging directly from VS				   
if (MSVC)
add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_CURRENT_SOURCE_DIR}/src/kernels/"
                   kernels)

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   "${CMAKE_SOURCE_DIR}/images"
                   .)
endif(MSVC)