#include "../global.hpp"
#include "initialization.hpp"

//function nondimensionalization
void Initialization::nondimensionalization(std::vector<double> &var, double ref) {
	
	for (auto i = 0; i < var.size(); i++) {
		var[i]	=	var[i]/ref;
	}
}

//function read_input
void Initialization::read_input(Parameters &parameters) {

	std::ifstream input_file;
	input_file.open("input/input.dat");

	if (input_file.is_open()) {
		std::string line;
		int count = 0;
		while (std::getline(input_file,line)) {
			count = count + 1;
			double value;
			std::string label;
			std::istringstream iss(line);

			iss >> value >> label;

			switch(count) {
				case 1:
					parameters.max_node = static_cast<int>(value);
					break;
				case 2:
					parameters.max_iter = static_cast<int>(value);
					break;
				case 3:
					parameters.error_max = value;
					break;
				case 4:
					parameters.gamma = value;
					break;
				case 5:
					parameters.gas_constant = value;
					break;
				case 6:
					parameters.cfl = value;
					break;
				case 7:
					parameters.total_temperature = value;
					break;
				case 8:
					parameters.total_density = value;
					break;
				case 9:
					parameters.ref_length = value;
					break;
				case 10:
					parameters.initial_temperature = value;
					break;
				case 11:
					parameters.initial_density = value;
					break;
				case 12:
					parameters.initial_velocity = value;
					break;
				default:
					std::cout << "sup!" << std::endl;
			}
		}

	} else {
		std::cout << "Input File is not found." << std::endl;
	}
}

//function calc_input
void Initialization::calc_input (Parameters &parameters, Variables &vars) {
	parameters.total_sound_speed	=	calc_sound_speed(parameters.gamma, parameters.gas_constant, parameters.total_temperature);
	parameters.ref_time		=	parameters.ref_length/parameters.total_sound_speed;
	parameters.throat_area		=	vars.area[((vars.area.size() - 1)/2)];
}

//function calc_sound_speed
double Initialization::calc_sound_speed (double gamma, double gas_constant, double temperature) {
	return sqrt(gamma*gas_constant*temperature);
}

//function calc_stretching
double Initialization::calc_stretching (int max_node, int index) { //homogeneous stretching
	return static_cast<double>(index)/static_cast<double>(max_node - 1);	//index start from 0
}

//function calc_area
double Initialization::calc_area (double x) {
	return 1 + 2.2*pow((x - 1.5), 2);
}

//function calc_grid_point
std::vector<double> Initialization::calc_grid_point (double ref_length, double init_position, int max_node) {
	
	//calculate grid function
	std::vector<double> x;
	for (auto i = 0; i < max_node; i++) {
		double temp = (init_position*(1 - calc_stretching(max_node, i)) + calc_stretching(max_node, i)*ref_length); //non dimensional
		x.push_back(temp);
	}
	return x;
}

//function calc_area_point
std::vector<double> Initialization::calc_area_point (std::vector<double> x, int max_node) {

	std::vector<double> area;
	for (auto i = 0; i < max_node; i++) {
		area.push_back(calc_area(x[i]));
	}

	return area;
}

//function calc_density_point
std::vector<double> Initialization::calc_density_point (double initial_density, int max_node) {
	
	std::vector<double> density;
	for (auto i = 0; i < max_node; i++) {
		density.push_back(initial_density);
	}
	return density;
}

//function calc_velocity_point
std::vector<double> Initialization::calc_velocity_point (double initial_velocity, int max_node) {
	
	std::vector<double> velocity;
	for (auto i = 0; i < max_node; i++) {
		velocity.push_back(initial_velocity);
	}
	return velocity;
}

//function calc_temperature_point
std::vector<double> Initialization::calc_temperature_point (double initial_temperature, int max_node) {
	
	std::vector<double> temperature;
	for (auto i = 0; i < max_node; i++) {
		temperature.push_back(initial_temperature);
	}
	return temperature;
}
