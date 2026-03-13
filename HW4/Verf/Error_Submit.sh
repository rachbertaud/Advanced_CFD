#!/bin/bash

for N in 64 128 256 512; do
	sed -i '' "2s/^[0-9]*/$N/" Mesh.inp  # Nx on line 2
	sed -i '' "4s/^[0-9]*/$N/" Mesh.inp  # Ny on line 4
    
 	./main
	mv xc.dat xc_N${N}.dat
	mv yc.dat yc_N${N}.dat
	mv c.dat c_N${N}.dat

done
