# ACFD HW3 — 2D Advection-Diffusion Solver

Steady-state temperature transport on a 2D domain using a finite volume method with a sinusoidal velocity field. Built incrementally — each folder adds or verifies one piece of the solver.

## Folders

| Folder | Purpose |
|---|---|
| `Diff_Check` | Diffusion-only solver with Dirichlet BCs, verified against analytical solution cos(x)cos(y) |
| `Neumann_Implementation` | Same diffusion-only setup but with Neumann BCs on E/W Boundaries |
| `Verf_of_Main` | Full advection-diffusion solver, verified with artificial fluid properties |
| `Main` | Production solver with real air properties; includes parameter sweeps over flow amplitude and length scales |

See each folder's `README.md` for build instructions and usage details.

## Dependencies

- [Eigen](https://eigen.tuxfamily.org) — sparse linear solver (path hardcoded in Makefiles)
- MATLAB — for visualization scripts (`viz.m`, `errorplot.m`, etc.)
