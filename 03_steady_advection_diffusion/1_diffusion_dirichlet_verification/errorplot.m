addpath /Users/rachelbertaud/code/MATLAB_Settings/;

plot_settings(1);

%%

Err_inf = [];

for N = [64 128 256 512]
    x = readmatrix(sprintf('xc_N%d.dat', N));
    y = readmatrix(sprintf('yc_N%d.dat', N));
    c = readmatrix(sprintf('c_N%d.dat', N));

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



    c_num_NB = c_num(2:Ny - 1, 2:Nx - 1);
    c_an_NB = c_an(2:Ny - 1, 2:Nx - 1);
    X_NB = X(2:Ny - 1, 2:Nx - 1);
    Y_NB = Y(2:Ny - 1, 2:Nx - 1);

    err = max(max(abs(c_num_NB - c_an_NB)))/max(max(abs(c_an_NB)));
    Err_inf = [Err_inf err];

end

N = [64 128 256 512];


f = figure(1);
theme(f,"light");
hold on
plot(N, (Err_inf), 'Color',[227/255,159/255,246/255])
plot(N, 1./N, '.-.', 'Color',[240/255,159/255,200/255])
plot(N, 1./(N.^2), '--', 'Color',[220/255,200/255,246/255])
set(gca,'YScale','log','XScale','log')
legend('Results from HW3 Solution', '$\cal{O}$$(h)$ Reference Line', '$\cal{O}$$(h^2)$ Reference Line', 'Location','northeast')
ylabel("Relative Error of Solution, $E_{\infty}$")
xlabel("Number of Grid Points, $N$")
hold off

saveas(f, "HW3_Error_Plot_Just_Diff.png", 'png')