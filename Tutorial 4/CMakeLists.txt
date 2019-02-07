cmake_minimum_required(VERSION 2.6)

project("Tutorial 4")

set(TARGET_NAME Tutorial_4)

set(CMAKE_CXX_STANDARD 11)

set(EXTRA_INCLUDE_DIRS ../include)
set(EXTRA_LIBRARY_DIRS "")
set(EXTRA_LIBRARIES "")

find_package(Boost REQUIRED)

set (EXTRA_INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
set (EXTRA_LIBRARY_DIRS ${EXTRA_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

find_package(OpenCL REQUIRED)

set (EXTRA_INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS} ${OpenCL_INCLUDE_DIRS})
set (EXTRA_LIBRARY_DIRS ${EXTRA_LIBRARY_DIRS} ${OPENCL_LIBRARY})
set (EXTRA_LIBRARIES ${EXTRA_LIBRARIES} ${OpenCL_LIBRARIES})

message(${Boost_INCLUDE_DIRS})

set (SOURCES
	"src/Tutorial 4.cpp")

include_directories(${EXTRA_INCLUDE_DIRS})
link_directories(${EXTRA_LIBRARY_DIRS})

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries (${TARGET_NAME} ${EXTRA_LIBRARIES})
