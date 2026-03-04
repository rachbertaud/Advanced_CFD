clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;
plot_settings(1);
cm = "turbo";

bx = 2;
by = 2;
Lx = 1;
Ly = 1;
A_vals = [0, 1e-5, 1e-4, 1e-3, 1e-2];
A_strs = {"0", "1e-5", "1e-4", "1e-3", "1e-2"};

for i = 1:length(A_vals)
    A = A_vals(i);
    A_str = A_strs{i};

    x = readmatrix(sprintf("xc_bx%.1f_by%.1f_A%s.dat", bx, by, A_str));
    y = readmatrix(sprintf("yc_bx%.1f_by%.1f_A%s.dat", bx, by, A_str));
    c = readmatrix(sprintf("c_bx%.1f_by%.1f_A%s.dat",  bx, by, A_str));

    ax_lim = [min(x), max(x)];
    ay_lim = [min(y), max(y)];

    [X, Y] = meshgrid(x, y);
    Nx = length(x);
    Ny = length(y);
    c_num = reshape(c, Ny, Nx);

    c_num_NB = c_num(2:Ny-1, 2:Nx-1)';
    X_NB = X(2:Ny-1, 2:Nx-1);
    Y_NB = Y(2:Ny-1, 2:Nx-1);
    Psi = -(A / (2*pi)) .* sin(2*pi*X_NB / (bx*Lx)) .* sin(2*pi*Y_NB / (by*Ly));

    f = figure(i);
    theme(f, "light");
    ax = gca;
    pcolor(ax, X_NB, Y_NB, c_num_NB)
    shading flat
    hold on
    contour(X_NB, Y_NB, Psi, 20, 'k', 'LineWidth', 0.5)
    title(sprintf("Numerical Solution,  A = %s", A_str))
    xlabel("x")
    ylabel("y")
    xlim(ax, ax_lim)
    ylim(ax, ay_lim)
    clim([min(c_num_NB(:)), max(c_num_NB(:))])
    colorbar
    colormap(ax, cm)
    hold off

    saveas(f, sprintf("HW3_Numerical_bx%.0f_by%.0f_A%s.png", bx, by, A_str), 'png')
end