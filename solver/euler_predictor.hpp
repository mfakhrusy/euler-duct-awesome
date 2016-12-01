#ifndef EULER_PREDICTOR_H
#define EULER_PREDICTOR_H

#include "../global.hpp"

class Euler_Predictor {
	private:
		

	protected:		
		//three function below ONLY appear in euler_main (not main), so protected is better
		std::vector<double> calc_predictor_continuity(Variables vars, int max_node);
		std::vector<double> calc_predictor_momentum(Variables vars, double gamma, int max_node);
		std::vector<double> calc_predictor_energy(Variables vars, double gamma, int max_node);



};

#endif
