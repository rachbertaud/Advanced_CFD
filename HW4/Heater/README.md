# Main

The full advection-diffusion solver with physically realistic air properties (rho=1.225 kg/m³, cp=1005 J/kg·K, k=0.026 W/m·K). Solves steady-state temperature transport on a 2D domain with a sinusoidal velocity field parameterized by amplitude `A` and length scales `bx`/`by`.

## Build & Run

```bash
make build    # compiles with Eigen
make run      # runs ./main
make clean    # removes binary and output .dat files
```

## Inputs

- **`Case.inp`** — fluid properties, boundary temps (Ts/Tn), and velocity field parameters (`A`, `bx`, `by`)
- **`Mesh.inp`** — grid resolution (Nx, Ny) and domain size (Lx, Ly)

## Velocity Field

```
u = -A/(by·Ly) · sin(2πx/bx·Lx) · cos(2πy/by·Ly)
v =  A/(bx·Lx) · cos(2πx/bx·Lx) · sin(2πy/by·Ly)
```

Setting `A=0` gives pure diffusion.

## Parameter Sweeps

Two bash scripts automate running cases and renaming outputs:

```bash
bash A_Sweep.sh    # fixes bx=by=2, sweeps A over: 0, 1e-5, 1e-4, 1e-3, 1e-2
bash B_Sweep.sh    # fixes A=0.015, sweeps bx=by over: 1.0, 0.5, 0.25
```

Outputs are saved as `c_bx<B>_by<B>_A<A>.dat` etc.

## Outputs

`xc.dat`, `yc.dat`, `c.dat` — cell-center coordinates and temperature field.

## Visualization

```matlab
viz.m     % plots the numerical solution (pcolor)
A_viz.m   % plots results from A_Sweep
B_viz.m   % plots results from B_Sweep
Aplot.m   % summary plot for A sweep
```
