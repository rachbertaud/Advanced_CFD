# Verf_of_Main

Verification of the full advection-diffusion solver (same code structure as `Main`). Uses artificial fluid properties (rho=1.1, cp=1.2, k=1.3) chosen to make the math clean, and checks the combined advection+diffusion solve against an analytical solution. Run this before trusting `Main` with real physical parameters.

## Build & Run

```bash
make build    # compiles with Eigen
make run      # runs ./main
make clean    # removes binary and output .dat files
```

## Convergence Study

```bash
bash Error_Submit.sh
```

Sweeps over N = 64, 128, 256, 512 and saves `c_N<N>.dat`, `xc_N<N>.dat`, `yc_N<N>.dat`.

## Inputs

- **`Case.inp`** — rho, cp, k, boundary temps (Ts/Tn), flow amplitude `A`, and length scales `bx`/`by` for the velocity field
- **`Mesh.inp`** — grid resolution (Nx, Ny) and domain size (Lx, Ly)

## Velocity Field

The advection velocities are sinusoidal and controlled by `A`, `bx`, `by` in `Case.inp`:

```
u = -A/(by·Ly) · sin(2πx/bx·Lx) · cos(2πy/by·Ly)
v =  A/(bx·Lx) · cos(2πx/bx·Lx) · sin(2πy/by·Ly)
```

Setting A=0 reduces to pure diffusion.

## Outputs

`xc.dat`, `yc.dat`, `c.dat` — cell-center coordinates and temperature field.

## Visualization

```matlab
viz.m        % plots the numerical solution
errorplot.m  % convergence plot (error vs. mesh size)
```
