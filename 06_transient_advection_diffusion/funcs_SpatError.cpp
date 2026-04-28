#include "Header_SpatError.H"
#include "Header_VolSF.H"
#include "Header_Mesh.H"
#include "Header_Time.H"

#include <iostream>
#include <iomanip>

SpatError::SpatError()
{
}

SpatError::SpatError(const volScalarField& C)
{
  omega = C.omega;
  Nx = C.Nx;
  Ny = C.Ny;
  Ntot = C.Ntot;

  AnSol.assign(Ntot, 0.0);

}


void SpatError::setAnSol(const meshType& Mesh,
                         const Time& runTime)
{
  double t = runTime.time;

  for ( int i = 1; i <= Nx; i++ )
  {
    for ( int j = 1; j <= Ny; j ++)
    {
      double x = Mesh.xc[i];
      double y = Mesh.yc[j];

      double val = std::cos(x)*std::cos(y)*std::cos(omega*t);

      AnSol[i + j*(Nx + 2)] = val;
    }
  }
}



bool SpatError::compStart(const volScalarField& C, const Time& runTime) const
{
  if(runTime.timeStep > 1)
  {
    return (C.Tmax < 1e-10);
  }
  else
    return (C.Tmax < -1);
}

void SpatError::comp(const volScalarField& C)
{
  double num = 0;
  double denom = 0;
  double top = 0;

  
  for( int j = 1; j < (Ny); j++)
  {
    for( int i = 1; i < (Nx); i++)
    {
      int row = i + j*(Nx + 2);
      top = std::fabs(AnSol[row] - C.t1.values[row]);
      if (top > num )
      {
        num = top;
      }

      if (std::fabs(AnSol[row]) > denom)
      {
        denom = std::fabs(AnSol[row]); 
      }

    }
  }

   std::cout << "ERROR=" << std::setprecision(15) << (num/denom) << std::endl;
}



