#!/bin/bash
# Temporal convergence study: time-periodic manufactured solution
# (omega = 6.28) on a fixed 64^2 mesh, dt refined from 0.1 to 0.0005.
# Writes t_convergence.csv.

# In-place sed that works with both GNU (Linux) and BSD (macOS) sed
sedi() { sed -i.bak "$@" && rm -f "${!#}.bak"; }

echo 'dt, error' > t_convergence.csv

sedi "8s/.*/6.28/" T.inp             # omega

sedi "2s/^[0-9]*/64/" Mesh.inp       # Nx on line 2
sedi "4s/^[0-9]*/64/" Mesh.inp       # Ny on line 4

for dt in 0.1 0.05 0.01 0.005 0.001 0.0005; do
  sedi "6s/.*/$dt/" ControlDict.inp

  output=$(./main_TE)
  echo "$output"

  error=$(echo "$output" | grep "ERROR=" | cut -d'=' -f2)
  echo "$dt,$error" >> t_convergence.csv
done
