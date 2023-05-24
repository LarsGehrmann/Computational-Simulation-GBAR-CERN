function plot_distTarMod_P()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\distTarModValues";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\distTarModParameters";
dirEnd1 = "_nt_Title1.csv";
dirEnd2 = "_nt_Title3.csv";
distTarMod = 0;
i = 1;
while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 14, 0);
        eDepTot(i) = M(1,1) * 10^6;        % convert MeV -> eV
        M = csvread(dir2, 8, 0);
        distTarMod(i) = M(1,1);
    catch ME
        break
    end
    i = i + 1;
end
%noElectrons = 10^(ceil(log10(n)));
noElectrons = 100000;
eDepRel = eDepTot / noElectrons;
P = reqW(eDepRel);
[X,Y,r2] = myLinReg(distTarMod,P);
format long
r2
format short
figure
hold on
distTarMod = distTarMod(1:32);
P = P(1:32);
plot(distTarMod, P, 'kX')
%plot(X,Y,'k')
grid on
titleHelp1 = '$\textbf{Required cooling power as a function of distance}$';
titleHelp2 =  '$\textbf{between moderator and target}$';
titleHelp = {titleHelp1,titleHelp2};
%title(titleHelp,'FontSize',12)
xlabel('$\textrm{dist} / \textrm{mm}$','FontSize',12)
ylabel('$P / \textrm{W}$','FontSize',12)
legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthEast')
%saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_distTarMod.png")
end