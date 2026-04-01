#ifndef HEADER_VELF_H
#define HEADER_VELF_H

#include "Header_Mesh.H"
#include "Header_IO.H"

#include <map>
#include <string>

struct velocityField
{
  double Uin; //mean inlet velocity
  double Vm; //transmembrane velocity
  double h; //channel half-height
  

  // ------- member functions -------- //
  double compU(double x, double y) const;
  double compV(double x, double y) const;
  void set();
  void disp();
  std::map<std::string, double> VelVar;
  
  // --------- constructors ---------------
  velocityField(meshType& Mesh);
};

#endif
