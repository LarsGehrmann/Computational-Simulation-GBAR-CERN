function plot_modEnd_noAnnihi()

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Visualization\HPC\modEndValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Visualization\HPC\modEndParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";

dModeratorEnd = 0;
noAnnihiModTotal = 0;
noAnnihiModEnd = 0;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 14, 0);
        noAnnihiModTotal(i) = M(1,7);
        noAnnihiModEnd(i) = M(1,9);
        M = csvread(dir2, 9, 0);
        dModeratorTotal = M(1,2);
        dModeratorEnd(i) = M(1,3);
    catch ME
        break
    end
    i = i + 1;
end

noAnnihiModTotal = noAnnihiModTotal / 10^7; % 10^7
noAnnihiModEnd = noAnnihiModEnd / 10^7; % 10^7


% paperIncoming = 2.4 * 10^9;
% paperSlow = 1.2 * 10^7;
% paperEff = paperSlow / paperIncoming;
paperEff = 3 * 10^-3;

dModeratorTotal = dModeratorTotal * 10^3; % mm -> um
dModeratorEnd = dModeratorEnd * 10^3; % mm -> um
[X,Y,sigma] = myAvg(dModeratorEnd,noAnnihiModTotal);
figure
hold on
plot(dModeratorEnd, noAnnihiModEnd,'rX')
plot(dModeratorEnd,noAnnihiModTotal,'ko')
plot(X,Y,'k')
yline(paperEff,'b')
grid on
xlabel('$d_{\textrm{Mod,End}} / \mu \textrm{m}$','FontSize',12)
ylabel('$\textrm{Annihilation efficiency}$')
legendHelp = "$\textrm{Mean-fit: } \mu=$" + num2str(Y(1)) + ", $\sigma=$" + num2str(sigma);
legend('$\textrm{End of moderator}$', '$\textrm{Total moderator}$',legendHelp, '$\textrm{Reference slow }e^{+} \textrm{ efficiency}$','Fontsize',11)
legend('Location','West')
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\modEnd.png")

titleHelp = {"$\textbf{Annihilation ratio as a function of moderator end-thickness}$", "$\textbf{for a total moderator thickness of } d = 50 \mu \textbf{m}$"};
title(titleHelp, 'Fontsize',13)

