
clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;
plot_settings(1);
cm = "internet";
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
            c_num(i,j) = (c_num(i +1, j) - c_num(i, j))/dx + ;
        else 
            c_num(i,j) = (c_num(i , j) + c_num(i - 1, j))/ 2;
        end
    end
end


%extrapolate corners
c_num(1,1) = (c_num(2,1) + c_num(3,1)) / 2;






f = figure(1);
theme(f,"light");
ax = gca;
surf(ax, X, Y, c_num)
xlabel("x")
ylabel("y")
colorbar
%shading flat
