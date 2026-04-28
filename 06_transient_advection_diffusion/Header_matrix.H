#ifndef HEADER_MATRIX_H
#define HEADER_MATRIX_H

#include <vector>
#include "Header_Mesh.H"
#include "Header_ScaSF.H"
#include "Header_VolSF.H"
#include "Header_velF.H"
#include "Header_Time.H"

#include <Eigen/Sparse>
#include <Eigen/Dense>
#include <Eigen/SparseLU>


//---------------------------COMP FUNCTIONS----------------------------------------------

struct matrixType
{				
	int Nx, Ny;			// number of cells in x and y
	int Nx2, Ny2;			// includes ghost nodes
	std::vector<int> ROW;		// row indicies of nonzeros
	std::vector<int> COL;		//column indicies of nonzeros
	std::vector<double> VAL;	// values of nonzeros
	Eigen::VectorXd B;		// RHS vector
	Eigen::VectorXd X;    // solution vector

	matrixType(meshType& Mesh);
	
	// initalize values
	void init(const meshType& Mesh);

	// add a matrix entry at row, col with value val
	void addEntry(int row, int col, double val);

	// set RHS at cell (i,j)
	void setRHS(int i, int j, double val);

	// get RHS at cell (i,j)
	double getRHS(int i, int j) const;

	void BuildA(
	    const meshType& Mesh, 
	    const surfaceScalarField& Flux,
	  	const volScalarField& C,
	  	const Time& runTime);

	void BuildRHS(
      const meshType& Mesh,
    	const volScalarField& C,
    	const velocityField& U,
    	const Time& runTime);


	
	int EigenSolve();
	Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
	void factorize();
	void solve(volScalarField& C);

};
#endif
