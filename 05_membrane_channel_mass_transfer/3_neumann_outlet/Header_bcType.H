#ifndef HEADER_BCTYPE_H
#define HEADER_BCTYPE_H

#include <string>
#include "Header_IO.H"
#include "Header_Mesh.H"

struct bcType{

  double Vm;
  double k;
  double dy;
  double dx;

  bcType();
  bcType(std::string filename);
  
  void read();
  void set();
  void disp() const;
  
  
  void W(double y, double t, double& a, double& b, double& g) const;
  void E(double y, double t, double& a, double& b, double& g) const;
  void N(double x, double t, double& a, double& b, double& g) const;
  void S(double x, double t, double& a, double& b, double& g) const;

};

#endif
