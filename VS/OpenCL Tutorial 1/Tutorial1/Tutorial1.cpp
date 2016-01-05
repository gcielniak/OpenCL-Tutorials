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
	cerr << "  -l : list all platforms and devices, verbose level [0, 1, 2, 3]" << endl;
	cerr << "  -h : print this message" << endl;
}

int main(int argc, char **argv)
{
	//Part 1 - handle command line options such as device selection, verbosity, etc.
	int platform_id = 0;
	int device_id = 0;
	
	for (int i = 1; i < argc; i++)	{
		if ((strcmp(argv[i], "-p") == 0) && (i < (argc - 1))) { platform_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-d") == 0) && (i < (argc - 1))) { device_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-l") == 0) && (i < (argc - 1))) { ListPlatformsDevices((VerboseLevel)atoi(argv[++i])); }
		else if (strcmp(argv[i], "-h") == 0) { print_help(); }
	}

	//Part 2 - host operations
	//2.1 Select computing devices
	cl::Context context = GetContext(platform_id, device_id);
	//display the selected device
	
	cout << "Runinng on: " << GetPlatformName(platform_id) << ", " << GetDeviceName(platform_id, device_id) << endl;

	//create a queue to which we will push commands for the device
//	cl::CommandQueue queue(context);
	cl::CommandQueue queue(context, CL_QUEUE_PROFILING_ENABLE);

	//2.2 Load & build the device code
	cl::Program::Sources sources;

	AddSources(sources, "kernels/simple_add.cl");

	cl::Program program(context, sources);

	try	{
		program.build();
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
		return 0;
	}

	//Part 4 - memory allocation
	//host - input
	std::vector<int> A = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; //C++11 allows this type of initialisation
	std::vector<int> B = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	//host - output
	std::vector<int> C(A.size());

	//device - buffers
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, A.size()*sizeof(int));
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, B.size()*sizeof(int));
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, C.size()*sizeof(int));

	//Part 5 - device operations

	//5.1 Copy arrays A and B to device memory
	queue.enqueueWriteBuffer(buffer_A, CL_TRUE, 0, A.size()*sizeof(int), &A[0]);
	queue.enqueueWriteBuffer(buffer_B, CL_TRUE, 0, B.size()*sizeof(int), &B[0]);

	//5.2 Execute the device code (i.e. run the kernel)
	cl::Kernel kernel_add = cl::Kernel(program, "simple_add");
	kernel_add.setArg(0, buffer_A);
	kernel_add.setArg(1, buffer_B);
	kernel_add.setArg(2, buffer_C);

	cl::Event prof_event;
//	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(A.size()), cl::NullRange);
	queue.enqueueNDRangeKernel(kernel_add, cl::NullRange, cl::NDRange(A.size()), cl::NullRange, NULL, &prof_event);

	queue.finish();//wait until all processing is finished

	prof_event.wait(); //wait until all measurements are preformed

	//5.3 Copy the result from device to host
	queue.enqueueReadBuffer(buffer_C, CL_TRUE, 0, C.size()*sizeof(int), &C[0]);

	std::cout << "A = : " << A << endl;
	std::cout << "B = : " << B << endl;
	std::cout << "C = : " << C << endl;

	std::cout << GetFullProfilingInfo(prof_event, ProfilingResolution::PROF_US) << endl;

	return 0;
}