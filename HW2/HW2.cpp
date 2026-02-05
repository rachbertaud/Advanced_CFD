#include <fstream>	// needed for file writing
#include <iostream> 	// needed for cout
#include <string> 	// needed for string 
#include <map>		// for variable map definition
#include "HW2.h"	// for user-defined functions
#include <vector>	// needed for vectors


int main()
{
	std::map<std::string, double> var;

	read_inputs(var);

	std::cout << "--------INPUTS---------" << std::endl;
	for(const auto& pair : var)
	{
    		std::cout << pair.first << " = " << pair.second << std::endl;
	}
	
	// defining dx and dy with user inputs 
	double dx = var["Lx"] / var["Nx"];
	double dy = var["Ly"] / var["Ny"];
	
	// defining x-domain vector spaces
	std::vector<double> xf(var["Nx"] + 1); // face locations
	std::vector<double> x(var["Nx"] + 2); // cell-centered locations
	
	// computing face locations 
	for(int i = 0; i <= var["Nx"]; i++)
	{
		xf[i] = dx*i;
	}
	
	// computing cell centered loations
	for(int i = 0; i <= (var["Nx"] + 1); i++)
	{
		x[i] = -dx*0.5 + dx*i;
	}

        // defining y-domain vector spaces
        std::vector<double> yf(var["Ny"] + 1); // face locations
        std::vector<double> y(var["Ny"] + 2); // cell-centered locations

        // computing face locations
        for(int i = 0; i <= var["Ny"]; i++)
        {
                yf[i] = dy*i;
        }

        // computing cell centered loations
        for(int i = 0; i <= (var["Ny"] + 1); i++)
        {
                y[i] = -dy*0.5 + dy*i;
        }
	
	std::ofstream xfile; 
	std::ofstream yfile; 
	xfile.open("x.dat");
	yfile.open("y.dat");

	for (int i = 0; i < (var["Nx"] + 2); i++)
	{
		xfile << x[i] << "\n";
	}		
	
	for (int i = 0; i < (var["Ny"] + 2); i ++)
	{
		yfile << y[i] << "\n";
	}

	xfile.close();
	yfile.close();
}
