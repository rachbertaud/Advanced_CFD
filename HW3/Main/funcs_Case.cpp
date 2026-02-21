#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_Case.h"

//---------------------------CASE FUNCTIONS----------------------------------------------

void read_inputs_case(std::map<std::string, double>& variables)
{
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
			variables[var_name] = value;
		}
		
		i++;
	}

	inputfile.close();
}




void readCase(caseType& Case){
	
	std::map<std::string, double> var;
	read_inputs_case(var);			//reads inputs and puts them in the map

	Case.rho = var["rho"];
	Case.cp = var["cp"];
	Case.k = var["k"];
	Case.Ts = var["Ts"];
	Case.Tn = var["Tn"];
	Case.A = var["A"];
	Case.bx = var["bx"];
	Case.by = var["by"];
	Case.src = int(var["src"]);
	
	//map falls out of scope and is automatically cleaned
}

void dispCase(const caseType& Case){
	std::cout << "---------------------------CASE INPUTS--------------------------" << std::endl;
	std::cout << "Rho : " << Case.rho << " (density of air kg/m^3)" << std::endl;
	std::cout << "Cp : " << Case.cp << " (heat capacity of air J/(kg K))" << std::endl;
	std::cout << "k : " << Case.k << " (thermal conductivity W/(m K))" << std::endl;
	std::cout << "Ts : " << Case.Ts << " (south wall temperature K)" << std::endl;
	std::cout << "Tn : " << Case.Tn << " (noth wall temperature K)" << std::endl;
	std::cout << "A : " << Case.A << " (velocity amplitude m/s)" << std::endl;
	std::cout << "bx : " << Case.bx << " (flow parameter)" << std::endl;
	std::cout << "by : " << Case.by << " (flow parameter)" << std::endl; 
	std::cout << "src : " << Case.src << " (source flag term)" << std::endl; 
	std::cout << "----------------------------------------------------------------" << std::endl; 
}

