#include "Header_velF.H"
#include "Header_Mesh.H"

#include <iostream>

double velocityField::compU(double x, double y) const
{
  double yhat = (y - h)/h;
  double xhat = x*h;
  return 1.5*Uin*(1 - (Vm/Uin)*xhat)*(1 - yhat*yhat);
}

double velocityField::compV(double x, double y) const
{
  double yhat = (y - h)/h;
  double xhat = x*h;
  return (Vm/2)*(3*yhat - yhat*yhat*yhat);
}


velocityField::velocityField(meshType& Mesh)
{
  h = 0.5*Mesh.Ly;
  std::string filename = "Vel.inp";
  reader(filename, VelVar);
  set();
  disp();
  
}

void velocityField::set()
{
  std::string su = "Uin";
  Uin = VelVar["Uin"];
  std::string sv = "Vm";
  Vm = VelVar["Vm"];
}

void velocityField::disp()
{
  std::cout << "********* VELOCITY INPUTS ************" << std::endl;
  std::cout << "Uin      " << Uin << "      probably something" << std::endl;
  std::cout << "Vm       " << Vm << "       probs something" << std::endl; 
}
