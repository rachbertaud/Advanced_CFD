#!/bin/bash

# In-place sed that works with both GNU (Linux) and BSD (macOS) sed
sedi() { sed -i.bak "$@" && rm -f "${!#}.bak"; }

for N in 64 128 256 512; do
	sedi "2s/^[0-9]*/$N/" inputs_error  # Nx on line 2
	sedi "4s/^[0-9]*/$N/" inputs_error  # Ny on line 4

 	./No_k/run_No_K 1
	mv No_k/x_No_K.dat No_k/x_No_K_N${N}.dat
	mv No_k/y_No_K.dat No_k/y_No_K_N${N}.dat
	mv No_k/c_No_K.dat No_k/c_No_K_N${N}.dat

        ./With_K_m/run_K_m 1
        mv With_K_m/x_with_km.dat With_K_m/x_with_km_N${N}.dat
        mv With_K_m/y_with_km.dat With_K_m/y_with_km_N${N}.dat
        mv With_K_m/c_with_km.dat With_K_m/c_with_km_N${N}.dat

done
