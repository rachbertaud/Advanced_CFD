#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout
#include <cmath>

#include "Header_Robin.h"

//---------------------------MESH FUNCTIONS----------------------------------------------

void BC::read()
{
	std::map<std::string, double> var;
	
	//define a string 
	std::string line;
	std::string var_name;

	//open the input file 
	std::ifstream inputfile;
	
	inputfile.open("BC.inp");

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

	k = var["k"];
	h = var["h"];
	Tx = var["Tx"];
	Td = var["Td"];
	s1 = var["s1"];
	s2 = var["s2"];
	n1 = var["n1"];
	n2 = var["n2"];
	w1 = var["w1"];
	w2 = var["w2"];
}

void BC::disp() const{
    std::cout << "---------------------------BC INPUTS---------------------------" << std::endl;
    std::cout << "k  : " << k  << " (Thermal conductivity of air)" << std::endl;
    std::cout << "h  : " << h  << " (Heat Transfer coefficient of windows)" << std::endl;
    std::cout << "Tx : " << Tx << " (Temperature External)" << std::endl;
    std::cout << "Td : " << Td << " (Temperature of Door)" << std::endl;
    std::cout << "n1 : " << n1 << " | n2 : " << n2 << " (Window coordinates - North)" << std::endl;
    std::cout << "w1 : " << w1 << " | w2 : " << w2 << " (Window coordinates - West)" << std::endl;
    std::cout << "s1 : " << s1 << " | s2 : " << s2 << " (Door coordinates - South)" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
}

void BC::W(double x, double y, double t, double& a, double& b, double& g) const
{
    if(y >= w1 && y <= w2)
    {
      a = h;
      b = k;
      g = h*(std::cos(x)*std::cos(y) + std::sin(x)*std::cos(y));
    }
    else
     {
       a = 0;
       b = 1;
       g = std::sin(x)*std::cos(y);
     }
}

void BC::E(double x, double y, double t, double& a, double& b, double& g) const
{
	a = 0;
	b = 1;
	g = -std::sin(x)*std::cos(y);
}

void BC::S(double x, double y, double t, double& a, double& b, double& g) const
{
    if(x >= s1 && x <= s2)
    {
      a = 1;
      b = 0;
      g = std::cos(x)*std::cos(y);
    }
    else
    {
      a = 0;
      b = 1;
      g = std::cos(x)*std::sin(y);
    }
}

void BC::N(double x, double y,  double t, double& a, double& b, double& g) const
{
    if(x >= n1 && x <= n2)
    {
      a = h;
      b = k;
      g = h*(std::cos(x)*std::cos(y) - std::cos(x)*std::sin(y));
    }
    else
    {
      a = 0;
      b = 1;
      g = -std::cos(x)*std::sin(y);
    }
}

