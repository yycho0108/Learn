#include "Net.h"
#include <string>
#include <iostream>
#include <fstream>

#define namedPrint(x) std::cout << #x << " : " << x << std::endl;

template<typename T>
void ask(std::string s, T& val){
	std::cout << s << " : " << std::endl;
	std::cin >> val;
	//std::cout << "RECEIVED : " << val << std::endl;
}
int main(){

	int lim;
	double rho, eps, decay;
	std::ifstream fin("params.txt");
	fin >> lim >> rho >> eps >> decay;
	fin.close();

	std::ofstream fout("loss.csv");

	char tune;
	ask("Tune?",tune);
	tune = std::tolower(tune);

	if(tune == 'y'){
		ask("lim", lim);
		ask("rho", rho);
		ask("eps", eps);
		ask("decay", decay);
	}

	namedPrint(lim);
	namedPrint(rho);
	namedPrint(eps);
	namedPrint(decay);
	
	Net<2,4,1> net(0.9);//(rho,eps,decay); //for learning rate & decay use default
	std::vector<double> X(2);
	std::vector<double> Y(1);

	auto start = clock();
	for(int i=0;i<lim;++i){
		XOR_GEN(X,Y);
		net.FF(X);
		net.BP(Y);
		fout << net.error() << std::endl;
	}
	fout.flush();
	fout.close();

	auto end = clock();
	printf("Took %f seconds\n", float(end-start)/CLOCKS_PER_SEC);
	for(int i=0;i<10;++i){
		XOR_GEN(X,Y);
		std::cout << X[0] << ',' << X[1] << ':' <<  Y[0] << '|' << net.FF(X)[0] << std::endl;
	}
}
