#include <iostream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include "CL\cl.hpp"
#include "Utils.h"

using namespace std;

void print_help()
{
	cerr << "OpenCLTutorial usage:" << endl;

	cerr << "  -v : verbose level [0, 1, 2, 3]" << endl;
	cerr << "  -h : print this message" << endl;
}

int main(int argc, char **argv)
{
	int platform_id = -1;
	int device_id = -1;

	for (int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-p") == 0) && (i < (argc - 1))) { platform_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-d") == 0) && (i < (argc - 1))) { device_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-v") == 0) && (i < (argc - 1))) { ListPlatformsDevices((VerboseLevel)atoi(argv[++i])); }
		else if (strcmp(argv[i], "-h") == 0) { print_help(); }
	}

	cl::Context context = GetContext(platform_id, device_id);

	cl::Program::Sources sources;

	AddSources(sources, "kernels/simple_add.cl");

	cl::Program program(context, sources);

	try
	{
		program.build();
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
		return 0;
	}

	//host buffers
	//input
	std::vector<int> A = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //C++11 allows this type of initialisation
	std::vector<int> B = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	
	//output
	std::vector<int> C(A.size());

	// create buffers on the device
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, A.size()*sizeof(int));
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, B.size()*sizeof(int));
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, C.size()*sizeof(int));

	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context, CL_QUEUE_PROFILING_ENABLE);

	//write arrays A and B to the device
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, A.size()*sizeof(int), &A[0]);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, B.size()*sizeof(int), &B[0]);

	cl::Event evt;

	cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_B);
	kernel_add.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(A.size()), cl::NullRange, NULL, &evt);

	queue.finish();

	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, C.size()*sizeof(int), &C[0]);

	evt.wait();

	std::cout << " result: \n";
	for (int i = 0; i < C.size(); i++){
		std::cout << C[i] << " ";
	}
	cout << endl;

	cerr << "Time elapsed: " << evt.getProfilingInfo<CL_PROFILING_COMMAND_END>() - evt.getProfilingInfo<CL_PROFILING_COMMAND_START>() << " ns" << endl;

	return 0;
}