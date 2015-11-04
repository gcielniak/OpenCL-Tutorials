#include <iostream>
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
	VerboseLevel verbose_level = VERBOSE_OFF;
	int platform_id = -1;
	int device_id = -1;

	for (int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-p") == 0) && (i < (argc - 1))) { platform_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-d") == 0) && (i < (argc - 1))) { device_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-v") == 0) && (i < (argc - 1))) { verbose_level = (VerboseLevel)atoi(argv[++i]); }
		else if (strcmp(argv[i], "-h") == 0) { print_help(); }
	}

	ListPlatformsDevices(verbose_level);

	vector<cl::Platform> platforms;

	//select device
	cl::Device device;

	cl::Context context(CL_DEVICE_TYPE_GPU);

	try
	{
		cl::Platform::get(&platforms);

		for (unsigned int i = 0; i < platforms.size(); i++)
		{
			vector<cl::Device> devices;
			platforms[i].getDevices((cl_device_type)CL_DEVICE_TYPE_ALL, &devices);

			for (unsigned int j = 0; j < devices.size(); j++)
			{
				if ((i == platform_id) && (j == device_id)) {
					device = devices[j];
					context = cl::Context({ device });
				}
				break;
			}
		}
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
	}


	cl::Program::Sources sources;

	AddSources(sources, "kernels/simple_add.cl");

	cl::Program program(context, sources);

	try
	{
		program.build();
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
	}

	//host buffers
	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	int C[sizeof(A) / sizeof(A[0])];

	// create buffers on the device
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(A));
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(B));
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(C));

	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context);

	//write arrays A and B to the device
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, sizeof(A), A);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, sizeof(B), B);

	cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_B);
	kernel_add.setArg(2, buffer_C);
	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(sizeof(A) / sizeof(A[0])), cl::NullRange);

	queue.finish();

	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, sizeof(C), C);

	std::cout << " result: \n";
	for (int i = 0; i<10; i++){
		std::cout << C[i] << " ";
	}

	return 0;
}