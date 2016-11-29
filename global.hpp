#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

struct Parameters {

	//from input.dat
	int max_node;
	int max_iter;
	double error_max;
	double gamma;
	double gas_constant;
	double total_temperature;
	double total_density;
	double ref_length;

	//computed value
	double total_sound_speed;
	double throat_area;
	double reference_time;

};


#endif
