#include <iostream>
#include <vector>
#include <string>

#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
#define __CL_ENABLE_EXCEPTIONS

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

std::string GetPlatformName(cl_platform_id id)
{
	size_t size = 0;
	clGetPlatformInfo(id, CL_PLATFORM_NAME, 0, nullptr, &size);

	std::string result;
	result.resize(size);
	clGetPlatformInfo(id, CL_PLATFORM_NAME, size,
		const_cast<char*> (result.data()), nullptr);

	return result;
}

std::string GetDeviceName(cl_device_id id)
{
	size_t size = 0;
	clGetDeviceInfo(id, CL_DEVICE_NAME, 0, nullptr, &size);

	std::string result;
	result.resize(size);
	clGetDeviceInfo(id, CL_DEVICE_NAME, size,
		const_cast<char*> (result.data()), nullptr);

	return result;
}

const char *getErrorString(cl_int error)
{
	switch (error){
		// run-time and JIT compiler errors
	case 0: return "CL_SUCCESS";
	case -1: return "CL_DEVICE_NOT_FOUND";
	case -2: return "CL_DEVICE_NOT_AVAILABLE";
	case -3: return "CL_COMPILER_NOT_AVAILABLE";
	case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
	case -5: return "CL_OUT_OF_RESOURCES";
	case -6: return "CL_OUT_OF_HOST_MEMORY";
	case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
	case -8: return "CL_MEM_COPY_OVERLAP";
	case -9: return "CL_IMAGE_FORMAT_MISMATCH";
	case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	case -11: return "CL_BUILD_PROGRAM_FAILURE";
	case -12: return "CL_MAP_FAILURE";
	case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
	case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
	case -15: return "CL_COMPILE_PROGRAM_FAILURE";
	case -16: return "CL_LINKER_NOT_AVAILABLE";
	case -17: return "CL_LINK_PROGRAM_FAILURE";
	case -18: return "CL_DEVICE_PARTITION_FAILED";
	case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

		// compile-time errors
	case -30: return "CL_INVALID_VALUE";
	case -31: return "CL_INVALID_DEVICE_TYPE";
	case -32: return "CL_INVALID_PLATFORM";
	case -33: return "CL_INVALID_DEVICE";
	case -34: return "CL_INVALID_CONTEXT";
	case -35: return "CL_INVALID_QUEUE_PROPERTIES";
	case -36: return "CL_INVALID_COMMAND_QUEUE";
	case -37: return "CL_INVALID_HOST_PTR";
	case -38: return "CL_INVALID_MEM_OBJECT";
	case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	case -40: return "CL_INVALID_IMAGE_SIZE";
	case -41: return "CL_INVALID_SAMPLER";
	case -42: return "CL_INVALID_BINARY";
	case -43: return "CL_INVALID_BUILD_OPTIONS";
	case -44: return "CL_INVALID_PROGRAM";
	case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
	case -46: return "CL_INVALID_KERNEL_NAME";
	case -47: return "CL_INVALID_KERNEL_DEFINITION";
	case -48: return "CL_INVALID_KERNEL";
	case -49: return "CL_INVALID_ARG_INDEX";
	case -50: return "CL_INVALID_ARG_VALUE";
	case -51: return "CL_INVALID_ARG_SIZE";
	case -52: return "CL_INVALID_KERNEL_ARGS";
	case -53: return "CL_INVALID_WORK_DIMENSION";
	case -54: return "CL_INVALID_WORK_GROUP_SIZE";
	case -55: return "CL_INVALID_WORK_ITEM_SIZE";
	case -56: return "CL_INVALID_GLOBAL_OFFSET";
	case -57: return "CL_INVALID_EVENT_WAIT_LIST";
	case -58: return "CL_INVALID_EVENT";
	case -59: return "CL_INVALID_OPERATION";
	case -60: return "CL_INVALID_GL_OBJECT";
	case -61: return "CL_INVALID_BUFFER_SIZE";
	case -62: return "CL_INVALID_MIP_LEVEL";
	case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
	case -64: return "CL_INVALID_PROPERTY";
	case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
	case -66: return "CL_INVALID_COMPILER_OPTIONS";
	case -67: return "CL_INVALID_LINKER_OPTIONS";
	case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

		// extension errors
	case -1000: return "CL_INVALID_GL_SHAREGROUP_REFERENCE_KHR";
	case -1001: return "CL_PLATFORM_NOT_FOUND_KHR";
	case -1002: return "CL_INVALID_D3D10_DEVICE_KHR";
	case -1003: return "CL_INVALID_D3D10_RESOURCE_KHR";
	case -1004: return "CL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR";
	case -1005: return "CL_D3D10_RESOURCE_NOT_ACQUIRED_KHR";
	default: return "Unknown OpenCL error";
	}
}

void CheckError(cl_int error)
{
	if (error != CL_SUCCESS) {
		std::cerr << "OpenCL call failed with error " << getErrorString(error) << std::endl;
		std::exit(1);
	}
}

enum VerboseLevel
{
	VERBOSE_OFF,
	VERBOSE_BRIEF,
	VERBOSE_DETAILED,
	VERBOSE_FULL
};

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
	int platform_id = 0;
	int device_id = 0;

	for (int i = 1; i < argc; i++)
	{
		if ((strcmp(argv[i], "-p") == 0) && (i < (argc - 1))) { platform_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-d") == 0) && (i < (argc - 1))) { device_id = atoi(argv[++i]); }
		else if ((strcmp(argv[i], "-v") == 0) && (i < (argc - 1))) { verbose_level = (VerboseLevel)atoi(argv[++i]); }
		else if (strcmp(argv[i], "-h") == 0) { print_help(); }
	}

	vector<cl::Platform> platforms;

	if (verbose_level != VERBOSE_OFF)
	{
	try
	{
		cl::Platform::get(&platforms);

		cout << "Found " << platforms.size() << " platform(s):" << endl;

		for (unsigned int i = 0; i < platforms.size(); i++)
		{
			cout << "\n " << (i + 1) << ") " << platforms[i].getInfo<CL_PLATFORM_NAME>() << ", version: " << platforms[i].getInfo<CL_PLATFORM_VERSION>();

			if (verbose_level > VERBOSE_BRIEF)
				cout << ", vendor: " << platforms[i].getInfo<CL_PLATFORM_VENDOR>();

			if (verbose_level > VERBOSE_DETAILED)
				cout << ", profile: " << platforms[i].getInfo<CL_PLATFORM_PROFILE>() << ", extensions: " << platforms[i].getInfo<CL_PLATFORM_EXTENSIONS>();

			cout << endl;

			vector<cl::Device> devices;

			platforms[i].getDevices((cl_device_type)CL_DEVICE_TYPE_ALL, &devices);

			cout << "\tFound " << devices.size() << " device(s):" << endl;

			for (unsigned int j = 0; j < devices.size(); j++)
			{
				cout << "\t " << (j + 1) << ") " << devices[j].getInfo<CL_DEVICE_NAME>() << ", version: " << devices[j].getInfo<CL_DEVICE_VERSION>();

				if (verbose_level > VERBOSE_BRIEF)
				{
					cout << ", vendor: " << devices[j].getInfo<CL_DEVICE_VENDOR>();
					cl_device_type device_type = devices[j].getInfo<CL_DEVICE_TYPE>();
					cout << ", type: ";
					if (device_type & CL_DEVICE_TYPE_DEFAULT)
						cerr << "DEFAULT ";
					if (device_type & CL_DEVICE_TYPE_CPU)
						cerr << "CPU ";
					if (device_type & CL_DEVICE_TYPE_GPU)
						cerr << "GPU ";
					if (device_type & CL_DEVICE_TYPE_ACCELERATOR)
						cerr << "ACCELERATOR ";
					cout << ", compute units: " << devices[j].getInfo<CL_DEVICE_MAX_COMPUTE_UNITS>();
				}

				if (verbose_level > VERBOSE_DETAILED)
				{
				}

				cout << endl;
			}
		}
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
	}
	}


	//select device
	cl::Device device;

	try
	{
		cl::Platform::get(&platforms);

		for (unsigned int i = 0; i < platforms.size(); i++)
		{
			vector<cl::Device> devices;
			platforms[i].getDevices((cl_device_type)CL_DEVICE_TYPE_ALL, &devices);

			for (unsigned int j = 0; j < devices.size(); j++)
			{
				if ((i == platform_id) && (j == device_id))
					device = devices[j];
				break;
			}
		}
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
	}

	cl::Context context({ device });

	cl::Program::Sources sources;

	// kernel calculates for each element C=A+B
	std::string kernel_code =
		"   void kernel simple_add(global const int* A, global const int* B, global int* C){       "
		"       int id = get_global_id(0);"
		"       C[id] = A[id] + B[id];                 "
		"   }                                                                               ";
	sources.push_back({ kernel_code.c_str(), kernel_code.length() });

	cl::Program program(context, sources);

	try
	{
		program.build({ device });
	}
	catch (cl::Error err) {
		cerr << "ERROR: " << err.what() << "(" << err.err() << ")" << endl;
	}

	//host buffers
	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int B[] = { 0, 1, 2, 0, 1, 2, 0, 1, 2, 0 };
	int C[sizeof(A)/sizeof(A[0])];

	// create buffers on the device
	cl::Buffer buffer_A(context, CL_MEM_READ_WRITE, sizeof(A));
	cl::Buffer buffer_B(context, CL_MEM_READ_WRITE, sizeof(B));
	cl::Buffer buffer_C(context, CL_MEM_READ_WRITE, sizeof(C));

	//create queue to which we will push commands for the device.
	cl::CommandQueue queue(context, device);

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