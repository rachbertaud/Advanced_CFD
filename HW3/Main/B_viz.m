clear
addpath /Users/rachelbertaud/code/cmap-master;
addpath /Users/rachelbertaud/code/MATLAB_Settings/;
plot_settings(1);
cm = "turbo";

A = 0.015;
A_str = "0.015";
Lx = 1;
Ly = 1;
B_vals = [1.0, 0.5, 0.25];
B_strs = {"1.0", "0.5", "0.25"};

for i = 1:length(B_vals)
    B = B_vals(i);
    B_str = B_strs{i};

    x = readmatrix(sprintf("xc_bx%s_by%s_A%s.dat", B_str, B_str, A_str));
    y = readmatrix(sprintf("yc_bx%s_by%s_A%s.dat", B_str, B_str, A_str));
    c = readmatrix(sprintf("c_bx%s_by%s_A%s.dat",  B_str, B_str, A_str));

    ax_lim = [min(x), max(x)];
    ay_lim = [min(y), max(y)];

    [X, Y] = meshgrid(x, y);
    Nx = length(x);
    Ny = length(y);
    c_num = reshape(c, Ny, Nx);

    c_num_NB = c_num(2:Ny-1, 2:Nx-1)';
    X_NB = X(2:Ny-1, 2:Nx-1);
    Y_NB = Y(2:Ny-1, 2:Nx-1);
    Psi = -(A / (2*pi)) .* sin(2*pi*X_NB / (B*Lx)) .* sin(2*pi*Y_NB / (B*Ly));

    f = figure(i);
    theme(f, "light");
    ax = gca;
    pcolor(ax, X_NB, Y_NB, c_num_NB)
    shading flat
    hold on
    contour(X_NB, Y_NB, Psi, 2, 'k', 'LineWidth', 0.5)
    hold off
    title(sprintf("Numerical Solution,  A = %s,  bx = by = %s", A_str, B_str), 'Interpreter', 'none')
    xlabel("x")
    ylabel("y")
    xlim(ax, ax_lim)
    ylim(ax, ay_lim)
    clim([min(c_num_NB(:)), max(c_num_NB(:))])
    colorbar
    colormap(ax, cm)

    saveas(f, sprintf("HW3_Numerical_bx%s_by%s_A%s.png", B_str, B_str, A_str), 'png')
end
