#include <armadillo>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace arma;

mat sigmoid(mat& m){
	return 1.0/(1.0 + exp(-m));
}

class ConvLayer{
private:
	int d_i, d_o; //depth of input layers, depth of output layers
	bool** connection;
	
	std::vector<mat> W;
	std::vector<mat> b;

	std::vector<mat> _I;
	std::vector<mat> _O;
	std::vector<mat> _G;
	

public:
	ConvLayer(int,int);
	~ConvLayer();
	std::vector<mat>& transfer(std::vector<mat> I);
};

ConvLayer::ConvLayer(int d_i, int d_o):d_i(d_i),d_o(d_o){
	connection = new bool*[d_i];
	for(int i=0;i<d_i;++i){
		connection[i] = new bool[d_o];
	}
	for(int o=0;o<d_o;++o){
		W[o] = randu(5,5);
	}
}
ConvLayer::~ConvLayer(){

	for(int i=0;i<d_i;++i){
		delete connection[i];
	}
	delete[] connection;

}
std::vector<mat>& ConvLayer::transfer(std::vector<mat> I){
	_I.swap(I);

	for(int i=0;i<d_i;++i){
		for(int o=0;o<d_i;++o){
			if(connection[i][o]){
				_O[o] += conv2(_I[i],W[o],"same");
			}
		}
	}
	// subsample...
	
	for(int o=0;o<d_i;++o){
		_O[o] += b[o];
		_O[o] = sigmoid(_O[o]);
	}
	return _O;
}

int main(){
	return 0;
}
