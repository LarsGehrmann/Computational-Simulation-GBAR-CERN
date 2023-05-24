function plot_eDep_noElectrons()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');
noSim = 10;
format long
noElectrons = zeros(1,noSim);
eDepTot = zeros(1,noSim);  % [MeV] total deposited energy for different no of e-
eDepRel = zeros(1,noSim);  % [MeV] deposited energy per e- for different no of e-

dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDep_noElectrons_";
dirEnd = ".txt";
for i = 1:noSim
    noElectrons(i) = 10^4 * i;
    dir = dirStart + num2str(noElectrons(i)) + dirEnd;
    M = dlmread(dir, ',', 3, 0);
    eDepTot(i) = sum(M(:,4));
    eDepRel(i) = sum(M(:,4)) / noElectrons(i);
end

figure
subplot(2,1,1);
hold on
plot(noElectrons, eDepTot, 'kX')
grid on
[X,Y,r2] = myLinReg(noElectrons, eDepTot);
r2
plot(X,Y,'k')
%title('$\textbf{Total energy deposited in copper foil}$','FontSize',12)
xlabel('$\textrm{No } e^{-}$','FontSize',12)
ylabel('$E_{\textrm{dep}} / \textrm{MeV}$','FontSize',12)
%legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
%legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthWest')

subplot(2,1,2);
hold on
plot(noElectrons, eDepRel, 'kX')
grid on
[X,Y,sigma] = myAvg(noElectrons, eDepRel);
Y(1)
sigma
plot(X,Y,'k')
%title('$\textbf{Energy deposited in copper foil per electron}$','FontSize',12)
xlabel('$\textrm{No } e^{-}$','FontSize',12)
ylabel('$E_{\textrm{dep}} / \textrm{MeV}$','FontSize',12)
%legendHelp = "$\textrm{Mean-fit: } \mu=$" + num2str(Y(1)) + ", $\sigma=$" + num2str(sigma);
%legend('$\textrm{Simulated values}$', legendHelp,'Location','NorthWest')
format short
%saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\eDep_no_e.png")
end