
clear
% addpath /Users/rachelbertaud/code/cmap-master;
% addpath /Users/rachelbertaud/code/MATLAB_Settings/;
% plot_settings(1);
% cm = "internet";
%%
x = readmatrix("xc.dat");
y = readmatrix("yc.dat");
c_num = readmatrix("c.dat");

[X,Y] = meshgrid(x,y);
dx = abs(X(1,1) - X(1,2));
Nx = length(x);
Ny = length(y);
c_num = reshape(c_num, Nx, Ny)';
%%
%interpolate boundary cases
for i = [1, Nx]
    for j = 1:1:Ny
        if(i == 1)
            c_num(i,j) = (c_num(i +1, j) + c_num(i, j))/2;
        else 
            c_num(i,j) = (c_num(i , j) + c_num(i - 1, j))/ 2;
        end
    end
end


%extrapolate corners
y_e = @(x, x1, y1, x2, y2) (y1 + ((x - x1)*((y2 - y1)/(x2 - x1))));

c_num(1,1) = y_e(0, X(1,2), c_num(1,2), X(1,3), c_num(1,3));
x(1) = 0;
X(1,1) = 0;
c_num(1,Nx) = y_e(x(Nx), x(Nx-1), c_num(1,Nx-1), x(Nx - 2), c_num(1,Nx - 2));

c_num(Ny,1) = y_e(0, X(Ny,3), c_num(Ny,3), X(Ny,2), c_num(Ny,2));
X(Ny, 1) = 0;
c_num(Ny,Nx) = y_e(x(Nx), x(Nx-1), c_num(Ny,Nx-1), x(Nx - 2), c_num(Ny,Nx - 2));





f = figure(1);
theme(f,"light");
surf(X, Y, c_num)
% colormap(cm)
xlabel("$$x$$")
ylabel("$$y$$")
xlabel("$$C(x,y)$$")
colorbar
shading flat
name = "HW5_NeumannBC_Nx" + num2str(Nx) + "_Ny_" + num2str(Ny) + ".png";
saveas(f, name, 'png')

f = figure(2);
theme(f, "light")
plot(x, c_num(1,:), color=[227/255,159/255,246/255])
hold on 
ylabel("$$C(x,0)$$")
xlabel("$$x$$")
% plot(x, c_num(1,:), 'm')
name = "HW5_NeumannBC_Nx" + num2str(Nx) + "_Ny_" + num2str(Ny) + "_Edge.png";
saveas(f, name, 'png')
