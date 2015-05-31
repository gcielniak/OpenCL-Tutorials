#include <iostream>
#include <vector>
#include <string>
#ifdef __APPLE__
    #include "OpenCL/opencl.h"
#else
    #include "CL/cl.h"
#endif

std::string GetPlatformName (cl_platform_id id)
{
	size_t size = 0;
	clGetPlatformInfo (id, CL_PLATFORM_NAME, 0, nullptr, &size);

	std::string result;
	result.resize (size);
	clGetPlatformInfo (id, CL_PLATFORM_NAME, size,
		const_cast<char*> (result.data ()), nullptr);

	return result;
}

std::string GetDeviceName (cl_device_id id)
{
	size_t size = 0;
	clGetDeviceInfo (id, CL_DEVICE_NAME, 0, nullptr, &size);

	std::string result;
	result.resize (size);
	clGetDeviceInfo (id, CL_DEVICE_NAME, size,
		const_cast<char*> (result.data ()), nullptr);

	return result;
}

void CheckError(cl_int error)
{
	if (error != CL_SUCCESS) {
		std::cerr << "OpenCL call failed with error " << error << std::endl;
		std::exit (1);
	}
}

int main()
{
	cl_uint platformIdCount = 0;
	cl_uint deviceIdCount = 0;
	cl_int platform = 0;
	cl_int device = 0;

	clGetPlatformIDs (0, nullptr, &platformIdCount);

	std::cout << "Found " << platformIdCount << " platform(s)" << std::endl;

	std::vector<cl_platform_id> platformIds (platformIdCount);
	clGetPlatformIDs (platformIdCount, platformIds.data (), nullptr);
	if (platformIdCount)
		platform = 0;

	for (cl_uint i = 0; i < platformIdCount; ++i) 
	{
		std::cout << "\t (" << (i+1) << ") : " << GetPlatformName (platformIds [i]) << std::endl;

		clGetDeviceIDs (platformIds[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceIdCount);
		std::cout << "\t\tFound " << deviceIdCount << " device(s)" << std::endl;

		std::vector<cl_device_id> deviceIds (deviceIdCount);
		clGetDeviceIDs (platformIds[i], CL_DEVICE_TYPE_ALL, deviceIdCount,	deviceIds.data (), nullptr);

		if 	(platform == i)
			device = 0;

		for (cl_uint j = 0; j < deviceIdCount; ++j)
			std::cout << "\t\t (" << (j+1) << ") : " << GetDeviceName (deviceIds[j]) << std::endl;
	}

	if ((platform < 0) || (device < 0))
	{
		std::cerr << "No compatible OpenCL device detected." << std::endl;
		return 0;
	}

	const cl_context_properties contextProperties [] =
	{
		CL_CONTEXT_PLATFORM,
		reinterpret_cast<cl_context_properties> (platformIds[platform]),
		0, 0
	};
	
	cl_int error;

	clGetDeviceIDs (platformIds[platform], CL_DEVICE_TYPE_ALL, 0, nullptr, &deviceIdCount);
	std::vector<cl_device_id> deviceIds (deviceIdCount);
	clGetDeviceIDs (platformIds[platform], CL_DEVICE_TYPE_ALL, deviceIdCount,	deviceIds.data (), nullptr);

	cl_context context = clCreateContext(contextProperties, deviceIdCount,	deviceIds.data (), nullptr,
		nullptr, &error);

	CheckError(error);

	cl_command_queue queue = clCreateCommandQueue (context, deviceIds[device], 0, &error);
	
	CheckError (error);
	
	clReleaseCommandQueue (queue);
	clReleaseContext (context);

	return 0;
}