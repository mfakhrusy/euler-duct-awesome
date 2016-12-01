#ifndef INITIALIZATION_H 
#define INITIALIZATION_H

#include "../global.hpp"

class Initialization {
	private:
		double calc_stretching(int max_node, int index);
		
	public:
		//two function of nondimensionalize depends on input --> function overloading
		void nondimensionalization(std::vector<double> &var, double ref);
		void nondimensionalization(double &var, double ref);

		void read_input(Parameters &parameters);
		void calc_input(Parameters &parameters, Variables &vars);
		double calc_sound_speed(double gamma, double gas_constant, double temperature);
		double calc_area(double x);

		std::vector<double> calc_grid_point(double ref_length, double init_position, int max_node);
		std::vector<double> calc_area_point(std::vector<double> x, int max_node);
		std::vector<double> calc_density_point(double initial_density, int max_node);
		std::vector<double> calc_velocity_point(double initial_velocity, int max_node);
		std::vector<double> calc_temperature_point(double initial_temperature, int max_node);

};

#endif
