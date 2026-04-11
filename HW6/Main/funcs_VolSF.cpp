#include "Header_VolSF.H"
#include "Header_IO.H"
#include "Header_Mesh.H"
#include "Header_bcType.H"
#include "Header_Time.H"

#include <iostream>
#include <string> 	//needed for string
#include <fstream>

void volScalarField::disp(std::string name)
{
  std::cout << "****** " << name << " inputs *******" << std::endl;
  std::cout << "rho   " << rho << "   put some units here probs" << std::endl;
  std::cout << "cp    " << cp <<  "   ^^^" << std::endl;
  std::cout << "k     " << k <<   "   ^^^^" << std::endl;
}

volScalarField::volScalarField(std::string name, meshType Mesh, const Time& runTime)
  {
    filename = name + ".inp";
    savename = name + ".dat";
    reader(filename, VolVar);
    std::string srho = "rho";
    rho = retriever(srho, VolVar);
    std::string scp = "cp";
    cp = retriever(scp, VolVar);
    std::string sk = "k";
    k = retriever(sk, VolVar);
    std::string om = "omega";
    omega = retriever(om, VolVar);
    time = runTime.time;

    disp(name);

    Nx = Mesh.Nx;
    Ny = Mesh.Ny;
    Ntot = (Nx + 2)*(Ny + 2);
    values.assign(Ntot, 0.0);
    
    BC = bcType(rho, k, cp, omega, time);

    t00.allocate(Nx + 2, Ny + 2);
    t0.allocate(Nx + 2, Ny + 2);
    t1.allocate(Nx + 2, Ny + 2);
    F.allocate(Nx + 2, Ny + 2);
  };


double volScalarField::get(int i, int j) const
{
    return values[i + j*(Nx + 2)];
}

void volScalarField::set(int i, int j, double val)
{
    values[i + j*(Nx + 2)] = val;
}

void volScalarField::Save(const Time& runTime) const
{
    double time = runTime.time;
    std::string tName = std::to_string(time);
    std::ofstream file;
    file.open("T_" + tName);
    for (int i = 0; i < Ntot; i++)
    {
        file << t0.values[i] << "\n";
    }

    file.close();
}

  
void volScalarField::setUniformIC(double val)
{
  for(int i = 0; i < (Nx + 2); i++)
  {
    for(int j = 0; j < (Ny + 2); j++)
    {
      t0.set(i, j, val);
    }
  }
}

void volScalarField::setSource(const meshType& Mesh,
                               const Time& runTime)
{
  double t = runTime.time;

  for ( int i = 1; i <= Nx; i++ )
  {
    for ( int j = 1; j <= Ny; j ++)
    {
      double x = Mesh.xc[i];
      double y = Mesh.yc[j];

      
      double sqrTerm = std::sin(x)*std::sin(x)*std::cos(y)*std::cos(y)
                       - std::cos(x)*std::cos(x)*std::sin(y)*std::sin(y);
      double val = -rho*cp*omega*std::cos(x)*std::cos(y)*std::sin(omega*t)
                   + rho*cp*std::cos(omega*t)*(sqrTerm)
                   + 2*k*std::cos(x)*std::cos(y)*std::cos(omega*t);
      
      F.set(i,j,val);
    }
  }
}

void volScalarField::compTmax(const Time& runTime)
{
  double Tmax = 0;
  for(int i = 0; i < Ntot; i ++){
    double diff = std::fabs(t1.values[i] - t0.values[i]);
    if( diff > Tmax)
    {
      Tmax = diff;
    }
  }
  double dt = runTime.dt;

  double time = runTime.time;
  
  Tmax = Tmax/dt;

  std::cout << "**********************************************" << std::endl;
  std::cout << "Tmax is " << Tmax << " at time " << time<< "!" << std::endl;
}

void volScalarField::update()
{
  t0 = t1;
}
