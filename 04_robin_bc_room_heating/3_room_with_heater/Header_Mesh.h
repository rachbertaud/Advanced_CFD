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

	void read();
	void create();
	void disp() const;
	void write() const;
	
};


#endif
