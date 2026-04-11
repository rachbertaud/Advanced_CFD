#include <vector>
#include <iostream>

#include "Header_Mesh.H"
#include "Header_ScaSF.H"
#include "Header_velF.H"
#include "Header_VolSF.H"

surfaceScalarField::surfaceScalarField(const meshType& Mesh)
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

void surfaceScalarField::ComputePhix(
		 const meshType& Mesh,
		 const volScalarField& C,
	   const velocityField& U)
{	
	for (int i = 0; i <= Nx; i++)
	{
		for(int j = 0; j < Ny; j++)
		{
			double x = Mesh.xf[i];
			double y = Mesh.yc[j+1];
			
			phix[ i + j*(Nx + 1)] = U.compU(x,y);		
		}
	}
}

void surfaceScalarField::ComputePhiy( 
		 const meshType& Mesh,
		 const volScalarField& C,
		 const velocityField& U)
{
	for (int i = 0; i < Nx; i++)
	{
		for( int j = 0; j<= Ny; j++)
		{
			double x = Mesh.xc[i + 1];
			double y = Mesh.yf[j];
			//std::cout << C.cp << "," << C.rho << "," << U.compV(x,y) << std::endl;
			phiy[i + j*Nx] = U.compV(x,y); 

		}
	}
}

