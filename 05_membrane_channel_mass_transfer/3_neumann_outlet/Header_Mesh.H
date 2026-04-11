#ifndef HEADER_MESH_H
#define HEADER_MESH_H

#include <vector>
#include <string>
#include <map>

#include "Header_IO.H"

struct meshType{

  int Nx, Ny;
	double Lx, Ly;
	double dx, dy;
	std::vector<double> xc, yc;
	std::vector<double> xf, yf;
	std::map<std::string, double> var;

  // constructors
  meshType();

  // member functions
  void read();
  void set();
  void disp() const;
  void write() const;
};


#endif

