#include "global.hpp"
#include "misc/initialization.hpp"
#include "solver/euler_main.hpp"
#include "misc/raw_output.hpp"

int main() {
	
	//classes and structs definitions
	Parameters parameters;
	Variables vars;
	Initialization inits;
	Euler_Main euler_main;
	Raw_Output outputs;

	std::cout << "Computation: STARTED! " << std::endl;

	//initialization process
	inits.read_input(parameters);
	
	//initialization process
	inits.calc_initialization_main(vars, parameters);

	std::cout << " ... ... ..." << std::endl;

	//main computation process
	euler_main.calc_main_computation(vars, parameters);

	//print the result to external file
	outputs.print_raw_output(vars, parameters);

	std::cout << "Computation: FINISHED! " << std::endl;
}
