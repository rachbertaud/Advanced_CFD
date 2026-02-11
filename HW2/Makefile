## Inputs are 0 for full input file, 1 for error input file, and 2 for base input file

FuelRod:
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o Fuel_Rod/run_FuelRod Fuel_Rod/HW2_Fuel_Rod.cpp funcs_HW2.cpp
	./Fuel_Rod/run_FuelRod 0

NoK:
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o No_k/run_No_K No_k/HW2_No_K.cpp funcs_HW2.cpp
	./No_k/run_No_K 2

WithKm:
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o With_K_m/run_K_m With_K_m/HW2_With_K_m.cpp funcs_HW2.cpp
	./With_K_m/run_K_m 2

runAll:
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o Fuel_Rod/run_FuelRod Fuel_Rod/HW2_Fuel_Rod.cpp funcs_HW2.cpp
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o No_k/run_No_K No_k/HW2_No_K.cpp funcs_HW2.cpp
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o With_K_m/run_K_m With_K_m/HW2_With_K_m.cpp funcs_HW2.cpp
	
	./Fuel_Rod/run_FuelRod 0
	./No_k/run_No_K 2
	./With_K_m/run_K_m 2

ErrorPlots:
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o With_K_m/run_K_m With_K_m/HW2_With_K_m.cpp funcs_HW2.cpp
	g++ -I/Users/rachelbertaud/code/eigen-5.0.0 -o No_k/run_No_K No_k/HW2_No_K.cpp funcs_HW2.cpp

	./Error_Submit.sh
clean: 
	rm -f With_K_m/run_K_m
	rm -f No_k/run_No_K
	rm -f FuelRod/run_FuelRod

clean_data:
	rm -f With_K_m/x*
	rm -f With_K_m/y*
	rm -f With_K_m/c*

	rm -f No_k/x*
	rm -f No_k/y*
	rm -f No_k/c*

	rm -f Fuel_Rod/x*
	rm -f Fuel_Rod/y*
	rm -f Fuel_Rod/c*

