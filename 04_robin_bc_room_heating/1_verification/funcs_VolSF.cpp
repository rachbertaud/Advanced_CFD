#include <vector>
#include <iostream>
#include <fstream>

#include "Header_Mesh.h"
#include "Header_VolSF.h"

void volScalarField::allocate(const meshType& Mesh)
{
    Nx = Mesh.Nx;
    Ny = Mesh.Ny;
    Ntot = (Nx + 2)*(Ny + 2);
    values.assign(Ntot, 0.0);

}

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
    file.open("T.dat");
    for (int i = 0; i < Ntot; i++)
    {
        file << values[i] << "\n";
    }

    file.close();
}


