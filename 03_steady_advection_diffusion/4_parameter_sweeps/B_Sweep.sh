#!/bin/bash

# In-place sed that works with both GNU (Linux) and BSD (macOS) sed
sedi() { sed -i.bak "$@" && rm -f "${!#}.bak"; }

# Case 2: A = 0.015, vary bx = by
A=0.015
sedi "12s/.*/${A};/" Case.inp

for B in 1.0 0.5 0.25; do
    sedi "14s/.*/$(echo $B);/" Case.inp
    sedi "16s/.*/$(echo $B);/" Case.inp

    ./main
    mv xc.dat xc_bx${B}_by${B}_A${A}.dat
    mv yc.dat yc_bx${B}_by${B}_A${A}.dat
    mv c.dat   c_bx${B}_by${B}_A${A}.dat
done
