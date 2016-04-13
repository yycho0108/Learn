#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

int SIZE = 10000;

int main(int argc, char* argv[]){

	if(argc != 1){
		SIZE = std::atoi(argv[1]);
	}

	int* a = new int[SIZE];
	int* b = new int[SIZE];
	int* c = new int[SIZE];

	for(int i=0;i<SIZE;++i){
		a[i]=b[i]=i;
		c[i]=0;
	}

	auto start = clock();

	for(int i=0;i<SIZE;++i){
		c[i] = a[i] + b[i];
	}

	auto end = clock();
	printf("Took %f Seconds", (end-start)/float(CLOCKS_PER_SEC));


	delete[] a;
	delete[] b;
	delete[] c;
}
