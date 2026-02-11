clear
addpath /Users/rachelbertaud/code/MATLAB_Settings/;
plot_settings(1);


%% With K
x = readmatrix("x_with_km.dat");
y = readmatrix("y_with_km.dat");
c = readmatrix("c_with_km.dat");

%% Without K

% x = readmatrix("x_No_K.dat");
% y = readmatrix("y_No_K.dat");
% c = readmatrix("c_No_K.dat");

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


figure(1)
surf(X_NB,Y_NB,c_num_NB)
title("Numerical")
xlabel("x")
ylabel("y")
colorbar()

figure(2)
surf(X_NB,Y_NB,c_an_NB)
xlabel("x")
ylabel("y")
title("analytical")
colorbar()


%%

err = max(max(abs(c_num_NB - c_an_NB)))/max(max(abs(c_an_NB)))
