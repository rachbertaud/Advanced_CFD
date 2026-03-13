#ifndef HEADER_SCASF_H
#define HEADER_SCASF_H

#include <vector>

#include "Header_Mesh.h"
#include "Header_Case.h"

struct surfaceScalarField
{
	int Nx, Ny;
	std::vector<double> phix;
	std::vector<double> phiy;

	void allocate(const meshType& Mesh);
	
	double getw(int i, int j) const;

	double gete(int i, int j) const;
	
	double getn(int i, int j) const;
	
	double gets(int i, int j) const;

	double compV(double x, double y, 
	     const meshType& Mesh, 
	     const caseType& Case);

	double compU(double x, double y, 
	     const meshType& Mesh, 
	     const caseType& Case);

	void ComputePhix(
		 const meshType& Mesh,
		 const caseType& Case);

	void ComputePhiy( 
		 const meshType& Mesh,
		 const caseType& Case);





};

// double compU(double x, double y, 
// 	     const meshType& Mesh, 
// 	     const caseType& Case);

// double compV(double x, double y, 
// 	     const meshType& Mesh, 
// 	     const caseType& Case);

// void ComputePhix(surfaceScalarField& flux, 
// 		 const meshType& Mesh,
// 		 const caseType& Case);

// void ComputePhiy(surfaceScalarField& flux, 
// 		 const meshType& Mesh,
// 		 const caseType& Case);



#endif
