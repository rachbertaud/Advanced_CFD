#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/SparseLU>
#include <vector>
#include <iostream> 
#include <fstream>

#include "Header_Build.h"
#include "Header_EigenSolve.h"

int EigenSolve(const matrixType& A, const matrixType& RHS)
{
	int Nx2 = A.Nx2;
	int Ny2 = A.Ny2;

	int Ntot = Nx2*Ny2;

	Eigen::VectorXd Bs(Ntot);
	for (int i = 0; i < Ntot; i++)
	{
		Bs[i] = RHS.B[i];
	}

	int nnz = A.ROW.size();

	std::vector<Eigen::Triplet<double>> triplets;
	triplets.reserve(nnz);

	for (int k = 0; k < nnz; k++)
	{
		triplets.push_back(Eigen::Triplet<double>(
			A.ROW[k],
			A.COL[k],
			A.VAL[k]
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
	for (int i = 0; i < Ntot; i++)
	{
		cfile << C[i] << "\n";
	}
	cfile.close();

	return 0;
}

