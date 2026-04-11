#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_bcType.H"

//---------------------------MESH FUNCTIONS----------------------------------------------

bcType::bcType()
{
  double hi = 1;
}
void bcType::disp() const
{
  std::cout << "------------ BC DATA --------------" << std::endl;
  std::cout << "Vm     " << Vm << std::endl;
  std::cout << "k      " << k << std::endl;

}

bcType::bcType(std::string filename)
{
  std::map<std::string, double> var;
  std::string fileone = "Vel.inp";
  
  reader(fileone, var);
  reader(filename, var);

  Vm = var["Vm"];
  k = var["k"];

  disp();
  
  
  
  
}

void bcType::W(double y, double t, double& a, double& b, double& g) const
{
  // concentration is value of inlet at west wall (beg of membrane)
  double Cin = 0; //should be sin(y)*sin(x) here, but it's just 0
  a = 1;
  b = 0;
  g = Cin;
   
}

void bcType::E(double y, double t, double& a, double& b, double& g) const
{
  // concentration is zero on east wall (end of channel)
	a = 0; //const
	b = 1; // deriv
	g = std::cos(6.28)*std::sin(y);
}

void bcType::S(double x, double t, double& a, double& b, double& g) const
{
  a = -Vm;
  b = -k;
  g = -Vm*std::sin(x)*std::sin(0) - k*std::sin(x)*std::cos(0);; //Vm*sin(y)*sin(x) at south is 0 bc y = 0 here
}

void bcType::N(double x, double t, double& a, double& b, double& g) const
{
  a = Vm;
  b = -k;
  g = Vm*std::sin(x)*std::sin(6.28) - k*std::sin(x)*std::cos(6.28); 
}

