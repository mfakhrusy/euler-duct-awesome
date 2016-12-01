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

//function calc_sound_speed_array
std::vector<double> Euler_Main::calc_main_sound_speed(Parameters &parameters, std::vector<double> temperature) {

	std::vector<double> sound_speed;

	//initialize local variables
	int max_node		=	parameters.max_node;
	double gamma		=	parameters.gamma;
	double gas_constant	=	parameters.gas_constant;

	for (auto i = 0; i < max_node; i++) {
		sound_speed.push_back(sqrt(gamma*gas_constant*temperature[i]));
	}

	return sound_speed;

}

//function for calc_main_delta_t
double Euler_Main::calc_main_delta_t(Variables vars, std::vector<double> sound_speed, double cfl, int max_node) {
	
	double delta_t_final;
	std::vector<double> delta_t_array(max_node + 1);

	//make local variables
	std::vector<double> v		=	vars.v;
	double delta_x			=	vars.delta_x;

	//compute delta_x
	for (auto i = 0; i < max_node; i++) {
		double temp = cfl*(delta_x/(v[i] + sound_speed[i]));
		delta_t_array[0] = temp;
	}

	delta_t_final	=	delta_t_array[0];

	//take the smallest value
	for (auto i = 1; i < max_node; i++) {
		if (delta_t_final > delta_t_array[i]) {
			delta_t_final = delta_t_array[i];
		}
	}

	return delta_t_final;
}

std::vector<double> calc_main_basic_formula(std::vector<double> F, std::vector<double> dF_dt, double delta_t, int max_node) {
	
	std::vector<double> new_F(max_node + 1);

	for (auto i = 0; i < max_node; i++) {
		new_F[i]	=	F[i] + dF_dt[i]*delta_t;
	}

	return new_F;
}

//function for calc_main_computation	->	main looping function
void Euler_Main::calc_main_computation(Variables &vars, Parameters parameters) {
	
	//impose BC before predictor scheme
	calc_main_bc_impose(vars, parameters);

	//predictor step
	drho_dt_predictor	=	calc_predictor_continuity(vars, parameters.max_node);
	dv_dt_predictor		=	calc_predictor_momentum(vars, parameters.gamma, parameters.max_node);
	dT_dt_predictor		=	calc_predictor_energy(vars, parameters.gamma, parameters.max_node);

	//compute new variable
	sound_speed_array	=	calc_main_sound_speed(parameters, vars.temperature);
	delta_t			=	calc_main_delta_t(vars, sound_speed_array, parameters.cfl, parameters.max_node);
	
	
	
	
	//do something
}

