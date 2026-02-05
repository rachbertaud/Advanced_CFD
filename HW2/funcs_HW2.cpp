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
	
	//Read first line that specifies the number of inputs 
	std::getline(inputfile, line);
	int num_inputs;
	std::stringstream(line) >> num_inputs;

	double value;

	for(int i = 1; i <= (2*num_inputs); i++)
	{
		std::getline(inputfile,line);
		if(i % 2 == 0){
			std::stringstream(line) >> value;
			variables[var_name] = value;
		}
		else{
			std::stringstream(line) >> var_name;
		}
	}
}
