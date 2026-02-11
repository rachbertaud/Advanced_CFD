#!/bin/bash

for N in 64 128 256 512; do
	sed -i '' "2s/^[0-9]*/$N/" inputs_error  # Nx on line 2
	sed -i '' "4s/^[0-9]*/$N/" inputs_error  # Ny on line 4
    
 	./No_k/run_No_K 1
	mv No_k/x_No_K.dat No_k/x_No_K_N${N}.dat
	mv No_k/y_No_K.dat No_k/y_No_K_N${N}.dat
	mv No_k/c_No_K.dat No_k/c_No_K_N${N}.dat

        ./With_K_m/run_K_m 1
        mv With_K_m/x_with_km.dat With_K_m/x_with_km_N${N}.dat
        mv With_K_m/y_with_km.dat With_K_m/y_with_km_N${N}.dat
        mv With_K_m/c_with_km.dat With_K_m/c_with_km_N${N}.dat




done
