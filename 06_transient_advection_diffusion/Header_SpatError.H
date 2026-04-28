#ifndef HEADER_SPATERROR_H
#define HEADER_SPATERROR_H

#include <vector>
#include "Header_VolSF.H"
#include "Header_Mesh.H"
#include "Header_Time.H"

struct SpatError{

  int Tot_Res;
  int Ntot, Nx, Ny;
  double omega;
    
  std::vector<double> AnSol;

  SpatError();
  SpatError(const volScalarField& C);

  bool compStart(const volScalarField& C, const Time& runTime) const;

  void comp(const volScalarField& C);

  void setAnSol(const meshType& Mesh,
                         const Time& runTime);



  
};


#endif
