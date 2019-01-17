//a simple OpenCL kernel which copies all pixels from A to B
__kernel void identity(__global const uchar4* A, __global uchar4* B) {
	int id = get_global_id(0);
	B[id] = A[id];
}

//simple 2D identity kernel
__kernel void identity2D(__global const uchar4* A, __global uchar4* B) {
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0); //width in pixels
	int id = x + y*width;
	B[id] = A[id];
}

//2D averaging filter
__kernel void avg_filter2D(__global const uchar4* A, __global uchar4* B) {
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0); //width in pixels
	int id = x + y*width;

	uint4 result = (uint4)(0);//zero all 4 components

	for (int i = (x-1); i <= (x+1); i++)
	for (int j = (y-1); j <= (y+1); j++) 
		result += convert_uint4(A[i + j*width]); //convert pixel values to uint4 so the sum can be larger than 255

	result /= (uint4)(9); //normalise all components (the result is a sum of 9 values) 

	B[id] = convert_uchar4(result); //convert back to uchar4 
}

//2D 3x3 convolution kernel
__kernel void convolution2D(__global const uchar4* A, __global uchar4* B, __constant float* mask) {
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0); //width in pixels
	int id = x + y*width;

	float4 result = (float4)(0.0f,0.0f,0.0f,0.0f);//zero all 4 components

	for (int i = (x-1); i <= (x+1); i++)
	for (int j = (y-1); j <= (y+1); j++)
		result += convert_float4(A[i + j*width])*(float4)(mask[i-(x-1) + (j-(y-1))*3]);//convert pixel and mask values to float4

	B[id] = convert_uchar4(result); //convert back to uchar4
}
