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

//function for calc_main_bc_impose	->	imposing the BC function (FOR PREDICTOR -- overloading)
void Euler_Main::calc_main_bc_impose(Variables_Predictor &vars_predictor, Parameters parameters) {
	
	//make local variables
	std::vector<double> &rho		=	vars_predictor.rho_predictor;
	std::vector<double> &v			=	vars_predictor.v_predictor;
	std::vector<double> &temperature	=	vars_predictor.temperature_predictor;

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
	std::vector<double> delta_t_array(max_node);

	//make local variables
	std::vector<double> v		=	vars.v;
	double delta_x			=	vars.delta_x;

	//compute delta_x
	for (auto i = 0; i < max_node; i++) {
		double temp = cfl*(delta_x/(v[i] + sound_speed[i]));
		delta_t_array[i] = temp;
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

std::vector<double> Euler_Main::calc_main_basic_formula(std::vector<double> F, std::vector<double> dF_dt, double delta_t, int max_node) {
	
	std::vector<double> new_F(max_node);

	for (auto i = 0; i < max_node; i++) {
		new_F[i]	=	F[i] + dF_dt[i]*delta_t;
	}

	return new_F;
}

//function for calc_main_average
std::vector<double> Euler_Main::calc_main_average(std::vector<double> dF_dt_predictor, std::vector<double> dF_dt_corrector, int max_node) {

	std::vector<double> dF_dt_average(max_node);
	for (auto i = 0; i < max_node; i++) {
		dF_dt_average[i]	=	0.5*(dF_dt_predictor[i] + dF_dt_corrector[i]);
	}
	return dF_dt_average;
}

double Euler_Main::calc_main_error(std::vector<double> dF_dt_predictor, std::vector<double> dF_dt_corrector, int max_node) {
	
	double error;
		
		//do root mean square
		for (auto i = 0; i < max_node; i++) {
			
			double temp_error 	= 	pow(0.5*(dF_dt_predictor[i] + dF_dt_corrector[i]), 2);
			error 			=	error + temp_error;
		}
		error	=	error/max_node;
		error	=	sqrt(error);

	return error;
}

//function for calc_main_computation	->	main looping function
void Euler_Main::calc_main_computation(Variables &vars, Parameters parameters) {
	

	//make new local variables
	std::vector<double> &rho		=	vars.rho;
	std::vector<double> &v			=	vars.v;
	std::vector<double> &temperature	=	vars.temperature;
	
	int max_node				=	parameters.max_node;
	int max_iter				=	parameters.max_iter;
	double cfl				=	parameters.cfl;
	double gamma				=	parameters.gamma;
	double error_max			=	parameters.error_max;

	double error;
	int iteration_count = 0;

	std::vector<double> &rho_predictor		=	vars_predictor.rho_predictor;
	std::vector<double> &v_predictor		=	vars_predictor.v_predictor;
	std::vector<double> &temperature_predictor	=	vars_predictor.temperature_predictor;

	do {
		iteration_count++;
	
		//impose BC before predictor scheme
		calc_main_bc_impose(vars, parameters);
	
		//compute delta_t
		sound_speed_array	=	calc_main_sound_speed(parameters, temperature);
		delta_t			=	calc_main_delta_t(vars, sound_speed_array, cfl, max_node);
		
		//predictor step
			drho_dt_predictor	=	calc_predictor_continuity(vars, max_node);
		dv_dt_predictor		=	calc_predictor_momentum(vars, gamma, max_node);
		dT_dt_predictor		=	calc_predictor_energy(vars, gamma, max_node);
	
		//compute new variable
		rho_predictor		=	calc_main_basic_formula(rho, drho_dt_predictor, delta_t, max_node);
		v_predictor		=	calc_main_basic_formula(v, dv_dt_predictor, delta_t, max_node);
		temperature_predictor	=	calc_main_basic_formula(temperature, dT_dt_predictor, delta_t, max_node);
	
		//impose BC before corrector scheme	-> use Variables_Predictor class instead of Variables (overloading)
		calc_main_bc_impose(vars_predictor, parameters);
	
		//corrector step
		drho_dt_corrector	=	calc_corrector_continuity(vars_predictor, vars,  max_node);
		dv_dt_corrector		=	calc_corrector_momentum(vars_predictor, vars,  gamma, max_node);
		dT_dt_corrector		=	calc_corrector_energy(vars_predictor, vars,  gamma, max_node);
		
		//compute the average
		drho_dt_average		=	calc_main_average(drho_dt_predictor, drho_dt_corrector, max_node);
		dv_dt_average		=	calc_main_average(dv_dt_predictor, dv_dt_corrector, max_node);
		dT_dt_average		=	calc_main_average(dT_dt_predictor, dT_dt_corrector, max_node);
	
		//compute new variable
		rho			=	calc_main_basic_formula(rho, drho_dt_average, delta_t, max_node);
		v			=	calc_main_basic_formula(v, dv_dt_average, delta_t, max_node);
		temperature		=	calc_main_basic_formula(temperature, dT_dt_average, delta_t, max_node);
	
		//compute error
		error		=	calc_main_error(drho_dt_predictor, drho_dt_corrector, max_node);

		std::cout << iteration_count << std::endl;
		for (auto i = 0; i < max_node; i++) {
			std::cout << rho[i] << " " << v[i] << " " << temperature[i] << std::endl;
		}
		std::cout << "THE ERROR: " << error << " " << error_max << std::endl;
		std::cout << std::endl;

		if (iteration_count > max_iter) break;
	} while(error > error_max);

}

