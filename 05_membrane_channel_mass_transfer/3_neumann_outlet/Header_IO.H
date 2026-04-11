#ifndef HEADER_IO_H
#define HEADER_IO_H

#include <string> 	//needed for string 
#include <map>		// for variable map definition

void reader(std::string& filename, std::map<std::string, double>& var);

double retriever(std::string& name, std::map<std::string, double>& var);


#endif

