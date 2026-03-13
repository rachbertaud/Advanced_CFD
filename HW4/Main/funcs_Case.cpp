#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_Case.h"

//---------------------------CASE FUNCTIONS----------------------------------------------

void caseType::read()
{
	std::map<std::string, double> var;

	//define a string 
	std::string line;
	std::string var_name;

	//open the input file 
	std::ifstream inputfile;
	
	inputfile.open("Case.inp");

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
			var[var_name] = value;
		}
		
		i++;
	}

	inputfile.close();


	rho = var["rho"];
	cp = var["cp"];
	k = var["k"];
	A = var["A"];
	bx = var["bx"];
	by = var["by"];
	src = int(var["src"]);
	
	//map falls out of scope and is automatically cleaned
}

void caseType::disp() const{
	std::cout << "---------------------------CASE INPUTS--------------------------" << std::endl;
	std::cout << "Rho : " << rho << " (density of air kg/m^3)" << std::endl;
	std::cout << "Cp : " << cp << " (heat capacity of air J/(kg K))" << std::endl;
	std::cout << "k : " << k << " (thermal conductivity W/(m K))" << std::endl;
	std::cout << "A : " << A << " (velocity amplitude m/s)" << std::endl;
	std::cout << "bx : " << bx << " (flow parameter)" << std::endl;
	std::cout << "by : " << by << " (flow parameter)" << std::endl; 
	std::cout << "----------------------------------------------------------------" << std::endl; 
}

