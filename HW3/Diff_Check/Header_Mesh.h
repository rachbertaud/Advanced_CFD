#ifndef HEADER_MESH_H
#define HEADER_MESH_H

#include <iostream>
#include <vector>
#include <map>

//---------------------------MESH FUNCTIONS----------------------------------------------

struct meshType{
	int Nx, Ny;
	double Lx, Ly;
	double dx, dy;
	std::vector<double> xc, yc;
	std::vector<double> xf, yf;
};

void read_inputs_mesh(std::map<std::string, double>& variables);

void readMesh(meshType& Mesh);

void createMesh(meshType& Mesh);

void dispMesh(const meshType& Mesh);

void writeMesh(const meshType& Mesh);

#endif
