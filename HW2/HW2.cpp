#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout
#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include "HW2.h"


int main()
{
	std::map<std::string, double> variables;

	read_inputs(variables);

	double Nx = variables["Nx"];
	double Ny = variables["Ny"];
	std::cout << "NX,NY = " << Nx << " , " << Ny << std::endl;
	
}
