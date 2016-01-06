#include <iostream>
#include <vector>
#include <string>

#define __CL_ENABLE_EXCEPTIONS
#include "CL\cl.hpp"
#include "Utils.h"
#include "Addons.h"

using namespace std;

void print_help()
{
	cerr << "OpenCLTutorial usage:" << endl;

	cerr << "  -p : select platform " << endl;
	cerr << "  -d : select device" << endl;
	cerr << "  -l : list all platforms and devices" << endl;
	cerr << "  -i : input length" << endl;
	cerr << "  -h : print this message" << endl;
}

int main(int argc, char **argv)
{
	//Part 1 - handle command line options such as device selection, verbosity, etc.
	int platform_id = 0;
	int device_id = 0;
	int input_length = 1;

	for (int i = 1; i < argc; i++)	{
		if ((strcmp(argv[i], "-p") == 0) && (i < (argc - 1))) { platform_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-d") == 0) && (i < (argc - 1))) { device_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-i") == 0) && (i < (argc - 1))) { input_length = atoi(argv[++i]); }
		else if (strcmp(argv[i], "-l") == 0) { cout << ListPlatformsDevices() << endl; }
		else if (strcmp(argv[i], "-h") == 0) { print_help(); }
	}

	//detect any potential exceptions
	try {

		//Part 2 - host operations
		//2.1 Select computing devices
		cl::Context context = GetContext(platform_id, device_id);
		
		//display the selected device
		cout << "Runinng on " << GetPlatformName(platform_id) << ", " << GetDeviceName(platform_id, device_id) << endl;

		//create a queue to which we will push commands for the device
		//	cl::CommandQueue queue(context);
		cl::CommandQueue queue(context, CL_QUEUE_PROFILING_ENABLE);

		//2.2 Load & build the device code
		cl::Program::Sources sources;

		AddSources(sources, "kernels/simple_add.cl");

		cl::Program program(context, sources);

		program.build();

		//Part 4 - memory allocation
		//host - input
		std::vector<int> A = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //C++11 allows this type of initialisation
		std::vector<int> B = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
//		std::vector<int> A(input_length);
//		std::vector<int> B(input_length);
		const int d = 5;
		//host - output
		std::vector<int> C(A.size());

		//device - buffers
		cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, A.size()*sizeof(int));
		cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, B.size()*sizeof(int));
		cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, C.size()*sizeof(int));

		//Part 5 - device operations

		cl::Event A_event, B_event, C_event, start_event, stop_event;

		queue.enqueueMarker(&start_event);

		start_event.wait();

		//5.1 Copy arrays A and B to device memory
		queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, A.size()*sizeof(int), &A[0], 0, &A_event);
		queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, B.size()*sizeof(int), &B[0], 0, &B_event);

		//5.2 Execute the device code (i.e. run the kernel)
		cl::Kernel kernel_mult = cl::Kernel(program, "simple_mult");
		kernel_mult.setArg(0, buffer_A);
		kernel_mult.setArg(1, buffer_B);
		kernel_mult.setArg(2, buffer_C);

		cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
		kernel_add.setArg(0, buffer_C);
		kernel_add.setArg(1, buffer_B);
		kernel_add.setArg(2, buffer_C);

		cl::Event kernel_event;
		queue.enqueueNDRangeKernel(kernel_mult, cl::NullRange, cl::NDRange(A.size()), cl::NullRange);
		queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(A.size()), cl::NullRange);

		//5.3 Copy the result from device to host
		queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, C.size()*sizeof(int), &C[0], 0, &C_event);

		queue.enqueueMarker(&stop_event);

		stop_event.wait();

		std::cout << "Upload A: " << GetFullProfilingInfo(A_event, ProfilingResolution::PROF_US) << endl;
		std::cout << "Upload B: " << GetFullProfilingInfo(B_event, ProfilingResolution::PROF_US) << endl;
		std::cout << "Download C: " << GetFullProfilingInfo(C_event, ProfilingResolution::PROF_US) << endl;
		std::cout << "Kernel execution: " << GetFullProfilingInfo(kernel_event, ProfilingResolution::PROF_US) << endl;
		std::cout << "Total: " << (C_event.getProfilingInfo<CL_PROFILING_COMMAND_END>() - A_event.getProfilingInfo<CL_PROFILING_COMMAND_QUEUED>()) / 1000 << endl;

			std::cout << "A = " << A << endl;
			std::cout << "B = " << B << endl;
			std::cout << "C = " << C << endl;
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << ", " << getErrorString(err.err()) << endl;
	}

	return 0;
}