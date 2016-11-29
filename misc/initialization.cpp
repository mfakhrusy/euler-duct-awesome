#include "../global.hpp"
#include "initialization.hpp"

void Initialization::read_input() {
	std::ifstream input_file;
	input_file.open("input/input.dat");

	if (input_file.is_open()) {
		


	} else {
		std::cout << "Input File is not found." << std::endl;
	}
}
