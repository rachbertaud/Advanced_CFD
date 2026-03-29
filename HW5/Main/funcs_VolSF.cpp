#include "Header_VolSF.H"
#include "Header_IO.H"
#include "Header_Mesh.H"
#include "Header_bcType.H"

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

volScalarField::volScalarField(std::string name, meshType Mesh)
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

    disp(name);

    Nx = Mesh.Nx;
    Ny = Mesh.Ny;
    Ntot = (Nx + 2)*(Ny + 2);
    values.assign(Ntot, 0.0);
    BC = bcType(filename);
  };


double volScalarField::get(int i, int j) const
{
    return values[i + j*(Nx + 2)];
}

void volScalarField::set(int i, int j, double val)
{
    values[i + j*(Nx + 2)] = val;
}

void volScalarField::Save() const
{
    std::ofstream file;
    file.open(savename);
    for (int i = 0; i < Ntot; i++)
    {
        file << values[i] << "\n";
    }

    file.close();
}

  
// void volScalarField
// ::read(std::string& name, std::map<std::string, double>& VolVar)
// {
//   std::string fieldname = name + ".inp";
//   reader(fieldname, VolVar);
  
  
