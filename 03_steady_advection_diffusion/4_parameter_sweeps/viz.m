
clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;

plot_settings(1);
cm = "turbo";
%%

x = readmatrix("xc.dat");
y = readmatrix("yc.dat");
c = readmatrix("c.dat");

ax_lim = [min(x), max(x)];
ay_lim = [min(y), max(y)];

A = 0.001;
bx = 2;
by = 2;
Lx = 1;
Ly = 1;

[X,Y] = meshgrid(x,y);

Nx = length(x);
Ny = length(y);

c_num = reshape(c, Ny, Nx);



%%
c_num_NB = c_num(2:Ny - 1, 2:Nx - 1)';
X_NB = X(2:Ny - 1, 2:Nx - 1);
Y_NB = Y(2:Ny - 1, 2:Nx - 1);

Psi = -(A / (2*pi)) .* sin(2*pi*X_NB / (bx*Lx)) .* sin(2*pi*Y_NB / (by*Ly));

f = figure(1);
theme(f,"light");
ax = gca;
pcolor(ax, X_NB, Y_NB, c_num_NB)
shading flat
hold on
%contour(X_NB, Y_NB, Psi, 20, 'k')
title("Numerical Solution")
xlabel("x")
ylabel("y")
xlim(ax, ax_lim)
ylim(ax, ay_lim)
clim([min(c_num_NB(:)) max(c_num_NB(:))])
colorbar
colormap(cm)
hold off
saveas(f, "HW3_Numerical.png", 'png')

