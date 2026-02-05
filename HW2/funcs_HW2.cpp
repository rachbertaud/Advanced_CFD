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
