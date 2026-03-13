#ifndef HEADER_ROBIN_H
#define HEADER_ROBIN_H

struct BC{

  double k;
  double h;
  double Tx;
  double Td;
  double Ts;
  double h1, h2;
  double n1, n2;
  double w1,w2;
  double s1,s2;
  

  void read();
  void disp() const;
  
  
  void W(double y, double t, double& a, double& b, double& g) const;
  void E(double y, double t, double& a, double& b, double& g) const;
  void N(double x, double t, double& a, double& b, double& g) const;
  void S(double x, double t, double& a, double& b, double& g) const;

};

#endif
