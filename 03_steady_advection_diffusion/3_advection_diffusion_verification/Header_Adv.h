#ifndef HEADER_ADV_H
#define HEADER_ADV_H

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
};

double compU(double x, double y, 
	     const meshType& Mesh, 
	     const caseType& Case);

double compV(double x, double y, 
	     const meshType& Mesh, 
	     const caseType& Case);

void ComputePhix(surfaceScalarField& flux, 
		 const meshType& Mesh,
		 const caseType& Case);

void ComputePhiy(surfaceScalarField& flux, 
		 const meshType& Mesh,
		 const caseType& Case);



#endif
