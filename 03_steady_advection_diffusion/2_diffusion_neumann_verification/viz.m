
clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;

plot_settings(1);
cm = "internet";
%%

x = readmatrix("xc.dat");
y = readmatrix("yc.dat");
c = readmatrix("c.dat");

ax_lim = [min(x), max(x)];
ay_lim = [min(y), max(y)];

[X,Y] = meshgrid(x,y);

Nx = length(x);
Ny = length(y);

c_num = reshape(c, Ny, Nx);

c_an = zeros(Ny, Nx);

for i = 2:1:Nx-1
    for j = 2:1:Ny-1
        row = (Nx)*(j - 1) + i;
        c_an(j,i) = cos(x(i))*cos(y(j));
    end
end 


%%
c_num_NB = c_num(2:Ny - 1, 2:Nx - 1);
c_an_NB = c_an(2:Ny - 1, 2:Nx - 1);
X_NB = X(2:Ny - 1, 2:Nx - 1);
Y_NB = Y(2:Ny - 1, 2:Nx - 1);


f = figure(1);
theme(f,"light");
surf(X_NB,Y_NB,c_num_NB)
shading interp
title("Numerical Solution")
xlabel("x")
ylabel("y")
xlim(ax_lim)
ylim(ay_lim)
colorbar()
colormap(cm)
saveas(f, "HW3_Numerical_Neumann.png", 'png')

f = figure(2);
theme(f,"light");
surf(X_NB,Y_NB,c_an_NB)
shading interp
xlabel("x")
ylabel("y")
title("Analytical Solution")
xlim(ax_lim)
ylim(ay_lim)
colormap(cm)
colorbar()
saveas(f, "HW3_Analytical_Neumann.png", 'png')

f = figure(3);
theme(f,"light");
surf(X_NB,Y_NB,abs(c_an_NB - c_num_NB))
shading interp
xlabel("x")
ylabel("y")
title("Local Error")
xlim(ax_lim)
ylim(ay_lim)
colormap(cm)
colorbar()
saveas(f, "HW3_Local_Err_Neumann.png", 'png')
