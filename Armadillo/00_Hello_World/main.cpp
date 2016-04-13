#include <armadillo>
#include <iostream>

using namespace arma;

int main(){
	mat A;
	A << 1.0 << 2.0 << endr
		<< 2.0 << 3.0 << endr
		<< 1.0 << 3.0 << endr;
	mat B = arma::trans(A);

	std::cout << A << std::endl;
	std::cout << B << std::endl;
	std::cout << A.t()*A << std::endl;

	return 0;
}
