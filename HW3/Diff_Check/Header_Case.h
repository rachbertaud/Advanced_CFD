#ifndef HEADER_CASE_H
#define HEADER_CASE_H

#include <map>
#include <vector>
#include <string> 	//needed for string 

//---------------------------CASE FUNCTIONS----------------------------------------------
struct caseType{
	// material properties
	double rho, cp, k;

	//boundary temps 
	double Ts, Tn;
	
	//velocity field params.
	double A, bx, by;

	//source-term flag
	int src; //this will apply source when src=1
};

void read_inputs_case(std::map<std::string, double>& variables);

void readCase(caseType& Case);

void dispCase(const caseType& Case);

#endif
