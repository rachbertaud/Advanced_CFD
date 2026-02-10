#ifndef READ_INPUTS_H
#define READ_INPUTS_H

#include <map>
#include <string>

void read_inputs(std::map<std::string, double>& variables);

double var_therm_cond(double x, double y);

double fuel_therm_cond(double x, double y);

#endif
