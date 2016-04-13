#include <armadillo>
#include <vector>
#include <iostream>

#include <functional>
#include <ctime>
#include <random>
#include "Parser.h"


using namespace arma;
using namespace std;

double sigmoid(double x){
	return 1.0/(1.0 + exp(-x));
}
vec sigmoid(vec& v){
	return 1.0/(1.0 + exp(-v));
}
vec sigmoidPrime(vec& v, bool sig){
	if(sig)
		return v % (1.0-v);
	else{
		vec s = sigmoid(v);
		return s % (1.0-s);
	}
}

class Layer{
private:
	int n; //size
	vec _I,_O,_G;
public:
	Layer(int n);
	~Layer();
	void transfer(vec);
	vec& I();
	vec& O();
	vec& G();
	int size();
};

Layer::Layer(int n):n(n){
	_I.set_size(n);
	_O.set_size(n);
	_G.set_size(n);
}
Layer::~Layer(){

}

void Layer::transfer(vec v){
	_I.swap(v);
	//_O = _I;
	_O = sigmoid(_I);
	//cout << "I" << arma::size(_I) << endl;
	//cout << "O" << arma::size(_O) << endl;
//	_O.for_each([](mat::elem_type& val){val = sigmoid(val);});
	//return _O;
	//_I.for_each([]())
}
vec& Layer::I(){
	return _I;
}
vec& Layer::O(){
	return _O;
}
vec& Layer::G(){
	return _G;
}
class Net{
private:
	std::vector<int> t; //topology
	std::vector<mat> W;
	std::vector<Layer> L; //layers
	std::vector<vec> B; //biases
public:
	std::vector<double> FF(std::vector<double> X);
	void BP(std::vector<double> Y);
	Net(std::vector<int> t);
	void save(std::string f);
	void load(std::string f);
};
Net::Net(std::vector<int> t):t(t){
	arma_rng::set_seed_random(); 
	for(size_t i=1;i<t.size();++i){
		W.push_back(arma::randn<mat>(t[i],t[i-1]));
		B.push_back(arma::randn<vec>(t[i]));
	}
	for(auto& e : t){
		L.push_back(Layer(e));
	}
}
std::vector<double> Net::FF(std::vector<double> X){
	L.front().O() = X;
	for(size_t i=1;i<t.size();++i){
		L[i].transfer(W[i-1]*L[i-1].O() + B[i-1]);	
	}
	return arma::conv_to<std::vector<double>>::from(L.back().O());
}
void Net::BP(std::vector<double> Y){
	L.back().G() = vec(Y) - L.back().O();
	for(size_t i = t.size()-2;i>=1;--i){
		L[i].G() = W[i].t() * L[i+1].G() % sigmoidPrime(L[i].O(),true);
	}
	for(size_t i=1;i<t.size();++i){
		W[i-1] += 0.6 * L[i].G() * L[i-1].O().t();
		B[i-1] += 0.6 * L[i].G();
	}
}

void Net::save(std::string f){
	for(size_t i=0;i<W.size();++i){
		W[i].save(f + "_W_" + std::to_string(i));
	}
	for(size_t i=0;i<B.size();++i){
		B[i].save(f + "_B_" + std::to_string(i));
	}
}
void Net::load(std::string f){
	for(size_t i=0;i<W.size();++i){
		W[i].load(f + "_W_" + std::to_string(i));
	}
	for(size_t i=0;i<B.size();++i){
		B[i].load(f + "_B_" + std::to_string(i));
	}
}
double randNum(){
	static auto _randNum = std::bind(std::uniform_real_distribution<double>(0.0,1.0),std::default_random_engine(time(0))); //random
	return _randNum();
}

void XOR_GEN(std::vector<double>& X, std::vector<double>& Y){
	X[0] = randNum()>0.5?1:0;
	X[1] = randNum()>0.5?1:0;
	Y[0] = int(X[0]) ^ int(X[1]);
}

int test_XOR(int argc, char* argv[]){
	int lim = 1000;
	if(argc != 1){
		lim = std::atoi(argv[1]);
	}
	std::vector<int> t({2,4,1});
	Net net(t);
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
void load(Net& net){
	std::cout << "LOAD? (Y/N)" << std::endl;
	char load;
	std::cin >> load;
	if(load == 'Y' || load == 'y'){
		net.load("save/Net");
	}
}
void save(Net& net){
	std::cout << "SAVE? (Y/N)" << std::endl;
	char save;
	std::cin >> save;
	if(save == 'Y' || save == 'y'){
		net.save("save/Net");
	}
}
void train(Net& net, int n){
	std::vector<double> X(28*28);
	std::vector<double> Y(10);
	
	Parser trainer("data/trainData","data/trainLabel");

	for(int i=0;i<n;++i){
		while(trainer.parseInput(X,Y)){
			net.FF(X);
			net.BP(Y);
		}
		trainer.reset();
	}
}
void test(Net& net){
	std::vector<double> X(28*28);
	std::vector<double> Y(10);
	Parser tester("data/testData","data/testLabel");
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

	std::vector<int> t({28*28,hSize,10});

	Net net(t);
	
	load(net);
	
	train(net,numTrain);
	
	test(net);
	
	save(net);

	return 0;
}
