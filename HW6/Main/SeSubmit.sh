#!/bin/bash
echo 'N, error' > convergence.csv


sed -i '' "8s/.*/0;/" T.inp
#sed -i '' "8s/omega/0/" T.inp	    

#sed -i '' "6s/.*/dt/" ControlDict.inp
sed -i '' "6s/.*/0.5;/" ControlDict.inp	 

for N in 64 128 256 512; do
	sed -i '' "2s/^[0-9]*/$N/" Mesh.inp  # Nx on line 2
	sed -i '' "4s/^[0-9]*/$N/" Mesh.inp  # Ny on line 4
    
 	output=$(./main_SE)
 	echo "$output"

 	error=$(echo "$output" | grep "ERROR=" | cut -d'=' -f2)
  echo "$N,$error" >> convergence.csv
 	
	# mv xc.dat xc_N${N}.dat
	# mv yc.dat yc_N${N}.dat
	# mv c.dat c_N${N}.dat

done
