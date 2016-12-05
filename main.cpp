#include "global.hpp"
#include "misc/initialization.hpp"
#include "solver/euler_main.hpp"

int main() {
	
	//classes and struct definitions
	Parameters parameters;
	Variables vars;
	Initialization inits;
	Euler_Main euler_main;

	//initialization process
	inits.read_input(parameters);
	
	//initialization process
	inits.calc_initialization_main(vars, parameters);

	//main computation process
	euler_main.calc_main_computation(vars, parameters);
}
