#include <vector>

#include "Header_matrix.h"	// for builder funcs/structs
#include "Header_Mesh.h"	// for mesh funcs/structs
#include "Header_Case.h"	// for case funcs/structs
#include "Header_ScaSF.h"		// for advection funcs/structs
#include "Header_Robin.h"

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

void matrixType::BuildA( 
	    const meshType& Mesh, 
	    const caseType& Case,
	    const surfaceScalarField& Flux,
	    BC& BC
	  )
{
	double dx = Mesh.dx;
	double dy = Mesh.dy;
	double k = Case.k;

	int row;

	//south/north boundary conditions
	for (int i = 1; i <= Nx; i++)
	{
		// south (Robin)
		row = i;
		double as,bs,gs;
		BC.S(Mesh.xc[i],0.0, 0.0, as, bs, gs);
		addEntry(row, row , 0.5*as + bs/dy);
		addEntry(row, row + Nx2, 0.5*as - bs/dy); 

		//north (Robin)
		row = i + (Nx2*(Ny + 1));
		double an,bn,gn;
		BC.N(Mesh.xc[i], Mesh.Ly, 0.0, an, bn, gn);
		addEntry(row, row, 0.5*an + bn/dy);
		addEntry(row, row - Nx2, 0.5*an - bn/dy);
	}

	//east/west boundary conditions
	for (int j = 1; j <= Ny; j++)
	{
		//west (Robin)
		row = Nx2*j;
		double aw,bw,gw;
		BC.W(0.0,Mesh.yc[j], 0.0, aw, bw, gw);
		addEntry(row, row, 0.5*aw + bw/dx);
		addEntry(row, row + 1, 0.5*aw - bw/dx);

		//east (Neumann (through robin))
		row = Nx2*(j + 1) - 1;
		double ae,be,ge;
		BC.E(Mesh.Lx,Mesh.yc[j], 0.0, ae, be, ge);
		addEntry(row, row, ae*0.5 + be/dx);
		addEntry(row, row - 1,ae*0.5 - be/dx);
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
	
			addEntry(row, row, ap);
			addEntry(row, row + 1, -ae);
			addEntry(row, row - 1, -aw);
			addEntry(row, row + Nx2, -an);
			addEntry(row, row - Nx2, -as);
		}
	}

	// extraneous nodes

	//bottom left 
	addEntry(0,0,1);
	
	//bottom right
	addEntry(Nx2 - 1, Nx2 - 1, 1);
	
	//top left
	addEntry(Nx2*(Ny + 1), Nx2*(Ny + 1), 1);

	//top right 
	addEntry((Nx2*Ny2 - 1), (Nx2*Ny2 - 1), 1);

}

void matrixType::BuildRHS( 
	      const meshType& Mesh,
	      const caseType& Case,
	      surfaceScalarField& Flux,
	    	BC& BC)
{

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
		// double gs = Case.Ts;
		double xs = Mesh.xc[i];
		double as = 0;
		double bs = 0;
		double gs = 0;
		BC.S(xs, 0.0, 0.0, as, bs, gs);
		
		setRHS(i, 0, gs);
	
		//north
		double xn = Mesh.xc[i];
		double an = 0;
		double bn = 0;
		double gn = 0;
		BC.N(xn,Mesh.Ly, 0.0, an, bn, gn);
		
		setRHS(i, Ny + 1, gn);
	}

	// east/west BC (Neumann)
	for (int j = 1; j <= Ny; j++)
	{
		//west 
		double yw = Mesh.yc[j];
		double aw = 0;
		double bw = 0;
		double gw = 0;
		BC.W(0.0,Mesh.yc[j], 0.0, aw, bw, gw);
		
		setRHS(0, j, gw);

		//east
		double ye = Mesh.yc[j];
		double ae = 0;
		double be = 0;
		double ge = 0;
		BC.E(Mesh.Lx,Mesh.yc[j], 0.0, ae, be, ge);

		setRHS((Nx + 1), j, ge);
	}

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

			double u = Flux.compU(x,y,Mesh,Case);
			double v = Flux.compV(x,y,Mesh,Case);
				
			double adv = Case.rho*Case.cp*((u*Tex) + (v*Tey));			
			
			double f = -diff + adv;

			setRHS(i,j,dx*dy*f);
		}
	}

}


	
	

