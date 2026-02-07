clc
clear
%%

A = readmatrix("matrix_A_dense.txt");
% 
% spy(A)



%%
x = readmatrix("x.dat");
y = readmatrix("y.dat");
c = readmatrix("c.dat");
b = readmatrix("b.dat");


[X,Y] = meshgrid(x,y);

Nx = length(x);
Ny = length(y);

b_mat = zeros(Ny, Nx);
b_check = reshape(b, Nx, Ny)';


for i = 0:1:(Ny - 1)
    b_mat((Ny - i), :) = b_check((i+1),:);
end

b_fcn = @(x,y) -2*cos(x)*cos(y);

b_an = zeros((Nx*Ny), 1);

% for i = 1:1:(Nx*Ny)
%     b_an(i) = cos(x(i))*cos(y(i)) 


c_num = reshape(c, Ny, Nx);
c_mat = zeros(Ny,Nx);
b_num = reshape(b, Ny, Nx);

for i = 0:1:(Ny - 1)
    c_mat((Ny - i), :) = c_num((i+1),:);
end

c_an = zeros(Ny, Nx);

for i = 2:1:Nx-1
    for j = 2:1:Ny-1
        row = (Nx)*(j - 1) + i;
        b_an(row) = 2*cos(x(i))*cos(y(j));
        c_an(j,i) = cos(x(i))*cos(y(j));
    end
end 

b_bruh = reshape(b_an, Ny, Nx);
b_huh = zeros(Ny, Nx);

for i = 0:1:(Ny - 1)
    b_huh((Ny - i), :) = b_bruh((i+1),:);
end

%%

ccc = A\b_an;

cc = reshape(ccc, Ny, Nx);

figure(1)
pcolor(c_num(2:(Ny - 1), 2:(Nx - 1)))
title("Numerical")
colorbar()

figure(2)
pcolor(c_an(2:(Ny - 1), 2:(Nx - 1)))
title("analytical")
colorbar()




%% Uncomment this to spy A, make sure you change Nx and Ny
% rows = readmatrix("row.dat");
% rows = rows + 1;
% 
% col = readmatrix("col.dat");
% col = col + 1;
% 
% val = ones(length(rows), 1);
% 
% A = sparse(rows, col, val, 16, 16);
% 
% spy(A)