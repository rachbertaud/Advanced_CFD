#ifndef HEADER_BCTYPE_H
#define HEADER_BCTYPE_H

#include <string>
#include "Header_IO.H"

struct bcType{

  double Vm;
  double k;

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
