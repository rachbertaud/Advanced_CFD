#include <iostream> 	//needed for cout
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include "HW2.h"


int main()
{
	std::map<std::string, double> variables;

	read_inputs(variables);

	double Nx = variables["Nx"];
	double Ny = variables["Ny"];
	double Lx = variables["Lx"];

	std::cout << "--------INPUTS---------" << std::endl;
	for(const auto& pair : variables)
	{
    		std::cout << pair.first << " = " << pair.second << std::endl;
	}	
}
