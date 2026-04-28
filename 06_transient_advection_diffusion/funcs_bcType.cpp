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

bcType::bcType(double Crho, double Ck, double Ccp, double Com, double Ctime)
{
  
  k = Ck;
  rho = Crho;
  cp = Ccp;
  omega = Com;
  time = Ctime;

}

void bcType::W(double y, double t, double& a, double& b, double& g) const
{
  // concentration is value of inlet at west wall (beg of membrane)
  double Cin = std::cos(y)*std::cos(omega*t); //should be sin(y)*sin(x) here, but it's just 0
  a = 1;
  b = 0;
  g = Cin;
   
}

void bcType::E(double y, double t, double& a, double& b, double& g) const
{
  // concentration is zero on east wall (end of channel)
  double Cout = std::cos(y)*std::cos(omega*t);
	a = 1; //const
	b = 0; // deriv
	
//	double out = (y1 + ((x - x1)*((y2 - y1)/(x2 - x1))))
	g = Cout;
}

void bcType::S(double x, double t, double& a, double& b, double& g) const
{
  double Cin = std::cos(x)*std::cos(omega*t);
  a = 1;
  b = 0;
  g = Cin;
}

void bcType::N(double x, double t, double& a, double& b, double& g) const
{
  double Cout = std::cos(x)*std::cos(omega*t);
  a = 1;
  b = 0;
  g = Cout;
}

