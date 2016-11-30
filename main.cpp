#include "global.hpp"
#include "misc/initialization.hpp"

int main() {
	
	//class and struct definitions
	Parameters parameters;
	Variables vars;
	Initialization inits;

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
	
	//initialize grid 
	vars.x 					=	inits.calc_grid_point(ref_length, 0, max_node);
	vars.area				=	inits.calc_area_point(vars.x, max_node);

	//initialization process -- computed
	inits.calc_input(parameters, vars);

	//define local vars -- computed
	const double &total_sound_speed		=	parameters.total_sound_speed;
	const double &ref_time			=	parameters.ref_time;
	const double &throat_area		=	parameters.throat_area;

	//initialize density, velocity, and temperature
	vars.rho				=	inits.calc_density_point(initial_density, max_node);
	vars.v					=	inits.calc_density_point(initial_velocity, max_node);
	vars.temperature			=	inits.calc_density_point(initial_temperature, max_node);


	//initalize the local variable
	std::vector<double> &x			=	vars.x;
	std::vector<double> &area		=	vars.area;
	std::vector<double> &rho		=	vars.rho;
	std::vector<double> &v			=	vars.v;
	std::vector<double> &temperature	=	vars.temperature;

	//nondimensionalize the variables
	inits.nondimensionalization(x, ref_length);
	inits.nondimensionalization(area, throat_area);
	inits.nondimensionalization(rho, total_density);
	inits.nondimensionalization(v, total_sound_speed);
	inits.nondimensionalization(temperature, total_temperature);

//	for (auto i = 0; i<x.size(); i++) {
//		std::cout << i << " " << x[i] << " " << area[i] << " " << rho[i] << " " << v[i] << " " << temperature[i] << " " << std::endl;
//	}



	
}
