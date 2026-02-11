% 50 5.1118e-07
% 100 5.0279e-07
% 200 5.0069e-07
% 500 9.9997e-07


% ADding km 
% 50 0.0020
% 100 4.9312e-04
% 200 1.2375e-04
% 400 3.1494e-05

%% BEFORE KM
% N = [50 100 200 400];
% Err_inf = [5.0149e-05 1.2997e-05 3.6082e-06 1.2758e-06];

%% WITH KM
N = [50 100 200 400];
Err_inf = [0.0020 4.9312e-04 1.2375e-04 3.1494e-05];

addpath /Users/rachelbertaud/code/MATLAB_Settings/;

plot_settings(1);



% 100 4.9312e-04
% 200 1.2375e-04
% 400 3.1494e-05

f = figure(1);
theme(f,"light");
hold on
plot(N, (Err_inf), 'Color',[227/255,159/255,246/255])
plot(N, 1./N, '.-.', 'Color',[240/255,159/255,200/255])
plot(N, 1./(N.^2), '--', 'Color',[220/255,200/255,246/255])
set(gca,'YScale','log','XScale','log')
legend('Results from HW2 Solution', '$\cal{O}$$(h)$ Reference Line', '$\cal{O}$$(h^2)$ Reference Line', 'Location','northeast')
ylabel("Relative Error of Solution, $E_{\infty}$")
xlabel("Number of Grid Points, $N$")
hold off

saveas(f, "HW2_Error_Plot_After_Km.png", 'png')