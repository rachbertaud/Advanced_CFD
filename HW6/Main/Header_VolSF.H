#ifndef HEADER_VOLSF_H
#define HEADER_VOLSF_H

#include <string>
#include <vector>
#include <map>

#include "Header_Mesh.H"
#include "Header_bcType.H"
#include "Header_fieldVal.H"
#include "Header_Time.H"


struct volScalarField
{
  int Nx, Ny;
  int Ntot;
  std::vector<double> values;
  double rho, cp, k, omega, time, Tmax;
  //std::string name;
  std::map<std::string, double> VolVar;

  std::string filename;
  std::string savename;

  bcType BC;

  // --------- constructors ---------- //
  volScalarField();
  volScalarField(std::string name);
  volScalarField(std::string name, meshType Mesh, const Time& runTime);

  
  // --------- member functions ------------ //
  void disp(std::string name);
  double get(int i, int j) const;
  void set(int i, int j, double val);
  void Save(const Time& runTime) const;
  void setUniformIC(double val, int flag, const meshType& Mesh);

  fieldVal t00;
  fieldVal t0;
  fieldVal t1;
  fieldVal F;
  void setSource(const meshType& Mesh,
                const Time& runTime);

  void compTmax(const Time& runTime);

  void update();

};




#endif

