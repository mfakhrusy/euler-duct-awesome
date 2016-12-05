#ifndef INITIALIZATION_H 
#define INITIALIZATION_H

#include "../global.hpp"

class Initialization {
	private:
		//calculation of some parameters which based on input parameters
		void calc_input(Parameters &parameters, Variables &vars);

		//calculate some variables for the computation
		double calc_stretching(int max_node, int index);
		double calc_sound_speed(double gamma, double gas_constant, double temperature);
		double calc_area(double x);

		//initial condition calculations
		std::vector<double> calc_grid_point(double ref_length, double init_position, int max_node);
		std::vector<double> calc_area_point(std::vector<double> x, int max_node);
		std::vector<double> calc_density_point(std::vector<double> x, int max_node);
		std::vector<double> calc_temperature_point(std::vector<double> x, int max_node);
		std::vector<double> calc_velocity_point(std::vector<double> x, std::vector<double> temperature, int max_node);

	
	public:
		//2 function for reading input and the other is for calculation of initial conditions
		void read_input(Parameters &parameters);
		void calc_initialization_main(Variables &vars, Parameters &parameters);

};

#endif
