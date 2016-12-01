#include "global.hpp"
#include "misc/initialization.hpp"
#include "solver/euler_main.hpp"

int main() {
	
	//class and struct definitions
	Parameters parameters;
	Variables vars;
	Initialization inits;
	Euler_Main euler_main;

	//initialization process
	inits.read_input(parameters);
	
	//define local vars
	const int &max_node			=	parameters.max_node;
	const int &max_iter			=	parameters.max_iter;
	const double &error_max			=	parameters.error_max;
	const double &gamma			=	parameters.gamma;
	const double &gas_constant		=	parameters.gas_constant;
	const double &cfl			=	parameters.cfl;
	const double &total_temperature		=	parameters.total_temperature;
	const double &total_density		=	parameters.total_density;
	const double &ref_length		=	parameters.ref_length;
	const double &initial_density		=	parameters.initial_density;
	const double &initial_velocity		=	parameters.initial_velocity;
	const double &initial_temperature	=	parameters.initial_temperature;
	
	//initialize grid and area
	vars.x 					=	inits.calc_grid_point(ref_length, 0, max_node);
	vars.area				=	inits.calc_area_point(vars.x, max_node);
	vars.delta_x				=	vars.x[1] - vars.x[0];	//can be anything since it's homogeneous

	//initialization process -- computed
	inits.calc_input(parameters, vars);

	//define local vars -- computed
	const double &total_sound_speed		=	parameters.total_sound_speed;
	const double &ref_time			=	parameters.ref_time;
	const double &throat_area		=	parameters.throat_area;

	//initialize density, velocity, and temperature
	vars.rho				=	inits.calc_density_point(initial_density, max_node);
	vars.v					=	inits.calc_velocity_point(initial_velocity, max_node);
	vars.temperature			=	inits.calc_temperature_point(initial_temperature, max_node);

	//initalize the local variable
	std::vector<double> &x			=	vars.x;
	std::vector<double> &area		=	vars.area;
	std::vector<double> &rho		=	vars.rho;
	std::vector<double> &v			=	vars.v;
	std::vector<double> &temperature	=	vars.temperature;
	double &delta_x				=	vars.delta_x;

	//nondimensionalize the variables
	inits.nondimensionalization(x, ref_length);
	inits.nondimensionalization(area, throat_area);
	inits.nondimensionalization(rho, total_density);
	inits.nondimensionalization(v, total_sound_speed);
	inits.nondimensionalization(temperature, total_temperature);

//	for (auto i = 0; i<x.size(); i++) {
//		std::cout << i << " " << x[i] << " " << area[i] << " " << rho[i] << " " << v[i] << " " << temperature[i] << " " << std::endl;
//	}

	//main computation process
	euler_main.calc_main_computation(vars, parameters);
}
