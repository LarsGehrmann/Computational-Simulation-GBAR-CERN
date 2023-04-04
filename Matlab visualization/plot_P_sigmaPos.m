function plot_P_sigmaPos()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

noSim = 11;
step = 10;                   % [1] increase sigma by that step
noElectrons = 10^4;
sigma = zeros(1,noSim);    % [1] std deviation of Gaussian beam for incident electrons
eDepTot = zeros(1,noSim);       % [eV] total deposited energy for different no of e-
eDepRel = zeros(1,noSim);       % [eV] deposited energy per e- for different no of e-
P = zeros(1,noSim);             % [W] required cooling power

dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDep_sigmaPos_";
dirEnd = ".txt";

for i = 1:noSim
    sigma(i) = step * (i-1);
    if rem(sigma(i),i) == 0 % if sigma is whole number
       sigmaString = num2str(round(sigma(i)));
    else
        sigmaString = num2str(sigma(i));
    end

    dir = dirStart + num2str(sigma(i)) + dirEnd;
    M = dlmread(dir, ',', 3, 0);
    eDepTot(i) = sum(M(:,4)) * 10^6;        % convert MeV -> eV
    eDepRel(i) = eDepTot(i) / noElectrons; 
    P(i) = reqW(eDepRel(i));
end

figure
plot(sigma, P, 'kX')
hold on
grid on
[X,Y,r2] = myLinReg(sigma, P);
plot(X,Y,'k')
titleHelp1 = '$\textbf{Required cooling power as a function of standard}$';
titleHelp2 =  '$\textbf{deviation}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$\sigma / \textrm{mm}$','FontSize',12)
ylabel('$P / \textrm{W}$','FontSize',12)
legendHelp = '$\textrm{Linear fit: }' + "r^2=$ "+ num2str(r2);
legend('$\textrm{Simulated values}$', legendHelp ,'Location','NorthWest')
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_sigmaPos.png")
end