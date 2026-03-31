
clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;
plot_settings(1);
cm = "turbo";
%%
% x = readmatrix("xc_N256.dat");
% y = readmatrix("yc_N256.dat");
% c = readmatrix("c_N256.dat");

x = readmatrix("xc.dat");
y = readmatrix("yc.dat");
c = readmatrix("c.dat");

[X,Y] = meshgrid(x,y);
Nx = length(x);
Ny = length(y);
c_num = reshape(c, Ny, Nx);
%%
c_num_NB = c_num(2:Ny - 1, 2:Nx - 1)';
X_NB = X(2:Ny - 1, 2:Nx - 1);
Y_NB = Y(2:Ny - 1, 2:Nx - 1);

an = sin(X_NB).*sin(Y_NB);

f = figure(1);
theme(f,"light");
ax = gca;
surf(ax, X_NB, Y_NB, an)

f = figure(2);
theme(f,"light");
ax = gca;
surf(ax, X_NB, Y_NB, abs(c_num_NB - an))
%shading flat
