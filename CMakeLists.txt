cmake_minimum_required(VERSION 2.8)

project(OpenCLTutorials)

find_package(OPENCL)

include_directories(${OpenCL_INCLUDE_DIRS})

add_executable(OpenCLTutorials src/Tutorial1.cpp)

target_link_libraries(OpenCLTutorials ${OpenCL_LIBRARIES})
		
message(STATUS "1: " ${EXECUTABLE_OUTPUT_PATH})

message(STATUS "2: "  ${CMAKE_BINARY_DIR})

message(STATUS "3: "  ${CMAKE_CURRENT_BINARY_DIR})

message(STATUS "4: "  ${PROJECT_BINARY_DIR})
		
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/opencl DESTINATION )

				   