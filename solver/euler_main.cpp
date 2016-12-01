#include "../global.hpp"
#include "euler_main.hpp"
#include "euler_predictor.hpp"

//function for calc_main_bc_neuman	->	function for neuman boundary condition
double Euler_Main::calc_main_bc_neuman(double first_value, double second_value) {
	return 2*first_value - second_value;
}

//function for calc_main_bc_dirichlet	->	function for dirichlet boundary condition
double Euler_Main::calc_main_bc_dirichlet(double value) {
	return value;
}

//function for calc_main_bc_impose	->	imposing the BC function
void Euler_Main::calc_main_bc_impose(Variables &vars, Parameters parameters) {
	
	//make local variables
	std::vector<double> &rho		=	vars.rho;
	std::vector<double> &v			=	vars.v;
	std::vector<double> &temperature	=	vars.temperature;

	double density_bc_dirichlet		=	parameters.initial_density/parameters.total_density;		//nondimensional
	double temperature_bc_dirichlet		=	parameters.initial_temperature/parameters.total_temperature;	//nondimensional
	double max_node				=	parameters.max_node;

	//first, for density. Dirichlet on inlet, neuman on outlet
	rho[0]				=	calc_main_bc_dirichlet(density_bc_dirichlet);
	rho[max_node - 1]		=	calc_main_bc_neuman(rho[max_node - 2], rho[max_node - 3]);

	//velocity. Both neuman (inlet & outlet)
	v[0]				=	calc_main_bc_neuman(v[1], v[2]);
	v[max_node - 1]			=	calc_main_bc_neuman(v[max_node - 2], v[max_node - 3]);

	//temperature, dirichlet inlet, neuman outlet
	temperature[0]			=	calc_main_bc_dirichlet(temperature_bc_dirichlet);
	temperature[max_node - 1]	=	calc_main_bc_neuman(temperature[max_node - 2], temperature[max_node - 3]);
	
}

//function for calc_main_computation	->	main looping function
void Euler_Main::calc_main_computation(Variables &vars, Parameters parameters) {
	
	//impose BC before predictor scheme
	calc_main_bc_impose(vars, parameters);

	//predictor step
	
	//do something
}

