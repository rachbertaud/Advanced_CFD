#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_bcType.H"

//---------------------------MESH FUNCTIONS----------------------------------------------

void bcType::disp() const
{
  std::cout << "------------ BC DATA --------------" << std::endl;
  std::cout << "Vm     " << Vm << std::endl;
  std::cout << "k      " << k << std::endl;

}

bcType::bcType(std::string& filename)
{
  std::map<std::string, double> var;
  std::string fileone = "Vel.inp";
  
  reader(fileone, var);
  reader(filename, var);

  Vm = var["Vm"];
  k = var["k"];
  
  
  
  
}

void bcType::W(double y, double t, double& a, double& b, double& g) const
{
  // concentration is value of inlet at west wall (beg of membrane)
  double Cin = 1.0;
  a = 0;
  b = 1;
  g = Cin;
   
}

void bcType::E(double y, double t, double& a, double& b, double& g) const
{
  // concentration is zero on east wall (end of channel)
	a = 1; //const
	b = 0; // deriv
	g = 0;
}

void bcType::S(double x, double t, double& a, double& b, double& g) const
{
  a = -Vm;
  b = -k;
  g = 0;
}

void bcType::N(double x, double t, double& a, double& b, double& g) const
{
  a = Vm;
  b = -k;
  g = 0; 
}

