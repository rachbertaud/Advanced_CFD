#include <iostream>
#include <cmath>

int main(int argc, char *argv[])
{
	//------------------------------- Question 1 ----------------------------------------

	//define N using user-input in float form and in as an int > this might not be necessary and should be changed later but lets see what happens 
 
	double N = atof(argv[1]);
	const int N_int = atoi(argv[1]);
	
	//print out result of N to confirm we are getting the N we expect
	std::cout << "N =" << N << std::endl;
	
	//define pi as an unchangeable constant
	const double pi = 4.0*std::atan(1.0); //this line was referenced from CPP Companion
	
	//define L as 2*pi
	double L = 2*pi;

	//define h as N/L
	double h = L/N;
	std::cout << "Checking L/N = " << L << "/" << N << " = " << h << " = h" << std::endl;

	//------------------------------- Question 2 ----------------------------------------

	
	//define grid points
	double x[N_int]

	//define function points
	double f[N]


}
