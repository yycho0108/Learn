#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include <iostream>

int SIZE = 10000;

extern void wrapper(int* a, int* b, int* c, int n);

int main(int argc, char* argv[]){

	if(argc != 1){
		SIZE = std::atoi(argv[1]);
	}

	int *a,*b,*c;

	a = (int*)malloc(SIZE*sizeof(int));
	b = (int*)malloc(SIZE*sizeof(int));
	c = (int*)malloc(SIZE*sizeof(int));

	for(int i=0;i<SIZE;++i){
		a[i]=b[i]=i;
		c[i]=0;
	}

	wrapper(a,b,c,SIZE);

	//for(int i=0;i<SIZE;++i){
	//	printf("%d,", c[i]);
	//}

	free(a);
	free(b);
	free(c);

	return 0;
}
