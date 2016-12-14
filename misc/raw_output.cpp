#include <sstream>
#include <fstream>
#include "raw_output.hpp"

void Raw_Output::print_raw_output(Variables vars, Parameters parameters) {

	//make local variables
	std::vector<double> x			=	vars.x;
	std::vector<double> area		=	vars.area;
	std::vector<double> rho			=	vars.rho;
	std::vector<double> temperature		=	vars.temperature;
	std::vector<double> v			=	vars.v;
	std::vector<double> pressure		=	vars.pressure;
	std::vector<double> mach		=	vars.mach;
	std::vector<double> mass_flow		=	vars.mass_flow;

	int max_node				=	parameters.max_node;

	std::ofstream ofs ("output/raw_output.dat", std::ofstream::out);
	
	for (auto i = 0; i < max_node; i++) {
		ofs << x[i] << " ";
		ofs << area[i] << " "; 
		ofs << rho[i] << " ";
		ofs << v[i] << " ";
		ofs << temperature[i] << " ";
		ofs << pressure[i] << " ";
		ofs << mach[i] << " ";
		ofs << mass_flow[i] << " ";
		ofs << std::endl;
	}


	ofs.close();

}
