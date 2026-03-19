#include <vector>

#include "Header_Mesh.H"
#include "Header_ScaSF.H"

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

void surfaceScalarField::ComputePhix(
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
			
			phix[ i + j*(Nx + 1)] = Case.cp*Case.rho*compU(x,y,Mesh,Case);		
		}
	}
}

void surfaceScalarField::ComputePhiy( 
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
			phiy[i + j*Nx] = Case.cp*Case.rho*compV(x,y,Mesh,Case); 

		}
	}
}

