#ifndef HEADER_BCTYPE_H
#define HEADER_BCTYPE_H

#include "Header_IO.H"
#include "Header_Mesh.H"

struct bcType{

  double k;
  double dy;
  double dx;
  double omega;
  double cp;
  double rho;
  double time;

  bcType();
  bcType(double Crho, double Ck, double Ccp, double Com, double Ctime);
  
  void read();
  void set();
  void disp() const;
  
  
  void W(double y, double t, double& a, double& b, double& g) const;
  void E(double y, double t, double& a, double& b, double& g) const;
  void N(double x, double t, double& a, double& b, double& g) const;
  void S(double x, double t, double& a, double& b, double& g) const;

};

#endif
