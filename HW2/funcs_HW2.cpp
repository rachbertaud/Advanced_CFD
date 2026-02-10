#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout
#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include "HW2.h"

void read_inputs(std::map<std::string, double>& variables)
{
	//define a string 
	std::string line;
	std::string var_name;

	//open the input file 
	std::ifstream inputfile;
	inputfile.open("inputs");
	

	double value;
	int i = 0;
	
	while(std::getline(inputfile, line))
	{
		if(line=="endfile") break;
		
		if(i % 2 == 0){
			std::stringstream(line) >> var_name;
		}
		else{
			std::stringstream(line) >> value;
			variables[var_name] = value;
		}
		
		i++;
	}

	inputfile.close();
}

double var_therm_cond(double x, double y){

	double km; 
	km = 1 + 0.5*std::sin(x)*std::sin(y);
	
	return km;
}
