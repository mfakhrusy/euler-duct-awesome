#ifndef EULER_MAIN_H
#define EULER_MAIN_H

#include "../global.hpp"
#include "euler_corrector.hpp"

class Euler_Main: protected Euler_Corrector  {
	private:
		double calc_main_bc_neuman(double first_value, double second_value);
		double calc_main_bc_dirichlet(double value);
		void calc_main_bc_impose(Variables &vars, Parameters parameters);
	
	public:
		void calc_main_computation(Variables &vars, Parameters parameters);
	
	
	
};

#endif
