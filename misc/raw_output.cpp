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

	std::ofstream ofs;
       	ofs.open("output/raw_output.dat", std::ofstream::out);
	ofs << "x area density velocity temperature pressure mach mass_flow" << std::endl;	
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

	std::vector<double> error_comp		=	vars.error_comp;
	print_error(error_comp);

}

void Raw_Output::print_error(std::vector<double> error_comp) {

	const int max_time_step	=	error_comp.size();
	std::ofstream error_outfile;
	error_outfile.open("output/error_output.dat");
	error_outfile << "time_step error" << std::endl;
	for (auto i = 0; i < max_time_step; i++) {
		error_outfile << i+1 << " " << error_comp[i] << std::endl;
	}
	error_outfile.close();

}
