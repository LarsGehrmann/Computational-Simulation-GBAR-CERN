function plot_avgE_noPos()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\avgEValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\avgEParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";
avgE = -1;  % [MeV] average energy of incident electrons
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 7, 0);
        noPos(i) = M(end,2);
        n = M(end,1);       % largest event number
        M = csvread(dir2, 8, 0);
        avgE(i) = M(1,4);
    catch ME
        i
        break
    end
    i = i + 1;
end
noElectrons = 10^(ceil(log10(n)))
noPosEff = noPos / noElectrons;
figure
plot(avgE, noPosEff, 'kX')
hold on
grid on
%[X,Y,r2] = myLinReg(dModerator, P);
%plot(X,Y,'k')
titleHelp1 = '$\textbf{Positron efficiency as a function of}$';
titleHelp2 =  '$\textbf{average energy of incident electrons}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$\bar{E} / \textrm{MeV}$','FontSize',12)
ylabel('$\eta$','FontSize',12)
%legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthWest')
%legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthEast')
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\avgE_noPos.png")
end