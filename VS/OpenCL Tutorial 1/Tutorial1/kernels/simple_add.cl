__kernel void simple_add(__global const int* A, __global const int* B, __global int* C)
{
	int id = get_global_id(0);
	C[id] = A[id] + B[id];
}

__kernel void simple_mult(__global const int* A, __global const int* B, __global int* C)
{
	int id = get_global_id(0);
	C[id] = A[id] * B[id];
}

__kernel void simple_addmult(__global const int* A, __global const int* B, __global int* C)
{
	int id = get_global_id(0);
	C[id] = A[id] * B[id] + B[id];
}
