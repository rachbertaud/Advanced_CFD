#ifndef READ_INPUTS_H
#define READ_INPUTS_H

#include <map>
#include <string>

void read_inputs(std::map<std::string, double>& variables);

double var_therm_cond(double x, double y);

double find_r(double x, double y, double Lx, double Ly);

double fuel_therm_cond(double x, double y, double Lx, double Ly, double R1, double R2, double k1, double k2, double k3);

double source(double r, double a, double b, double R1);

#endif
