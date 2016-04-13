#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>


#define IMGSIZE (28*28)

extern double ETA, ALPHA; // GLOBALS

struct Parser{
	std::ifstream f_data,f_label;
	Parser(std::string f_d, std::string f_l); //data, label
	~Parser();
	void reset();
	bool parseInput(std::vector<double>& X,std::vector<double>& Y);
};

void visualize(std::vector<double>& input);

#endif
