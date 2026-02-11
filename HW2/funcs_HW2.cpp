#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout
#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include "HW2.h"

void read_inputs(std::map<std::string, double>& variables, int input_flag)
{
	//define a string 
	std::string line;
	std::string var_name;

	//open the input file 
	std::ifstream inputfile;
	if(input_flag == 1)
	{
		inputfile.open("inputs_error");
	}
	else if(input_flag == 2)
	{
		inputfile.open("inputs_base");
	}
	else
	{
		inputfile.open("inputs");
	}
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


double find_r(double x, double y, double Lx, double Ly){

        double r;

        double x_diff = std::pow((x - (Lx/2)), 2);
	double y_diff = std::pow((y - (Ly/2)),2);

        r = std::sqrt(x_diff + y_diff);	
	//std::cout << "r = " << r << "(x, y) : " << x << ", " << y << std::endl;	
	return r;
}

double fuel_therm_cond(double x, double y, double Lx, double Ly, double R1, double R2, double k1, double k2, double k3){
	

	double r = find_r(x, y, Lx, Ly);
	
	double k = k3; 

	if ( r < R1 )
	{
		k = k1;
	}
	else if ( r < R2 )
	{
		k = k2;
	}

	return k;

}

double source(double r, double a, double b, double R1){
	
	double source_val = a*(1 + b*(std::pow((r/R1),2)));

	if ( r > R1 ) {
		source_val = 0;
	}

	return source_val;
}
