#ifndef HEADER_ROBIN_H
#define HEADER_ROBIN_H

struct BC{

  double k;
  double h;
  double Tx;
  double Td;
  double n1, n2;
  double w1,w2;
  double s1,s2;
  

  void read();
  void disp() const;
  
  
  void W(double x, double y, double t, double& a, double& b, double& g) const;
  void E(double x,double y, double t, double& a, double& b, double& g) const;
  void N(double x,double y, double t, double& a, double& b, double& g) const;
  void S(double x,double y, double t, double& a, double& b, double& g) const;

};

#endif
