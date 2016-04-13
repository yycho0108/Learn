#include <armadillo>
#include <iostream>
#include <fstream>
#include <ctime>


int K_START_LIM = 1;
int K_END_LIM = 10;

int M_START_LIM = 1;
int M_END_LIM = 10;

using namespace arma;
using namespace std;
mat fftconv2(mat A, mat B){//B = kernel
	
	auto M = A.n_rows;
	auto N = A.n_cols;
	
	auto U = B.n_rows;
	auto V = B.n_cols;
		
	//FFT-based
	A.resize(M+U-1,N+V-1);
	B.resize(M+U-1,N+V-1);

	cx_mat A_ = fft2(A);
	cx_mat B_ = fft2(B);


	mat C_ = abs(ifft2(A_%B_));
	C_ = C_.submat(U/2, V/2,M + U/2-1, N + V/2-1);

	return C_;

}

int main(int argc, char* argv[]){

	if(argc == 5){
		M_START_LIM = std::atoi(argv[1]);
		M_END_LIM = std::atoi(argv[2]);
		K_START_LIM = std::atoi(argv[3]);
		K_END_LIM = std::atoi(argv[4]);
	}

	std::ofstream fout("/dev/null");//dummy

	//test plain convolution
	auto start = clock();
	for(int M=M_START_LIM;M<M_END_LIM;++M){
		for(int N=M_START_LIM;N<M_END_LIM;++N){
			for(int U=K_START_LIM;U<K_END_LIM;++U){
				for(int V=K_START_LIM;V<K_END_LIM;++V){
					mat A(M,N,fill::randu);
					mat B(U,V,fill::randu);

					mat C = conv2(A,B,"same");	
					fout << C.n_cols << endl;
				}
			}
		}
	}
	auto end = clock();
	std::cout << "TOOK : " << float(end-start)/CLOCKS_PER_SEC << "SECONDS" << std::endl;



	start = clock();
	for(int M=M_START_LIM;M<M_END_LIM;++M){
		for(int N=M_START_LIM;N<M_END_LIM;++N){
			for(int U=K_START_LIM;U<K_END_LIM;++U){
				for(int V=K_START_LIM;V<K_END_LIM;++V){
					mat A(M,N,fill::randu);
					mat B(U,V,fill::randu);

					mat C = fftconv2(A,B);	
					fout << C.n_cols << endl;
				}
			}
		}
	}
	end = clock();
	std::cout << "TOOK : " << float(end-start)/CLOCKS_PER_SEC << "SECONDS" << std::endl;
}
