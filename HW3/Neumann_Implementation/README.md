# Neumann_Implementation

Same diffusion-only verification setup as `Diff_Check`, but with Neumann boundary conditions instead of Dirichlet. The analytical solution is still T(x,y) = cos(x)cos(y). This folder exists to check that the Neumann BC implementation is correct and converges at the expected rate.

## Build & Run

```bash
make build    # compiles with Eigen
make run      # runs ./main
make clean    # removes binary and output .dat files
```

## Convergence Study

Run the error sweep over mesh sizes N = 64, 128, 256, 512:

```bash
bash Error_Submit.sh
```

Saves output as `c_N<N>.dat`, `xc_N<N>.dat`, `yc_N<N>.dat` for each resolution.

## Inputs

- **`Case.inp`** — fluid properties (rho, cp, k), boundary temps, source term flag
- **`Mesh.inp`** — grid resolution and domain size

## Outputs

`xc.dat`, `yc.dat`, `c.dat` — cell-center coordinates and temperature field.

## Visualization

```matlab
viz.m        % plots numerical, analytical, and local error
errorplot.m  % convergence plot (error vs. mesh size)
```
