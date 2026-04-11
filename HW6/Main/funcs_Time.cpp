#include "Header_Time.H"
#include <iostream>
#include <string>

Time::Time()
{
  std::string filename = "controlDict.inp";
  reader(filename, var);
  set();
  disp();
}

void Time::set()
{
  startTime = var["startTime"];
  dt = var["dt"];
  Nt = var["Nt"];
  writeInterval = var["writeInterval"];
}

void Time::disp() const
{
  std::cout << "Start Time: " << startTime << "(seconds)" << std::endl;
  std::cout << "dt: " << dt << "(change in time, seconds)" << std::endl;
  std::cout << "Nt: " << Nt << "(number of time iterations)" << std::endl;
  std::cout << "Write Interval: " << writeInterval << "(iterations)" << std::endl;
}

void Time::advance()
{
  timeStep = timeStep + 1;
  time = time + dt;
}

bool Time::run() const
{
  return (timeStep < Nt);
}

bool Time::writeNow() const
{
  return (timeStep % writeInterval == 0);
}
