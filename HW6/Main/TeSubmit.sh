#!/bin/bash
echo 'dt, error' > t_convergence.csv

#sed -i '' "8s/.*/dt/" T.inp
sed -i '' "8s/.*/6.28/" T.inp	    


sed -i '' "2s/^[0-9]*/64/" Mesh.inp  # Nx on line 2
sed -i '' "4s/^[0-9]*/64/" Mesh.inp  # Nx on line 2


for dt in 0.1 0.05 0.01 0.005 0.001 0.0005; do
  sed -i '' "6s/.*/dt/" ControlDict.inp
  sed -i '' "6s/dt/$dt/" ControlDict.inp	    

 	output=$(./main_TE)
 	echo "$output"

 	error=$(echo "$output" | grep "ERROR=" | cut -d'=' -f2)
  echo "$dt,$error" >> t_convergence.csv

done
