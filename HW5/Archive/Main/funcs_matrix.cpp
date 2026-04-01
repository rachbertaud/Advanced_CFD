#include <vector>

#include "Header_matrix.H"	// for builder funcs/structs
#include "Header_Mesh.H"	// for mesh funcs/structs
#include "Header_ScaSF.H"		// for advection funcs/structs
#include "Header_VolSF.H"
#include "Header_velF.H"
#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/SparseLU>
#include <iostream>
#include <fstream>



matrixType::matrixType(meshType& Mesh)
{
	init(Mesh);
}

void matrixType::init(const meshType& Mesh)
{
	Nx = Mesh.Nx;
	std::cout << Nx << std::endl;
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
	    const surfaceScalarField& Flux,
	    const volScalarField& C)
{
	double dx = Mesh.dx;
	double dy = Mesh.dy;
	double k = C.k;
	//std::cout << "Here!" << std::endl;

	int row;

	//south/north boundary conditions
	for (int i = 1; i <= Nx; i++)
	{
		// south (Robin)
		row = i;
		double as,bs,gs;
		C.BC.S(Mesh.xc[i], 0.0, as, bs, gs);
		addEntry(row, row , 0.5*as + bs/dy);
		addEntry(row, row + Nx2, 0.5*as - bs/dy); 

		//north (Robin)
		row = i + (Nx2*(Ny + 1));
		double an,bn,gn;
		C.BC.N(Mesh.Lx, 0.0, an, bn, gn);
		addEntry(row, row, 0.5*an + bn/dy);
		addEntry(row, row - Nx2, 0.5*an - bn/dy);
	}

	//east/west boundary conditions
	for (int j = 1; j <= Ny; j++)
	{
		//west 
		row = Nx2*j;
		double aw,bw,gw;
		C.BC.W(Mesh.yc[j], 0.0, aw, bw, gw);
		addEntry(row, row, 0.5*aw + bw/dx);
		addEntry(row, row + 1, 0.5*aw - bw/dx);

		//east
		row = Nx2*(j + 1) - 1;
		double ae,be,ge;
		C.BC.E(Mesh.Ly, 0.0, ae, be, ge);
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

	
	double cp = C.cp;

	//internal nodes of A
	//
	//double count = 0;
	
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
			//std::cout << "ae: " << ae << std::endl;
			double aw = Dw + Aw;
			//std::cout << "aw: " << aw << std::endl;
			double as = Ds + As;
			//std::cout << "as: " << as << std::endl;
			double an = Dn + An;
			//std::cout << "an: " << an << std::endl;
			double ap = Dp + Ap;
			//std::cout << "ap: " << ap << std::endl;

			row = Nx2*j + i;
	
			addEntry(row, row, ap);
			addEntry(row, row + 1, -ae);
			addEntry(row, row - 1, -aw);
			addEntry(row, row + Nx2, -an);
			addEntry(row, row - Nx2, -as);
			//count += 1;
		}
	}
	//std::cout << "count: " << count << std::endl;

	// extraneous nodes

	//bottom left 
	addEntry(0,0,1);
	
	//bottom right
	addEntry(Nx2 - 1, Nx2 - 1, 1);
	
	//top left
	addEntry(Nx2*(Ny + 1), Nx2*(Ny + 1), 1);

	//top right 
	addEntry((Nx2*Ny2 - 1), (Nx2*Ny2 - 1), 1);

		// Save the solution ot file
	//std::ofstream rowfile("row.dat");
	//double Ntot = Nx2*Ny2;
	//for (int i = 0; i < ROW.size(); i++)
	//{
	//	rowfile << ROW[i] << "\n";
	//}
	//rowfile.close();
 	// Save the solution ot file
	//std::ofstream colfile("col.dat");
	//for (int i = 0; i < COL.size(); i++)
	//{
	//	colfile << COL[i] << "\n";
	//}
	//colfile.close();
	// Save the solution ot file
	//std::ofstream valfile("val.dat");
	//for (int i = 0; i < VAL.size(); i++)
	//{
	//	valfile << VAL[i] << "\n";
	//}
	//valfile.close();

}

void matrixType::BuildRHS( 
	      const meshType& Mesh,
	      const volScalarField& C,
	    	const velocityField& U)
{

	double dx = Mesh.dx;
	double dy = Mesh.dy;
	double Lx = Mesh.Lx;
	double Ly = Mesh.Ly;

	double k = C.k;

	// south/north BC (Dirichlet)
	for (int i = 1; i <= Nx; i++)
	{
		//south 
		// double gs = Case.Ts;
		double xs = Mesh.xc[i];
		double as = 0;
		double bs = 0;
		double gs = 0;
		C.BC.S(xs, 0.0, as, bs, gs);
		
		setRHS(i, 0, gs);
	
		//north
		double xn = Mesh.xc[i];
		double an = 0;
		double bn = 0;
		double gn = 0;
		C.BC.N(xn, 0.0, an, bn, gn);
		
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
		C.BC.W(yw, 0.0, aw, bw, gw);
		
		setRHS(0, j, gw);

		//east
		double ye = Mesh.yc[j];
		double ae = 0;
		double be = 0;
		double ge = 0;
		C.BC.E(ye, 0.0, ae, be, ge);

		setRHS((Nx + 1), j, ge);
	}

}


int matrixType::EigenSolve()
{

	int Ntot = Nx2*Ny2;

	Eigen::VectorXd Bs(Ntot);
	for (int i = 0; i < Ntot; i++)
	{
		Bs[i] = B[i];
	}

	int nnz = ROW.size();

	std::vector<Eigen::Triplet<double>> triplets;
	triplets.reserve(nnz);

	for (int k = 0; k < nnz; k++)
	{
		triplets.push_back(Eigen::Triplet<double>(
			ROW[k],
			COL[k],
			VAL[k]
		));
	}

	Eigen::SparseMatrix<double> As(Ny2*Nx2, Nx2*Ny2);
	As.setFromTriplets(triplets.begin(), triplets.end());
	
	Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;

	solver.compute(As);

	if(solver.info() != Eigen::Success)
	{
		std::cerr << "Decomposition failed ! \n "; 
		return -1;
	}

	Eigen::VectorXd C = solver.solve(Bs);
	if(solver.info() != Eigen::Success)
	{
		std::cerr << "Solving failed! \n";
		return -1;
	}

	// Save the solution ot file
	std::ofstream cfile("c.dat");
	//cfile << std::scientific << std::setprecision(16);
	for (int i = 0; i < Ntot; i++)
	{
		cfile << C[i] << "\n";
	}
	cfile.close();

	return 0;
}


	
	

