clear



%%
x = readmatrix("x.dat");
y = readmatrix("y.dat");
c = readmatrix("c.dat");



[X,Y] = meshgrid(x,y);

Nx = length(x);
Ny = length(y);


%%


c_num = reshape(c, Ny, Nx)';

c_num_NB = c_num(2:Ny - 1, 2:Nx - 1);
X_NB = X(2:Ny - 1, 2:Nx - 1);
Y_NB = Y(2:Ny - 1, 2:Nx - 1);

%%

figure(1)
hold on
surf(X_NB,Y_NB,c_num_NB)
shading interp
colormap("turbo")
title("Numerical")
xlabel("x")
ylabel("y")

figure(2)
hold on
pcolor(X_NB,Y_NB,c_num_NB)
shading interp
colormap("turbo")
viscircles([0.015/2, 0.015/2], 0.004)
viscircles([0.015/2, 0.015/2], 0.005)
title("Numerical")
xlabel("x")
ylabel("y")

colorbar()


figure(3)
plot(X_NB, c_num_NB)



