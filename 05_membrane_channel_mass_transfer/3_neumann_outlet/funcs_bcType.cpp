#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files
#include <iostream> 	//needed for cout

#include "Header_bcType.H"
#include "Header_Mesh.H"

//---------------------------MESH FUNCTIONS----------------------------------------------

bcType::bcType()
{
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

  //std::map<std::string, double> meshname;
  //std::string mesh = "Mesh.inp";
  
  reader(fileone, var);
  reader(filename, var);
  //reader(mesh, var);

  Vm = var["Vm"];
  k = var["k"];
  

  disp();
  
  
  
  
}

void bcType::W(double y, double t, double& a, double& b, double& g) const
{
  // concentration is value of inlet at west wall (beg of membrane)
  double Cin = 1; //should be sin(y)*sin(x) here, but it's just 0
  a = 1;
  b = 0;
  g = Cin;
   
}

void bcType::E(double y, double t, double& a, double& b, double& g) const
{
  // concentration is zero on east wall (end of channel)
	a = 0; //const
	b = 1; // deriv
	
//	double out = (y1 + ((x - x1)*((y2 - y1)/(x2 - x1))))
	g = 0;
}

void bcType::S(double x, double t, double& a, double& b, double& g) const
{
  a = -Vm;
  b = k;
  g = 0;
}

void bcType::N(double x, double t, double& a, double& b, double& g) const
{
  a = Vm;
  b = -k;
  g = 0;
}

