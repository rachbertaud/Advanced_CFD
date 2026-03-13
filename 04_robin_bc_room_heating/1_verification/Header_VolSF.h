#ifndef HEADER_VOLSF_H
#define HEADER_VOLSF_H

#include <vector>

#include "Header_Mesh.h"

struct volScalarField
{
  int Nx, Ny; // grid resolution
  int Ntot; // total number of nodes
  std::vector<double> values; // scalar field values

  void allocate(const meshType& Mesh);
  double get(int i, int j) const;
  void set(int i, int j, double val);
  void Save() const;



};

#endif
