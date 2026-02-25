#include <vector>

#include "Header_Mesh.h"
#include "Header_Adv.h"

void surfaceScalarField::allocate(const meshType& Mesh)
{
	Nx = Mesh.Nx;
	Ny = Mesh.Ny;
	phix.assign((Nx+1)*Ny, 0.00);
	phiy.assign(Nx*(Ny+1), 0.00);
}

// get west face of cell (i,j)
double surfaceScalarField::getw(int i, int j) const
{
	return phix[i-1 + (j - 1)*(Nx + 1)];
}


double surfaceScalarField::gete(int i, int j) const
{
	return phix[i + (j - 1)*(Nx + 1)];
}

double surfaceScalarField::gets(int i, int j) const
{
	return phiy[i - 1 + (j - 1)*Nx];
}

double surfaceScalarField::getn(int i, int j) const
{
	return phiy[i - 1 + (j)*Nx];
}

double compU(double x, double y, 
	     const meshType& Mesh, 
	     const caseType& Case)
{

	const double pi = 3.141592653589793;

	double A = Case.A;
	double by = Case.by;
	double bx = Case.bx;

	double Ly = Mesh.Ly;
	double Lx = Mesh.Lx;

	double frac1 = -A/(by*Ly);
	double frac2 = (2*pi*x)/(bx*Lx);
	double frac3 = (2*pi*y)/(by*Ly); 

	double out = frac1*std::sin(frac2)*std::cos(frac3);

	return out;
}


double compV(double x, double y, 
	     const meshType& Mesh, 
	     const caseType& Case)
{

	const double pi = 3.141592653589793;

	double A = Case.A;
	double by = Case.by;
	double bx = Case.bx;

	double Ly = Mesh.Ly;
	double Lx = Mesh.Lx;

	double frac1 = A/(bx*Lx);
	double frac2 = (2*pi*x)/(bx*Lx);
	double frac3 = (2*pi*y)/(by*Ly); 

	double out = frac1*std::cos(frac2)*std::sin(frac3);

	return out;
}


void ComputePhix(surfaceScalarField& flux, 
		 const meshType& Mesh,
		 const caseType& Case)
{
	int Nx = Mesh.Nx;
	int Ny = Mesh.Ny;
	
	for (int i = 0; i <= Nx; i++)
	{
		for(int j = 0; j < Ny; j++)
		{
			double x = Mesh.xf[i];
			double y = Mesh.yc[j+1];
			
			flux.phix[ i + j*(Nx + 1)] = Case.cp*Case.rho*compU(x,y,Mesh,Case);		
		}
	}
}

void ComputePhiy(surfaceScalarField& flux, 
		 const meshType& Mesh,
		 const caseType& Case)
{
	int Nx = Mesh.Nx;
	int Ny = Mesh.Ny;
	
	for (int i = 0; i < Nx; i++)
	{
		for( int j = 0; j<= Ny; j++)
		{
			double x = Mesh.xc[i + 1];
			double y = Mesh.yf[j];		
			flux.phiy[i + j*Nx] = Case.cp*Case.rho*compV(x,y,Mesh,Case); 

		}
	}
}

