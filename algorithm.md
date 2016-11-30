#Algorithm for Euler Solver on Convergent-Divergent Duct

1. Start the program.
2. Input the constant parameters, compute another parameters which can be computed by these parameters (like speed of sound).
3. Compute A(x) with an arbitrary function. 
4. Initialize the computational point and the initial condition for every variable (velocity, temperature, dst).
5. Compute delta-t for each grid point, take the smallest delta-t for computation.
6. Computation Start - Looping Process
	* Compute drho/dt, dv/dt, dT/dt for the predictor phase. Introduce BC in the processes.
	* Calculate new variable which will be used by corrector phase (variable with bar).
	* Compute drho/dt, dv/dt, dT/dt for the corrector phase. Introduce BC in the processes.
	* Compute the average value of drho/dt, dv/dt, dT/dt.
	* Compute new variable for next time step.
	* Go back to first step on the loop.
7. Computation stops after value before minus value after is rather negligible (minimum errors).
8. Write to file, program is finished.
