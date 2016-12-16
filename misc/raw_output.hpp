#ifndef RAW_OUTPUT_H 
#define RAW_OUTPUT_H

#include "../global.hpp"

class Raw_Output {

	void print_error(std::vector<double> error_comp);
	public:
		void print_raw_output(Variables vars, Parameters parameters);

};


#endif
