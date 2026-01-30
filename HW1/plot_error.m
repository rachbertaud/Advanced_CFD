plot_settings(1) %this turns on a file with settings i like for MATLAB plots

A = readmatrix("HW1_Error_Data.csv");
%%
close all

N = A(:,1);
Err_inf = A(:,2);

f = figure(1);
theme(f,"light");
hold on
plot(N, (Err_inf), 'Color',[227/255,159/255,246/255])
plot(N, 1./N, '.-.', 'Color',[240/255,159/255,200/255])
plot(N, 1./(N.^2), '--', 'Color',[220/255,200/255,246/255])
set(gca,'YScale','log','XScale','log')
legend('Results from HW1 Solution', '$\cal{O}$$(h)$ Reference Line', '$\cal{O}$$(h^2)$ Reference Line', 'Location','southwest')
ylabel("Relative Error of Solution, $E_{\infty}$")
xlabel("Number of Grid Points, $N$")
hold off

saveas(f, "HW1_Error_Plot.png", 'png')