#include <armadillo>
#include <vector>
#include <iostream>

#include <functional>
#include <ctime>
#include <random>

#include "Parser.h"
#include "Net.h"


using namespace arma;
using namespace std;


using _Net_ = Net<28*28,75,10>;


int test_XOR(int argc, char* argv[]){
	int lim = 1000;
	if(argc != 1){
		lim = std::atoi(argv[1]);
	}
	_Net_ net;
	std::vector<double> X(2);
	std::vector<double> Y(1);

	auto start = clock();
	for(int i=0;i<lim;++i){
		XOR_GEN(X,Y);
		net.FF(X);
		net.BP(Y);
	}
	auto end = clock();
	printf("Took %f seconds", float(end-start)/CLOCKS_PER_SEC);
	for(int i=0;i<10;++i){
		XOR_GEN(X,Y);
		std::cout << X[0] << ',' << X[1] << ':' <<  Y[0] << '|' << net.FF(X)[0] << std::endl;
	}
	return 0;
}

template<typename T>
void print(std::vector<T> v){
	for(auto i : v){
		std::cout << i << ' ';
	}
	std::cout << std::endl;
}

int maxIndex(std::vector<double> v){
	double cmax = -100;
	int index = 0;
	int n = v.size();
	for(int i=0;i<n;++i){
		if(cmax < v[i]){
			cmax = v[i];
			index = i;
		}
	}
	return index;
}
void load(_Net_& net){
	std::cout << "LOAD? (Y/N)" << std::endl;
	char load;
	std::cin >> load;
	if(load == 'Y' || load == 'y'){
		net.load("save/_Net_");
	}
}
void save(_Net_& net){
	std::cout << "SAVE? (Y/N)" << std::endl;
	char save;
	std::cin >> save;
	if(save == 'Y' || save == 'y'){
		net.save("save/_Net_");
	}
}
void train(_Net_& net, int n){
	std::vector<double> X(28*28);
	std::vector<double> Y(10);

	std::ofstream fout("loss.csv");
	
	Parser trainer("../data/trainData","../data/trainLabel");

	int step=0;

	for(int i=0;i<n;++i){
		while(trainer.parseInput(X,Y)){
			if(++step%100==0)
				std::cout << "TRAINING ... " << step << std::endl;
			net.FF(X);
			net.BP(Y);
			fout << net.error() << std::endl;
		}
		trainer.reset();
	}

}
void test(_Net_& net){
	std::vector<double> X(28*28);
	std::vector<double> Y(10);
	Parser tester("../data/testData","../data/testLabel");
	int right = 0;
	int wrong = 0;	
	while(tester.parseInput(X,Y)){
		if(maxIndex(net.FF(X)) == maxIndex(Y)){
			++right;
		}else{
			++wrong;
		}
	}
	printf("%d right, %d wrong\n", right,wrong);
}

int main(int argc, char* argv[]){
	int hSize = 15; //default hidden layer size
	int numTrain = 1;

	if(argc > 1){
		hSize = std::atoi(argv[1]);
	}
	if(argc > 2){
		numTrain = std::atoi(argv[2]);
	}


	_Net_ net;
	
	load(net);
	
	train(net,numTrain);
	
	test(net);
	
	save(net);

	return 0;
}
