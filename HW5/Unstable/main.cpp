#include "Header_VolSF.H"
#include "Header_Mesh.H"
#include "Header_velF.H"
#include "Header_ScaSF.H"
#include "Header_matrix.H"
#include "Header_bcType.H"

int main()
{
  int flag = 0;

  meshType Mesh;
  
  volScalarField C("C", Mesh);

  velocityField U(Mesh);

  surfaceScalarField Flux(Mesh);
  Flux.ComputePhix(Mesh, C, U);
  Flux.ComputePhiy(Mesh, C, U);

  matrixType Matrix(Mesh);
  Matrix.BuildA(Mesh, Flux, C);
  Matrix.BuildRHS(Mesh, C, U);

  Matrix.EigenSolve();  
  
  

  return flag;
};
