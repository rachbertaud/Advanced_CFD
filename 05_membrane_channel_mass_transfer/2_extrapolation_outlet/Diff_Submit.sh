#!/bin/bash

# In-place sed that works with both GNU (Linux) and BSD (macOS) sed
sedi() { sed -i.bak "$@" && rm -f "${!#}.bak"; }

for D in 1e-9 1e-10 1e-11 1e-12; do
    sedi "6s|.*|$D|" C.inp

    ./main
    mv xc.dat xc_D${D}.dat
    mv yc.dat yc_D${D}.dat
    mv c.dat c_D${D}.dat
done
