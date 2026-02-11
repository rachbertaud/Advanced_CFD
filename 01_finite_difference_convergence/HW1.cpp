#include <iostream>
#include <cmath>
#include <fstream> //for data writing purposes

//defines namespace as std so we don't have to repeat it
using namespace std;

int main(int argc, char *argv[])
{
	//------------------------------- Question 1 ----------------------------------------
	cout << "---------------------------" << endl;
 	
	//user input for how many times they want to run the process (for how many N)
	const int stop = atoi(argv[1]) - 1;
 	cout << "stop = " << stop << endl;	
	//all file writing info referenced from https://stackoverflow.com/questions/25201131/writing-csv-files-from-c
	ofstream file;
	file.open ("HW1_Error_Data.csv"); //opens/makes data file
	file << "N, Err_inf, \n"; //writes header	


	//this for loops runs through the main code for different values of N, all multiples of 16
	for(int N = 16; N < (16*pow(2,stop) + 1); N *= 2){	
		//print out result of N to confirm we are getting the N we expect
		cout << "N = " << N << endl;
		
		//define pi as an unchangeable constant
		const double pi = 4.0*atan(1.0); //this line was referenced from CPP Companion
		
		//define L as 2*pi
		double L = 2*pi;

		//define h as N/L
		double h = L/static_cast<double>(N);
		//cout << "Checking L/N = " << L << "/" << N << " = " << h << " = h" << endl;

//------------------------------- Question 2 ----------------------------------------

		
		//define grid points
		double x[N];

		//define function points
		double f[N];

		//define numerical derivative array 
		double f_numerical[N];

		//define analytical derivative 
		double f_analytical[N];
		
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
				f_numerical[i] = (f[i + 1] - f[N - 1])/(2*h);
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
		
		//declare a difference matrix for error calculation
		double diff_f_sol[N]; 
		
		//define starting max values, can use 0 as we are taking fabs	
		double max_diff = 0;
		double max_analytical = 0;

		for(int i = 0; i < N; i++){
			//calculates the floating point absolute difference between our analytical and numerical solution
			diff_f_sol[i] = fabs(f_analytical[i] - f_numerical[i]);

			//checks to see if the current i-th entry of diff_f_sol is the maximum
			if(diff_f_sol[i] > max_diff){
				max_diff = diff_f_sol[i];
			}

			//determines maximum value of f_analytical
			if(fabs(f_analytical[i]) >  max_analytical){
				max_analytical = fabs(f_analytical[i]);
			}


		}
		
		double E_inf = max_diff/max_analytical;
		cout << "The global error, E_inf, is " << E_inf << endl;
		
		cout << "---------------------------" << endl;
		
		//writes current data to csv file
		file << N << "," << E_inf << ",\n";
	}
	
	file.close(); //closes csv file
	return 0;
	
//this ends main
}
