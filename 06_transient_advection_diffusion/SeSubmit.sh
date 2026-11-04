#!/bin/bash
# Spatial convergence study: steady manufactured solution (omega = 0),
# mesh refined from 64^2 to 512^2. Writes convergence.csv.

# In-place sed that works with both GNU (Linux) and BSD (macOS) sed
sedi() { sed -i.bak "$@" && rm -f "${!#}.bak"; }

echo 'N, error' > convergence.csv

sedi "8s/.*/0;/" T.inp               # omega = 0
sedi "6s/.*/0.5;/" ControlDict.inp   # dt

for N in 64 128 256 512; do
  sedi "2s/^[0-9]*/$N/" Mesh.inp     # Nx on line 2
  sedi "4s/^[0-9]*/$N/" Mesh.inp     # Ny on line 4

  output=$(./main_SE)
  echo "$output"

  error=$(echo "$output" | grep "ERROR=" | cut -d'=' -f2)
  echo "$N,$error" >> convergence.csv
done
