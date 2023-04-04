clear all; clc; close all
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');



edges = logspace(-3,1,50);
dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\Histo";
dirEnd = "_nt_Title5.csv";

dir = dirStart + num2str(0) + dirEnd;

M = csvread(dir,8,0);

n = length(M);
TePTar = zeros(1,n);
TeMTar = zeros(1,n);
TePMod = zeros(1,n);
TeMMod = zeros(1,n);


TePTar = M(:,1);
TePTarLog = TePTar ~= -1;    % kick default entry -1
TePTar = TePTar(TePTarLog);
TeMTar = M(:,2);
TeMTarLog = TeMTar ~= -1;
TeMTar = TeMTar(TeMTarLog);
TePMod = M(:,3);
TePModLog = TePMod ~= -1;
TePMod = TePMod(TePModLog);
TeMMod = M(:,4);
TeMModLog = TeMMod ~= -1;
TeMMod = TeMMod(TeMModLog);

moderatorPositrons = length(TePMod)
moderatorElectrons = length(TeMMod);
totalPositrons = length(TePTar) + moderatorPositrons
totalElectrons = length(TeMTar) + length(TeMMod);
if moderatorPositrons ~= moderatorElectrons
    fprintf("Number of e+ in moderator is not equal number e- in moderator!")
end
if totalPositrons ~= totalElectrons
    fprintf("Number of total e+  is not equal number of total e-!")
end


figure
hold on
histfit(TePTar, edges)
set(gca,'xscale','log')
xlim([10^-2,10])
grid on
titleHelp1 = '$\textbf{Kinetic energy of positrons}$';
titleHelp2 = '$\textbf{generated in the target}$';
titleHelp = {titleHelp1 , titleHelp2};
title(titleHelp, 'Fontsize', 12)
xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{No}$')
