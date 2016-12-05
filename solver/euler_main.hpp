#ifndef EULER_MAIN_H
#define EULER_MAIN_H

#include "../global.hpp"
#include "euler_corrector.hpp"

struct Variables_Predictor {
	std::vector<double> rho_predictor;
	std::vector<double> v_predictor;
	std::vector<double> temperature_predictor;
};

class Euler_Main: public Euler_Corrector {

	private:
		Variables_Predictor vars_predictor;

		std::vector<double> drho_dt_predictor;
		std::vector<double> dv_dt_predictor;
		std::vector<double> dT_dt_predictor;

		std::vector<double> drho_dt_corrector;
		std::vector<double> dv_dt_corrector;
		std::vector<double> dT_dt_corrector;

		std::vector<double> drho_dt_average;
		std::vector<double> dv_dt_average;
		std::vector<double> dT_dt_average;

		std::vector<double> sound_speed_array;
		double delta_t;

		//calculate speed of sound
		std::vector<double> calc_main_sound_speed(Parameters &parameters, std::vector<double> temperature);

		//boundary condition functions
		void calc_main_bc_impose(Variables &vars, Parameters parameters);
		void calc_main_bc_impose(Variables_Predictor &vars_predictor, Parameters parameters);

		double calc_main_bc_neuman(double first_value, double second_value);
		double calc_main_bc_dirichlet(double value);

		//compute delta_t
		double calc_main_delta_t(Variables vars, std::vector<double> sound_speed, double cfl, int max_node);

		//main final function
		std::vector<double> calc_main_basic_formula(std::vector<double> F, std::vector<double> dF_dt, double delta_t, int max_node);

		//averaging function
		std::vector<double> calc_main_average(std::vector<double> dF_dt_predictor, std::vector<double> dF_dt_corrector, int max_node);

		//error computation
		double calc_main_error(std::vector<double> dF_dt_predictor, std::vector<double> dF_dt_corrector, int max_node);
	
	public:
		void calc_main_computation(Variables &vars, Parameters parameters);
	
	
	
};

#endif
