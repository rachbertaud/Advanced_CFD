#include <iostream> 		//for cout
#include <vector>
#include <cmath>

#include "Header_Build.h"	// for builder funcs/structs
#include "Header_Mesh.h"	// for mesh funcs/structs
#include "Header_Case.h"	// for case funcs/structs
#include "Header_Adv.h"		// for advection funcs/structs

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
	    const caseType& Case,
	    const surfaceScalarField& Flux)
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

	//east/west boundary conditions (Neumann)
	for (int j = 1; j <= Ny; j++)
	{
		//west
		row = Nx2*j;
		Matrix.addEntry(row, row, -1/dx);
		Matrix.addEntry(row, row + 1, 1/dx);

		//east 
		row = Nx2*(j + 1) - 1;
		Matrix.addEntry(row, row, 1/dx);
		Matrix.addEntry(row, row - 1, -1/dx);
	}

	//five-point stencil
	double De  = k*dy/dx;
	double Dw = k*dy/dx;
	double Ds = k*dx/dy;
	double Dn = k*dx/dy;
	double Dp = De + Dw + Ds + Dn;


	double Se = 0.5;
	double Sw = 0.5;
	double Sn = 0.5;
	double Ss = 0.5;

	
	double cp = Case.cp;

	//internal nodes of A
	
	for (int i = 1; i <= Nx; i++)
	{
		for (int j = 1; j <= Ny; j++)
		{

			double Fe = Flux.gete(i,j);
			double Fw = Flux.getw(i,j);
			double Fs = Flux.gets(i,j);
			double Fn = Flux.getn(i,j); 

			double Ae = -Fe*Se*dy;
			double Aw = Fw*(1 - Sw)*dy;
			double As = Fs*(1 - Ss)*dx;
			double An = -Fn*Sn*dx;
			double Ap = Fe*(1 - Se)*dy - Fw*Sw*dy + Fn*(1 - Sn)*dx - Fs*Ss*dx;

			double ae = De + Ae;
			double aw = Dw + Aw;
			double as = Ds + As;
			double an = Dn + An;
			double ap = Dp + Ap;

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
	int Ny2 = Matrix.Ny2;

	double dx = Mesh.dx;
	double dy = Mesh.dy;
	double Lx = Mesh.Lx;
	double Ly = Mesh.Ly;

	double k = Case.k;
	double by = Case.by;
	double bx = Case.bx;

	// south/north BC (Dirichlet)
	for (int i = 1; i <= Nx; i++)
	{
		//south 
		double gs = std::cos(Mesh.xc[i]);
		Matrix.setRHS(i, 0, gs);
	
		//north 
		double gn = std::cos(Mesh.xc[i])*std::cos(Ly);
		Matrix.setRHS(i, Ny + 1, gn);
	}

	// east/west BC (Neumann)
	for (int j = 1; j <= Ny; j++)
	{
		//west 
		double gw = -std::sin(0);
		Matrix.setRHS(0, j, gw);

		//east
		double ge = -std::sin(Lx)*std::cos(Mesh.yc[j]);
		Matrix.setRHS((Nx + 1), j, ge);
	}

	const double pi = 3.141592653589793;
	
	// internal nodes
	for (int i = 1; i <= Nx; i++)
	{
		for (int j = 1; j <= Ny; j++)
		{
			double diff = -2*k*std::cos(Mesh.xc[i])*std::cos(Mesh.yc[j]);

			double x = Mesh.xc[i];
			double y = Mesh.yc[j];
			
			double Tex = -std::sin(x)*std::cos(y);
			double Tey = -std::cos(x)*std::sin(y);

			double u = compU(x,y,Mesh,Case);
			double v = compV(x,y,Mesh,Case);
			
			double adv = Case.rho*Case.cp*((u*Tex) + (v*Tey));			
			
			double f = -diff + adv;

			Matrix.setRHS(i,j,dx*dy*f);
		}
	}
}


	
	

