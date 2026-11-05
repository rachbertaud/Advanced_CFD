# 2D Transient Advection-Diffusion

Adds time stepping to the finite volume solver from the previous project:

    ρ c_p (∂T/∂t + u·∇T) = ∇·(k ∇T) + f

Advection and diffusion use centered differences for second-order spatial accuracy. Time integration is fully implicit (backward Euler). The matrix stays the same from step to step, so it is assembled and LU-factorized once. Each step only rebuilds the right-hand side and does a forward/back substitution.

Verification uses the manufactured solution

    T(x, y, t) = cos(x) cos(y) cos(ωt)

on [0, 2π]² in a cellular flow u = -sin(x) cos(y), v = cos(x) sin(y) with time-dependent Dirichlet boundary conditions on all walls, and ρ = 1.1, c_p = 1.2, k = 1.3.

- **Spatial convergence** (`main_SE`, `SeSubmit.sh`): ω = 0 and T = 0 at t = 0, meshes 64² to 512², marched in time until the solution stops changing (largest change between steps below 1e-10). The error converges at second order.
- **Temporal convergence** (`main_TE`, `TeSubmit.sh`): ω = 2π and T = cos(x) cos(y) at t = 0, Δt from 0.1 to 0.0005, error measured at t = 1. The error converges at first order, as expected for backward Euler, until it reaches a floor set by the spatial error.

## Code layout

| File | Contents |
|---|---|
| `funcs_Time.cpp` | Time step, end time and output interval from `ControlDict.inp` |
| `funcs_Mesh.cpp` | Mesh from `Mesh.inp` |
| `funcs_VolSF.cpp` | Cell-centered field: initial condition, source term, output |
| `funcs_ScaSF.cpp` | Face fluxes |
| `funcs_velF.cpp` | Velocity field |
| `funcs_bcType.cpp` | Boundary conditions |
| `funcs_matrix.cpp` | Matrix and right-hand side assembly, factorization and solve |
| `funcs_SpatError.cpp` | Error against the exact solution |

## Running

```bash
make build
make run       # runs both convergence studies, then plot.py
make clean     # removes the executables and output files
```

`plot.py` reads `convergence.csv` and `t_convergence.csv` and plots both against first- and second-order reference slopes. `TeSubmit.sh` runs the temporal study on a 64² mesh; change the two `Mesh.inp` lines in it to 32 to reproduce the 32² case.
