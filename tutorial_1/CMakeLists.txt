find_package(OpenCL REQUIRED)
add_executable(test_tgt main.cpp)
target_link_libraries(test_tgt OpenCL::OpenCL)
