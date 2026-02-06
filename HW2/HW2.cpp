#include <fstream>	// needed for file writing
#include <iostream> 	// needed for cout
#include <string> 	// needed for string 
#include <map>		// for variable map definition
#include "HW2.h"	// for user-defined functions
#include <vector>	// needed for vectors
#include <cmath>	// math library for RHS

int main()
{
	std::map<std::string, double> var;

	read_inputs(var);


	int Nx = int(var["Nx"]);
	int Ny = int(var["Ny"]);
	double Lx = var["Lx"];
	double Ly = var["Ly"];


	std::cout << "--------INPUTS---------" << std::endl;
	for(const auto& pair : var)
	{
    		std::cout << pair.first << " = " << pair.second << std::endl;
	}
	
	// defining dx and dy with user inputs 
	double dx = Lx / static_cast<double>(Nx);
	double dy = Ly / static_cast<double>(Ny);
	
	// defining x-domain vector spaces
	std::vector<double> xf(var["Nx"] + 1); // face locations
	std::vector<double> x(var["Nx"] + 2); // cell-centered locations
	
	// computing face locations 
	for(int i = 0; i <= Nx; i++)
	{
		xf[i] = dx*i;
	}
	
	// computing cell centered loations
	for(int i = 0; i <= (Nx + 1); i++)
	{
		x[i] = -dx*0.5 + dx*i;
	}

        // defining y-domain vector spaces
        std::vector<double> yf(Ny + 1); // face locations
        std::vector<double> y(Ny + 2); // cell-centered locations

        // computing face locations
        for(int i = 0; i <= Ny; i++)
        {
                yf[i] = dy*i;
        }

        // computing cell centered loations
        for(int i = 0; i <= (Ny + 1); i++)
        {
                y[i] = -dy*0.5 + dy*i;
        }
	
	std::ofstream xfile; 
	std::ofstream yfile; 
	xfile.open("x.dat");
	yfile.open("y.dat");

	for (int i = 0; i < (Nx + 2); i++)
	{
		xfile << x[i] << "\n";
	}		
	
	for (int i = 0; i < (Ny + 2); i ++)
	{
		yfile << y[i] << "\n";
	}

	xfile.close();
	yfile.close();

//--------------------------------------- PROBLEM ONE -------------------------------------
	
	// build matrix
	int row; 
	int Nx2 = Nx + 2;
	int Ny2 = Ny + 2;

	std::vector<int> ROW, COL;
	std::vector<double> VAL;
	
	// north/south boundary conditions
	for( int i = 1; i <= Nx; i ++)
	{
		//southern (first row) 
		row = i;

		//these enforce that the average between GC and domain is 0
		ROW.push_back(row);
		COL.push_back(row);
		VAL.push_back(0.5);

		ROW.push_back(row);
		COL.push_back(row + Nx2);
		VAL.push_back(0.5);
		
		//northern (last row)
		row = ((Ny2 - 1)*Nx2) + i;
		
		ROW.push_back(row);
		COL.push_back(row);
		VAL.push_back(0.5);

		ROW.push_back(row);
		COL.push_back(row - Nx2);
		VAL.push_back(0.5);
	}

	// east/west BC
	for( int j = 1; j <= Ny; j++)
	{
		// western (left-most column)
		row = j*Nx2;
	
		ROW.push_back(row);
		COL.push_back(row);
		VAL.push_back(0.5);

		ROW.push_back(row);
		COL.push_back(row + 1);
		VAL.push_back(0.5);
		
		// eastern (right-most column)
		row = (j + 1)*Nx2 - 1; // remember we don't care about the corners
		
		ROW.push_back(row);
		COL.push_back(row);
		VAL.push_back(0.5);

		ROW.push_back(row);
		COL.push_back(row - 1);
		VAL.push_back(0.5);
	}

	// five-point stencil
	double k1 = var["k1"]; 
	double ae = k1*dy/dx;
	double aw = k1*dy/dx;
	double an = k1*dx/dy;
	double as = k1*dx/dy;
	double ap = ae + aw + an + as;

	int col;

	for ( int i = 1; i <= Nx; i++ ) 
	{		
		for ( int j = 1; j <= Ny; j++ )
			{
			//these will be all the points not on the boundaries.
			ROW.push_back(row);
			COL.push_back(row);
			VAL.push_back(ap);

			ROW.push_back(row);
			COL.push_back(row + 1);
			VAL.push_back(ae);

			ROW.push_back(row);
			COL.push_back(row - 1);
			VAL.push_back(aw);

			ROW.push_back(row);
			COL.push_back(row + Nx2);
			VAL.push_back(an);

			ROW.push_back(row);
			COL.push_back(row - Nx2);
			VAL.push_back(as);
		}
				
	}

	// now for extraneous nodes
	
	// bottom left
	ROW.push_back(0);
	COL.push_back(0);
	VAL.push_back(0);
	
	//bottom right
	ROW.push_back(Nx2);
	COL.push_back(Nx2);
	VAL.push_back(0);
	
	//top left 
	ROW.push_back((Ny+1)*Nx2);
	COL.push_back((Ny + 1)*Nx2);
	VAL.push_back(0);

	// top right
	ROW.push_back((Ny + 1)*(Nx + 1));
	COL.push_back((Ny + 1)*(Nx + 1));
	VAL.push_back(0);
	  
//---------------------------PROBLEM TWO---------------------------------
	// initalize RHS vector to zeros
	int Ntot = Ny2*Nx2; // total num of nodes
	std::vector<double> B(Ntot, 0.0);; // init to 0

	// south/north boundary conditions
	for(int i = 1; i <= Nx; i++)
	{
		// south 
		row = i;
		B[row] = std::cos(x[i]);

		// north 
		row = (Ny + 1)*Nx2 + i;
		B[row] = std::cos(x[i])*std::cos(Ly);
	
	}

	// east/west boundary conditions
	for(int j = 1; j <= Ny; j++)
	{
		// west
		row = Nx2*j;
		B[row] = std::cos(y[j]);
	
		// east
		row = Nx2*(j + 1) - 1; //don't forget the first row corner is meh
		B[row] = std::cos(x[Lx])*std::cos(y[j]);
		
	}

	// internal nodes
	for (int i = 1; i <= Nx; i++)
	{
		for (int j = 1; j <= Ny; j++)
		{
			row = Nx2*j + i;
			B[row] = std::cos(x[i])*std::cos(y[i]);
		}
	}
//-------------------------PROBLEM THREE-----------------------------------
//this ends main
}
