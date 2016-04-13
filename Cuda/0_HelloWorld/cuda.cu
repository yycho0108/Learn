#include <stdio.h>
#include <time.h>

__global__ void vAdd(int* a, int* b, int* c, int n){
	int i = threadIdx.x;
	if(i<n)
		c[i] = a[i] + b[i];
}

void wrapper(int* a, int* b, int* c, int n){
	
	int *d_a,*d_b,*d_c;

	cudaMalloc(&d_a,n*sizeof(int));
	cudaMalloc(&d_b,n*sizeof(int));
	cudaMalloc(&d_c,n*sizeof(int));

	cudaMemcpy(d_a,a,n * sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,n * sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_c,c,n * sizeof(int),cudaMemcpyHostToDevice);

	clock_t start = clock();
	vAdd<<< 1,n >>>(d_a,d_b,d_c,n);
	clock_t end = clock();
	printf("Took %f Seconds", float(end-start)/CLOCKS_PER_SEC);

	//cudaMemcpy(a,d_a,n*sizeof(int),cudaMemcpyDeviceToHost);
	//cudaMemcpy(b,d_b,n*sizeof(int),cudaMemcpyDeviceToHost);
	cudaMemcpy(c,d_c,n*sizeof(int),cudaMemcpyDeviceToHost);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return;
}
