#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define __CL_ENABLE_EXCEPTIONS

#include <iostream>
#include <vector>

// Include guarded openCL libs
#ifdef __APPLE__
	#include <OpenCL/cl.hpp>
#else
	#include <CL/cl.hpp>
#endif

int main(int argc, char **argv) {

	std::cout << "Hello" << std::endl;
	return 0;
}
