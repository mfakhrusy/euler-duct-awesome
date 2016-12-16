#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <cmath>
#include <vector>

struct Parameters {

	//from input.dat
	int max_node;
	int max_iter;
	double error_max;
	double gamma;
	double gas_constant;
	double cfl; 			//courant number
	double total_temperature;
	double total_density;
	double ref_length;

	//3 values below is the initial condition of calculation
	double initial_temperature;
	double initial_density;
	double initial_velocity;

	//computed value
	double total_sound_speed;
	double throat_area;
	double ref_time;

};

struct Variables {

	std::vector<double> x;
	std::vector<double> v;
	std::vector<double> t;
	std::vector<double> rho;
	std::vector<double> temperature;
	std::vector<double> area;
	std::vector<double> pressure;
	std::vector<double> mach;
	std::vector<double> mass_flow;
	
	//assume: homogeneous delta_x
	double delta_x;

	//variables for error for each time step
	std::vector<double> error_comp;

};


#endif
