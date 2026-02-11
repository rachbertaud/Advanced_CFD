clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;

plot_settings(1);
cm = "thermal";


%%
x = readmatrix("x_Fuel_Rod.dat");
y = readmatrix("y_Fuel_Rod.dat");
c = readmatrix("c_Fuel_Rod.dat");



[X,Y] = meshgrid(x,y);

Nx = length(x);
Ny = length(y);
Lx = 0.015;


%%


c_num = reshape(c, Ny, Nx)';

c_num_NB = c_num(2:Ny - 1, 2:Nx - 1);
X_NB = X(2:Ny - 1, 2:Nx - 1);
Y_NB = Y(2:Ny - 1, 2:Nx - 1);

%%

f1 = figure(1);
theme(f1,"light");
hold on
surf(X_NB,Y_NB,c_num_NB)
colormap(cm)
xlabel("$$x$$")
ylabel("$$y$$")
zlabel("$$T(x,y)$$");
view(3)
colorbar()
hold off
saveas(f1, "Fuel_Rod_3D.png", 'png')
%%
f2 = figure(2);
theme(f2,"light");
hold on
pcolor(X_NB,Y_NB,c_num_NB)
shading interp
colormap(cm)
viscircles([0.015/2, 0.015/2], 0.004 ,'Color',[1/255,255/255,1/255])
viscircles([0.015/2, 0.015/2], 0.005,'Color',[1/255,255/255,1/255])
xlabel("$$x$$")
ylabel("$$y$$")
colorbar()
hold off
saveas(f2, "Fuel_Rod_Birds_Eye.png", 'png')
%%

f3 = figure(3);
theme(f3,"light");
hold on
plot(Y_NB, c_num_NB(round(Ny/2),:),'Color',[245/255,100/255,245/255])
xr1 = xregion(((Lx/2)-0.004), ((Lx/2) + .004), FaceColor=[227/255,159/255,246/255],EdgeColor=[220/255,200/255,246/255]);
xr1.FaceAlpha = 0.25;
xr1.EdgeAlpha = 1;
xr1.LineWidth = 2;

xr = xregion(((Lx/2)-0.005), ((Lx/2) + .005), FaceColor=[227/255,159/255,246/255],EdgeColor=[220/255,200/255,246/255]);
xr.FaceAlpha = 0.25;
xr.EdgeAlpha = 1;
xr.LineWidth = 2;
xlabel("y")
ylabel("T")
saveas(f3, "TvsY.png", 'png')



