#ifndef EULER_CORRECTOR_H
#define EULER_CORRECTOR_H

#include "../global.hpp"
#include "euler_predictor.hpp"

//forward struct declaration
struct Variables_Predictor;

class Euler_Corrector: protected Euler_Predictor {

	protected:		
		//three function below ONLY appear in euler_main (not main), so protected is better
		std::vector<double> calc_corrector_continuity(Variables_Predictor vars_predictor, Variables vars, int max_node);
		std::vector<double> calc_corrector_momentum(Variables_Predictor vars_predictor, Variables vars, double gamma, int max_node);
		std::vector<double> calc_corrector_energy(Variables_Predictor vars_predictor, Variables vars, double gamma, int max_node);
};

#endif
