clear

addpath /Users/rachelbertaud/code/MATLAB_Settings/;
plot_settings(1);

%%
x = readmatrix("x_No_K.dat");
y = readmatrix("y_No_K.dat");
c = readmatrix("c_No_K.dat");

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
title("Numerical Solution")
xlabel("x")
ylabel("y")
colorbar()
saveas(f, "HW2_Numerical_No_K.png", 'png')

f = figure(2);
theme(f,"light");
surf(X_NB,Y_NB,c_an_NB)
xlabel("x")
ylabel("y")
title("Analytical Solution")
colorbar()
saveas(f, "HW2_Analytical_No_K.png", 'png')

f = figure(3);
theme(f,"light");
surf(X_NB,Y_NB,abs(c_an_NB - c_num_NB))
xlabel("x")
ylabel("y")
title("Local Error")
colorbar()
saveas(f, "HW2_Local_Err_No_K.png", 'png')


