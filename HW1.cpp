#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
	//------------------------------- Question 1 ----------------------------------------
	cout << "---------------------------" << endl;
	//define N using user-input in float form and in as an int > this might not be necessary and should be changed later but lets see what happens 
 
	double N = atof(argv[1]);
	const int N_int = atoi(argv[1]);
	
	//print out result of N to confirm we are getting the N we expect
	cout << "N =" << N << endl;
	
	//define pi as an unchangeable constant
	const double pi = 4.0*atan(1.0); //this line was referenced from CPP Companion
	
	//define L as 2*pi
	double L = 2*pi;

	//define h as N/L
	double h = L/N;
	cout << "Checking L/N = " << L << "/" << N << " = " << h << " = h" << endl;

	//------------------------------- Question 2 ----------------------------------------

	
	//define grid points
	double x[N_int];

	//define function points
	double f[N_int];

	//define numerical derivative array 
	double f_numerical[N_int];

	//define analytical derivative 
	double f_analytical[N_int];
	
	//define 2pi/L so I don't have to write it 13 times
	double C = (2*pi)/L; 

	for(int i=0; i < N; i++){
		x[i] = i*h; //declares the grid point by using h
		f[i] = exp(sin(C*x[i])); //declares function we wish to evaluate the derivative of
		f_analytical[i] = C*cos(C*x[i])*exp(sin(C*x[i])); //declares teh analytical solution to f
	}

	//------------------------------- Question 3 ----------------------------------------

	for(int i = 0; i < N; i ++){
		if(i == 0){
			//if I'm on the left boundary, I want the last input of f
			f_numerical[i] = (f[i + 1] - f[-1])/(2*h);
		}
		else if (i == (N - 1)){
			//if I'm at my right boundary, I want my first input of f
			f_numerical[i] = (f[0] - f[i - 1])/(2*h);
		}
		else{
			//else,I just want my neighbors
			f_numerical[i] = (f[i + 1] - f[i - 1])/(2*h);
		}
	}
	
	//------------------------------- Question 4 ----------------------------------------
	
	double diff_f_sol = 
	
	
	cout << "---------------------------" << endl;
//this ends main
}
