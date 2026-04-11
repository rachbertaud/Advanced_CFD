#include "Header_VolSF.H"
#include "Header_Mesh.H"
#include "Header_velF.H"
#include "Header_ScaSF.H"
#include "Header_matrix.H"
#include "Header_bcType.H"
#include "Header_Time.H"

int main()
{
  Time runTime;
  
  int flag = 0;

  meshType Mesh;
  
  volScalarField T("T", Mesh, runTime);

  velocityField U(Mesh);
  surfaceScalarField Flux(Mesh);
  Flux.ComputePhix(Mesh, T, U);
  Flux.ComputePhiy(Mesh, T, U);

  matrixType Matrix(Mesh);
  Matrix.BuildA(Mesh, Flux, T, runTime);
  Matrix.factorize();

  while( runTime.run() )
  {
    runTime.advance();

    T.setSource(Mesh, runTime);
    Matrix.BuildRHS(Mesh, T, U, runTime);

    Matrix.solve(T);


    if (runTime.writeNow())
    {
      T.compTmax(runTime);
      T.Save(runTime);
    }

    T.update();
  }
  

  return flag;
};
