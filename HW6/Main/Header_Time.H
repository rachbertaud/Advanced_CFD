#ifndef HEADER_TIME_H
#define HEADER_TIME_H
#include "Header_IO.H"
//
struct Time
{

  double startTime;
  double dt;
  int Nt;
  int writeInterval;
  std::map< std::string, double > var;
  double time;
  int timeStep;
  
  Time();

  void set();
  void disp() const;
  void advance();
  bool run() const;
  bool writeNow() const;
};



#endif
