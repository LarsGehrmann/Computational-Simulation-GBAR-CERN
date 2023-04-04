function NoPosDist()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

noSim = 15;
step = 0.5;                   % [cm] increase distance by that step
noElectrons = 10^5;
distTarMod = zeros(1,noSim);    % [cm] thickness of moderator
noPos = zeros(1,noSim);         % absolute number of generated positrons
noPosRel = zeros(1,noSim);         % number of positrons per electron

dirStart = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task1\build\positronPop_";
dirEnd = ".txt";

for i = 1:noSim
    distTarMod(i) = step * (i-1) + 0.2; 
    dir = dirStart + num2str(distTarMod(i)) + dirEnd;
    M = dlmread(dir, ',', 3, 0);
    noPos(i) = M(4);
end
noPosRel = noPos / noElectrons;

figure
plot(distTarMod, noPosRel, 'kX')
grid on
