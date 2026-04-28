import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Spatial convergence
df = pd.read_csv("convergence.csv", skipinitialspace=True)

fig1, ax1 = plt.subplots()
ax1.loglog(df["N"], df["error"], 'o-', color='hotpink', label="error")

N = df["N"].values
ax1.loglog(N, 1/N, '--', color='plum', label="O(h)")
ax1.loglog(N, 1/N**2, '--', color='orchid', label="O(h²)")

ax1.set_xlabel("N")
ax1.set_ylabel("Error")
ax1.set_title("Spatial Convergence")
ax1.legend()
plt.tight_layout()
fig1.savefig("spatial_convergence.png", dpi=150)

# Temporal convergence
df2 = pd.read_csv("t_convergence.csv", skipinitialspace=True)

fig2, ax2 = plt.subplots()
ax2.loglog(df2["dt"], df2["error"], 'o-', color='hotpink', label="error")

dt = df2["dt"].values
ax2.loglog(dt, dt/dt[0] * df2["error"].values[0], '--', color='plum', label="O(dt)")
ax2.loglog(dt, (dt/dt[0])**2 * df2["error"].values[0], '--', color='orchid', label="O(dt²)")
ax2.set_xlabel("dt")

ax2.set_ylabel("Error")
ax2.set_title("Temporal Convergence")
ax2.legend()

emin = df2["error"].min()
emax = df2["error"].max()
ax2.set_ylim(emin * 0.5, emax * 2)

plt.tight_layout()
fig2.savefig("temporal_convergence.png", dpi=150)

plt.show()
