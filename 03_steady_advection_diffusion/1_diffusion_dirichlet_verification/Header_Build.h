#ifndef HEADER_BUILD_H
#define HEADER_BUILD_H

#include <vector>
#include "Header_Mesh.h"
#include "Header_Case.h"

//---------------------------COMP FUNCTIONS----------------------------------------------

struct matrixType
{				
	int Nx, Ny;			// number of cells in x and y
	int Nx2, Ny2;			// includes ghost nodes
	std::vector<int> ROW;		// row indicies of nonzeros
	std::vector<int> COL;		//column indicies of nonzeros
	std::vector<double> VAL;	// values of nonzeros
	std::vector<double> B;		// RHS vector

	// initalize values
	void init(const meshType&Mesh);

	// add a matrix entry at row, col with value val
	void addEntry(int row, int col, double val);

	// set RHS at cell (i,j)
	void setRHS(int i, int j, double val);

	// get RHS at cell (i,j)
	double getRHS(int i, int j) const;

};

void BuildA(matrixType& Matrix,
	    const meshType& Mesh, 
            const caseType& Case);

void BuildRHS(matrixType& Matrix,
              const meshType& Mesh, 
              const caseType& Case);
#endif
