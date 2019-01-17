//a simple OpenCL kernel which adds two vectors A and B together into a third vector C
__kernel void add(__global const int* A, __global const int* B, __global int* C) {
	int id = get_global_id(0);
	C[id] = A[id] + B[id];
}

//a simple smoothing kernel averaging values in a local window (radius 1)
__kernel void avg_filter(__global const int* A, __global int* B) {
	int id = get_global_id(0);
	B[id] = (A[id - 1] + A[id] + A[id + 1])/3;
}

//a simple 2D kernel
__kernel void add2D(__global const int* A, __global const int* B, __global int* C) {
	int x = get_global_id(0);
	int y = get_global_id(1);
	int width = get_global_size(0);
	int height = get_global_size(1);
	int id = x + y*width;

	printf("id = %d x = %d y = %d w = %d h = %d\n", id, x, y, width, height);

	C[id]= A[id]+ B[id];
}
