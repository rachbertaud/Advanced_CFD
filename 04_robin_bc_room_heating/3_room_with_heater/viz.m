
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
A = 0.01;
bx = 2;
by = 2;
Lx = 5;
Ly = 5;
[X,Y] = meshgrid(x,y);
Nx = length(x);
Ny = length(y);
c_num = reshape(c, Ny, Nx);
%%
c_num_NB = c_num(2:Ny - 1, 2:Nx - 1)';
X_NB = X(2:Ny - 1, 2:Nx - 1);
Y_NB = Y(2:Ny - 1, 2:Nx - 1);
Psi = -(A / (2*pi)) .* sin(2*pi*X_NB / (bx*Lx)) .* sin(2*pi*Y_NB / (by*Ly));
avg = sum(sum(c_num_NB))/(Nx*Ny);

% BC coordinates (from BC.inp)
w1 = 3; w2 = 4;      % west window y-range
n1 = 3.5; n2 = 4.5;  % north window x-range
s1 = 1;  s2 = 1.8;   % south door x-range
x_west  = min(X_NB(:));
y_south = min(Y_NB(:));
y_north = max(Y_NB(:));

f = figure(1);
theme(f,"light");
ax = gca;
pcolor(ax, X_NB, Y_NB, c_num_NB)
shading flat
hold on
%contour(X_NB, Y_NB, Psi, 20, 'k')
plot([x_west  x_west],  [w1 w2],           '-', 'Color', [1.00 0.08 0.58], 'LineWidth', 3)  % west window  — Barbie pink
plot([n1 n2],           [y_north y_north],  '-', 'Color', [1.00 0.08 0.58], 'LineWidth', 3)  % north window — Barbie pink
plot([s1 s2],           [y_south y_south],  '-', 'Color', [0.60 0.00 1.00], 'LineWidth', 3)  % south door   — electric violet
title("Numerical Solution")
xlabel("x")
ylabel("y")
xlim(ax, ax_lim)
ylim(ax, ay_lim)
clim([min(c_num_NB(:)) max(c_num_NB(:))])
txt = ['Average Temperature (K) = ' int2str(avg)];
subtitle(txt)
colorbar
colormap(cm)
hold off
% saveas(f, "HW3_C_Numerical.png", 'png')
