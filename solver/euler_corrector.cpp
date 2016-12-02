#include "../global.hpp"
#include "euler_corrector.hpp"
#include "euler_main.hpp"

std::vector<double> Euler_Corrector::calc_corrector_continuity(Variables_Predictor vars_predictor, 
		Variables vars,
		int max_node) {
	
	std::vector<double> drho_dt(max_node);
	
	//make local variables
	std::vector<double> &rho	=	vars_predictor.rho_predictor;
	std::vector<double> &v		=	vars_predictor.v_predictor;
	std::vector<double> &area	=	vars.area;
	double &delta_x			=	vars.delta_x;

	drho_dt[0]		=	0;
	for (auto i = 1; i < max_node; i++) {	//from 1 until max_node - 1 because the edge will be calculated via BC
		double drho_dt_1 = -1*rho[i]*((v[i] - v[i-1])/delta_x);
		double drho_dt_2 = -1*v[i]*((rho[i] - rho[i-1])/delta_x);
		double drho_dt_3 = -1*rho[i]*v[i]*((log(area[i]) - log(area[i-1]))/delta_x);
		
		drho_dt[i] = drho_dt_1 + drho_dt_2 + drho_dt_3;
	}
	drho_dt[max_node - 1]	=	0;

	return drho_dt;
}

std::vector<double> Euler_Corrector::calc_corrector_momentum(Variables_Predictor vars_predictor, 
		Variables vars,
		double gamma,
		int max_node) {
	
	std::vector<double> dv_dt(max_node);
	
	//make local variables
	std::vector<double> &rho		=	vars_predictor.rho_predictor;
	std::vector<double> &v			=	vars_predictor.v_predictor;
	std::vector<double> &temperature	=	vars_predictor.temperature_predictor;
	std::vector<double> &area		=	vars.area;
	double &delta_x				=	vars.delta_x;

	dv_dt[0]	=	0;
	for (auto i = 1; i < max_node; i++) {	//from 1 until max_node - 1 because the edge will be calculated via BC
		double dv_dt_1 = -1*v[i]*((v[i] - v[i-1])/delta_x); 
		double dv_dt_2 = (temperature[i] - temperature[i-1])/delta_x;
		double dv_dt_3 = (temperature[i]/rho[i])*((rho[i] - rho[i-1])/delta_x);
		
		dv_dt[i] = dv_dt_1 - (1/gamma)*(dv_dt_2 + dv_dt_3);
	}
	dv_dt[max_node - 1]	=	0;

	return dv_dt;}

std::vector<double> Euler_Corrector::calc_corrector_energy(Variables_Predictor vars_predictor, 
		Variables vars,
		double gamma,
		int max_node) {
	
	std::vector<double> dT_dt(max_node);
	
	//make local variables
	std::vector<double> &v			=	vars_predictor.v_predictor;
	std::vector<double> &temperature	=	vars_predictor.temperature_predictor;
	std::vector<double> &area		=	vars.area;
	double &delta_x				=	vars.delta_x;

	dT_dt[0]	=	0;
	for (auto i = 1; i < max_node; i++) {	//from 1 until max_node - 1 because the edge will be calculated via BC
		double dT_dt_1 = -1*v[i]*((temperature[i] - temperature[i-1])/delta_x);
		double dT_dt_2 = -1*(gamma - 1)*temperature[i];
		double dT_dt_3 = (v[i] - v[i-1])/delta_x;
		double dT_dt_4 = v[i]*((log(area[i]) - log(area[i-1]))/delta_x);

		dT_dt[i] = dT_dt_1 + dT_dt_2*(dT_dt_3 + dT_dt_4);

	}
	dT_dt[max_node - 1]	=	0;

	return dT_dt;
}




