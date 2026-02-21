#include <iostream> 		//for cout
#include <vector>
#include <cmath>

#include "Header_Build.h"	// for builder funcs/structs
#include "Header_Mesh.h"	// for mesh funcs/structs
#include "Header_Case.h"	// for case funcs/structs

void matrixType::init(const meshType& Mesh)
{
	Nx = Mesh.Nx;
	Ny = Mesh.Ny;
	Nx2 = Nx + 2;
	Ny2 = Ny + 2;
	B.assign(Nx2*Ny2, 0.0);
}

void matrixType::addEntry(int row, int col, double val)
{
	ROW.push_back(row);
	COL.push_back(col);
	VAL.push_back(val);
}

void matrixType::setRHS(int i, int j, double val)
{
	B[i + j*Nx2] = val;
}

double matrixType::getRHS(int i, int j) const
{
	return B[i + j*Nx2];
}

void BuildA(matrixType& Matrix, 
	    const meshType& Mesh, 
	    const caseType& Case)
{
	int Nx = Matrix.Nx;
	int Ny = Matrix.Ny;
	int Nx2 = Matrix.Nx2;
	int Ny2 = Matrix.Ny2;
	double dx = Mesh.dx;
	double dy = Mesh.dy;
	double k = Case.k;

	int row;

	//south/north boundary conditions (Dirichlet)
	for (int i = 1; i <= Nx; i++)
	{
		// south 
		row = i;
		Matrix.addEntry(row, row , 0.5);
		Matrix.addEntry(row, row + Nx2, 0.5);

		//north 
		row = i + (Nx2*(Ny + 1));
		Matrix.addEntry(row, row, 0.5);
		Matrix.addEntry(row, row - Nx2, 0.5);
	}

	//east/west boundary conditions (Dirichlet)
	for (int j = 1; j <= Ny; j++)
	{
		//west
		row = Nx2*j;
		Matrix.addEntry(row, row, 0.5);
		Matrix.addEntry(row, row + 1, 0.5);

		//east 
		row = Nx2*(j + 1) - 1;
		Matrix.addEntry(row, row, 0.5);
		Matrix.addEntry(row, row - 1, 0.5);
	}

	//five-point stencil
	double De  = k*dy/dx;
	double Dw = k*dy/dx;
	double Ds = k*dx/dy;
	double Dn = k*dx/dy;
	double Dp = De + Dw + Ds + Dn;

	double Ae = 0;
	double Aw = 0;
	double As = 0;
	double An = 0;
	double Ap = 0;

	double ae = De + Ae;
	double aw = Dw + Aw;
	double as = Ds + As;
	double an = Dn + An;
	double ap = Dp + Ap;

	//internal nodes of A
	
	for (int i = 1; i <= Nx; i++)
	{
		for (int j = 1; j <= Ny; j++)
		{
			row = Nx2*j + i;
	
			Matrix.addEntry(row, row, ap);
			Matrix.addEntry(row, row + 1, -ae);
			Matrix.addEntry(row, row - 1, -aw);
			Matrix.addEntry(row, row + Nx2, -an);
			Matrix.addEntry(row, row - Nx2, -as);
		}
	}

	// extraneous nodes

	//bottom left 
	Matrix.addEntry(0,0,1);
	
	//bottom right
	Matrix.addEntry(Nx2 - 1, Nx2 - 1, 1);
	
	//top left
	Matrix.addEntry(Nx2*(Ny + 1), Nx2*(Ny + 1), 1);

	//top right 
	Matrix.addEntry((Nx2*Ny2 - 1), (Nx2*Ny2 - 1), 1);

}

void BuildRHS(matrixType& Matrix, 
	      const meshType& Mesh,
	      const caseType& Case)
{
	int Nx = Matrix.Nx;
	int Ny = Matrix.Ny;
	int Nx2 = Matrix.Nx2;
	int My2 = Matrix.Ny2;

	double dx = Mesh.dx;
	double dy = Mesh.dy;
	double Lx = Mesh.Lx;
	double Ly = Mesh.Ly;

	double k = Case.k;

	// south/north BC
	for (int i = 1; i <= Nx; i++)
	{
		//south 
		double gs = std::cos(Mesh.xc[i]);
		Matrix.setRHS(i, 0, gs);
	
		//north 
		double gn = std::cos(Mesh.xc[i])*std::cos(Ly);
		Matrix.setRHS(i, Ny + 1, gn);
	}

	// east/west BC
	for (int j = 1; j <= Ny; j++)
	{
		//west 
		double gw = std::cos(Mesh.yc[j]);
		Matrix.setRHS(0, j, gw);

		//east
		double ge = std::cos(Lx)*std::cos(Mesh.yc[j]);
		Matrix.setRHS((Nx + 1), j, ge);
	}

	
	// internal nodes
	for (int i = 1; i <= Nx; i++)
	{
		for (int j = 1; j <= Ny; j++)
		{
			double val = 2*dx*dy*k*std::cos(Mesh.xc[i])*std::cos(Mesh.yc[j]);
			Matrix.setRHS(i,j,val);
		}
	}
}


	
	

