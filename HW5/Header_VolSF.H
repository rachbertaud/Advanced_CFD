#ifndef HEADER_VOLSF_H
#define HEADER_VOLSF_H

#include <string>
#include <vector>
#include <map>

#include "Header_Mesh.H"


struct volScalarField
{
  int Nx, Ny;
  int Ntot;
  std::vector<double> values;
  double rho, cp, k;
  //std::string name;
  std::map<std::string, double> VolVar;

  std::string filename;
  std::string savename;

  // --------- constructors ---------- //
  volScalarField(std::string name, meshType Mesh);

  
  // --------- member functions ------------ //
  void disp(std::string name);
  double get(int i, int j) const;
  void set(int i, int j, double val);
  void Save() const;
  


};




#endif

