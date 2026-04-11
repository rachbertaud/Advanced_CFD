#ifndef HEADER_SCASF_H
#define HEADER_SCASF_H

#include <vector>

#include "Header_Mesh.H"
#include "Header_VolSF.H"
#include "Header_velF.H"

struct surfaceScalarField
{
	int Nx, Ny;
	std::vector<double> phix;
	std::vector<double> phiy;

	surfaceScalarField(const meshType& Mesh);
	
	double getw(int i, int j) const;

	double gete(int i, int j) const;
	
	double getn(int i, int j) const;
	
	double gets(int i, int j) const;

	void ComputePhix(const meshType& Mesh, const volScalarField& C, const velocityField& U);

	void ComputePhiy(const meshType& Mesh, const volScalarField& C, const velocityField& U);




};

#endif
