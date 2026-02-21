#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_Mesh.h"

//---------------------------MESH FUNCTIONS----------------------------------------------

void read_inputs_mesh(std::map<std::string, double>& variables)
{
	//define a string 
	std::string line;
	std::string var_name;

	//open the input file 
	std::ifstream inputfile;
	
	inputfile.open("Mesh.inp");

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




void readMesh(meshType& Mesh){
	
	std::map<std::string, double> var;
	read_inputs_mesh(var);			//reads inputs and puts them in the map

	Mesh.Nx = var["Nx"];
	Mesh.Ny = var["Ny"];
	Mesh.Lx = var["Lx"];
	Mesh.Ly = var["Ly"];
	
	//map falls out of scope and is automatically cleaned
}

void createMesh(meshType& Mesh){
	Mesh.dx = Mesh.Lx/Mesh.Nx;
	Mesh.dy = Mesh.Ly/Mesh.Ny;
	
	Mesh.xc.resize(Mesh.Nx + 2);
	Mesh.xf.resize(Mesh.Nx + 1);
	Mesh.yc.resize(Mesh.Ny + 2);
	Mesh.yf.resize(Mesh.Ny + 1);

	double dx = Mesh.dx;
	double dy = Mesh.dy;
	int Nx = Mesh.Nx;
	int Ny = Mesh.Ny;

	// computing face locations 
	for(int i = 0; i <= Nx; i++)
	{
		Mesh.xf[i] = dx*i;
	}
	
	// computing cell centered loations
	for(int i = 0; i <= (Nx + 1); i++)
	{
		Mesh.xc[i] = -dx*0.5 + dx*i;
	}

        // computing face locations
        for(int i = 0; i <= Ny; i++)
        {
                Mesh.yf[i] = dy*i;
        }

        // computing cell centered loations
        for(int i = 0; i <= (Ny + 1); i++)
        {
                Mesh.yc[i] = -dy*0.5 + dy*i;
        }
}	
		

void dispMesh(const meshType& Mesh){
	std::cout << "---------------------------MESH INPUTS--------------------------" << std::endl;
	std::cout << "Nx : " << Mesh.Nx << " (Number of cells in x)" << std::endl;
	std::cout << "Ny : " << Mesh.Ny << " (Number of cells  in y)" << std::endl;
	std::cout << "Lx : " << Mesh.Lx << " (Length of domain in x m)" << std::endl;
	std::cout << "Ly : " << Mesh.Ly << " (Length of domain in y m)" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl; 
}

void writeMesh(const meshType& Mesh){
	std::ofstream xfile; 
	std::ofstream yfile; 
	xfile.open("xc.dat");
	yfile.open("yc.dat");

	for (int i = 0; i < (Mesh.Nx + 2); i++)
	{
		xfile << Mesh.xc[i] << "\n";
	}		
	
	for (int i = 0; i < (Mesh.Ny + 2); i ++)
	{
		yfile << Mesh.yc[i] << "\n";
	}

	xfile.close();
	yfile.close();
}
