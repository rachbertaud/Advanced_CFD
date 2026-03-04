# Diff_Check

Verifies the diffusion-only solver against the analytical solution T(x,y) = cos(x)cos(y) with Dirichlet boundary conditions. No advection — just a sanity check that the diffusion stencil and linear solve are working correctly before adding more complexity.

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

This automatically edits `Mesh.inp`, runs the solver at each resolution, and saves output files as `c_N<N>.dat`, `xc_N<N>.dat`, `yc_N<N>.dat`.

## Inputs

- **`Case.inp`** — fluid properties (rho, cp, k), boundary temps (Ts/Tn), and source parameters
- **`Mesh.inp`** — grid resolution (Nx, Ny) and domain size (Lx, Ly)

## Outputs

`xc.dat`, `yc.dat`, `c.dat` — cell-center coordinates and temperature field.

## Visualization

```matlab
viz.m        % plots numerical, analytical, and local error side-by-side
errorplot.m  % convergence plot (error vs. mesh size)
```
