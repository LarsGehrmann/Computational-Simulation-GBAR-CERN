function plot_dModerator_P()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\dModeratorValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\dModeratorParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";
dModerator = -1;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 6, 0);
        eDepTot(i) = M(1,1) * 10^6;        % convert MeV -> eV
        M = csvread(dir2, 8, 0);
        dModerator(i) = M(1,2);
    catch ME
        break
    end
    i = i + 1;
end
noElectrons = 10000;
eDepRel = eDepTot / noElectrons;
P = reqW(eDepRel);
figure
plot(dModerator, P, 'kX')
hold on
grid on
titleHelp1 = '$\textbf{Required cooling power as a function of}$';
titleHelp2 =  '$\textbf{moderator thickness}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$d_{\textrm{Moderator}} / \textrm{mm}$','FontSize',12)
ylabel('$P / \textrm{W}$','FontSize',12)
%legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthWest')
%legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthEast')
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_dModerator.png")
end