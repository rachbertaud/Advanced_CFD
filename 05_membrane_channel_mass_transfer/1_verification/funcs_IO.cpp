#include "Header_IO.H"

#include <sstream> 	// needed for stringstream
#include <string> 	//needed for string 
#include <map>		// for variable map definition
#include <fstream> 	// helps us read files

void reader(std::string& filename, std::map<std::string, double>& var)
{
  //define a string 
	std::string line;
	std::string var_name;

	//open the input file 
	std::ifstream inputfile;
	
	inputfile.open(filename);

		double value;
	int i = 0;
	
	while(std::getline(inputfile, line))
	{
		if(line=="endfile") break;
		
		if(i % 2 == 0){
			std::stringstream(line) >> var_name;
		}
		else{
			std::stringstream(line) >> value;
			var[var_name] = value;
		}
		
		i++;
	}

	inputfile.close();  
};

double retriever(std::string& name, std::map<std::string, double>& var)
{
  return var[name];
};
