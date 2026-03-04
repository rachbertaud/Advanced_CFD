#!/bin/bash

# Case 1: bx = by = 2, vary A
BX=2.0
BY=2.0

# Set bx and by
sed -i '' "14s/.*/2.0;/" Case.inp
sed -i '' "16s/.*/2.0;/" Case.inp

for A in 0 1e-5 1e-4 1e-3 1e-2; do
    sed -i '' "12s/.*/${A};/" Case.inp

    ./main
    mv xc.dat xc_bx${BX}_by${BY}_A${A}.dat
    mv yc.dat yc_bx${BX}_by${BY}_A${A}.dat
    mv c.dat   c_bx${BX}_by${BY}_A${A}.dat
done
