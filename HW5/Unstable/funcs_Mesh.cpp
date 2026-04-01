#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_Mesh.H"

//---------------------------MESH FUNCTIONS----------------------------------------------

meshType::meshType()
{
	std::string filename = "Mesh.inp";
	reader(filename, var);
	set();
  disp();
  write();
}	

void meshType::set()
{
	Nx = var["Nx"];
	Ny = var["Ny"];
	Lx = var["Lx"];
	Ly = var["Ly"];
	
	//map falls out of scope and is automatically cleaned

	dx = Lx/Nx;
	dy = Ly/Ny;
	
	xc.resize(Nx + 2);
	xf.resize(Nx + 1);
	yc.resize(Ny + 2);
	yf.resize(Ny + 1);

	// computing face locations 
	for(int i = 0; i <= Nx; i++)
	{
		xf[i] = dx*i;
	}
	
	// computing cell centered loations
	for(int i = 0; i <= (Nx + 1); i++)
	{
		xc[i] = -dx*0.5 + dx*i;
	}

  // computing face locations
  for(int i = 0; i <= Ny; i++)
  {
          yf[i] = dy*i;
  }

  // computing cell centered loations
  for(int i = 0; i <= (Ny + 1); i++)
  {
          yc[i] = -dy*0.5 + dy*i;
  }
}

void meshType::disp() const{
	std::cout << "---------------------------MESH INPUTS--------------------------" << std::endl;
	std::cout << "Nx : " << Nx << " (Number of cells in x)" << std::endl;
	std::cout << "Ny : " << Ny << " (Number of cells  in y)" << std::endl;
	std::cout << "Lx : " << Lx << " (Length of domain in x m)" << std::endl;
	std::cout << "Ly : " << Ly << " (Length of domain in y m)" << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl; 
}

void meshType::write() const{
	std::ofstream xfile; 
	std::ofstream yfile; 
	xfile.open("xc.dat");
	yfile.open("yc.dat");

	for (int i = 0; i < (Nx + 2); i++)
	{
		xfile << xc[i] << "\n";
	}		
	
	for (int i = 0; i < (Ny + 2); i ++)
	{
		yfile << yc[i] << "\n";
	}

	xfile.close();
	yfile.close();
}
