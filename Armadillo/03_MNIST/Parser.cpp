#include "Parser.h"

/* ***** Utility Functions ***** */
double ETA = 0.15;
double ALPHA = 0.3;
using BYTE = unsigned char;



//FOR MNIST DATA SET
//
//
Parser::Parser(std::string dat, std::string lab){
	f_data.open(dat);
	f_label.open(lab);
	//skip metadata
	BYTE buf[16];
	f_data.read((char*)buf,16);
	f_label.read((char*)buf,8);
	//skip metadata
}

Parser::~Parser(){
	f_data.close();
	f_label.close();
}

void Parser::reset(){	
	f_data.clear();
	f_data.seekg(16,std::ios::beg);
	f_label.clear();
	f_label.seekg(8,std::ios::beg);
}

bool Parser::parseInput(std::vector<double>& X,std::vector<double>& Y){
	X.resize(IMGSIZE);
	Y.resize(10);
	
	BYTE buf_dat[IMGSIZE];
	BYTE buf_lab;

	f_data.read((char*)buf_dat,IMGSIZE);
	f_label.read((char*)&buf_lab,1);

	for(int i=0;i<IMGSIZE;++i){
		X[i] = (buf_dat[i] / 256.0);
	}
	for(int i=0;i<10;++i){
		Y[i]=0.0;
	}
	Y[buf_lab] = 1.0; // probability 100%, others 0%
	return f_data && f_label;
	//return std::make_pair(res_dat,res_lab);
}

void visualize(std::vector<double>& input){
	for(int i=0;i<28;++i){
		for(int j=0; j<28; ++j){
			std::cout << (input[i*28+j]>0.5?1:0);
		}
		std::cout << std::endl;
	}
}
