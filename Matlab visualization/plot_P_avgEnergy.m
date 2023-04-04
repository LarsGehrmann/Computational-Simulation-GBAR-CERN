function plot_P_avgEnergy()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

noSim = 31;
step = 0.5;                   % [MeV] increase thickness by that step
noElectrons = 10^4;
avgEnergy = zeros(1,noSim);    % [cm] thickness of moderator
eDepTot = zeros(1,noSim);       % [eV] total deposited energy for different no of e-
eDepRel = zeros(1,noSim);       % [eV] deposited energy per e- for different no of e-
P = zeros(1,noSim);             % [W] required cooling power

dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\eDep_avgEnergy_";
dirEnd = ".txt";

for i = 1:noSim
    avgEnergy(i) = step * (i-1);
    if rem(avgEnergy(i),i) == 0 % if avgEnergy is whole number
       avgEnergyString = num2str(round(avgEnergy(i)));
    else
        avgEnergyString = num2str(avgEnergy(i));
    end

    dir = dirStart + num2str(avgEnergy(i)) + dirEnd;
    M = dlmread(dir, ',', 3, 0);
    eDepTot(i) = sum(M(:,4)) * 10^6;        % convert MeV -> eV
    eDepRel(i) = eDepTot(i) / noElectrons; 
    P(i) = reqW(eDepRel(i));
end

figure
plot(avgEnergy, P, 'kX')
hold on
grid on
%[X,Y,r2] = myLinReg(avgEnergy, P);
%plot(X,Y,'k')
titleHelp1 = '$\textbf{Required cooling power as a function of}$';
titleHelp2 =  '$\textbf{incident electron energy}$';
titleHelp = {titleHelp1,titleHelp2};
title(titleHelp,'FontSize',12)
xlabel('$\bar{E} / \textrm{MeV}$','FontSize',12)
ylabel('$P / \textrm{W}$','FontSize',12)
saveas(gcf,"C:\Users\Gehrm\OneDrive\Desktop\Master thesis\Presentations\Plots for presentation\P_avgE.png")
end