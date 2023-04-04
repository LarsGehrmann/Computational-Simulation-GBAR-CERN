%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_Sample4distTargetOrigin()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\SampleWalls";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\ConstructionParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Construction Parameters.csv";

distTarOri = -1;
lastWallHit = -1;
i = 1;

while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1;
    dir2 = dirStart2 + num2str(i-1) + dirEnd2;
    try
        M = csvread(dir1, 8, 0);
        lastWallHit(i) = 0;
        for k = 1:length(M)
            if (M(k,1) == 4)
                lastWallHit(i) = lastWallHit(i) + 1; % hits on last sampling wall
            end
        end
        M = csvread(dir2, 14, 0);   %% read parameters
        distTarOri(i) = M(1,4) / 10; % mm->cm
    catch ME
        break
    end
    i = i + 1;
end
fprintf("Number of distances: " + i + "\n");
figure 
plot(distTarOri, lastWallHit, 'kX')
hold on
f = fit(distTarOri',lastWallHit','gauss2');
X = min(distTarOri);
Y = max(distTarOri);
x = linspace(X,Y,1000);
plot(x,f(x),'r')
grid on
legend('$\textrm{Simulated values}$', '')
xlabel('$\textrm{dist/cm}$')
ylabel('$\textrm{Number of hits}$')
legend('$\textrm{Simulated values}$', '$\textrm{Gaussian fit}$','Location','Northwest')
titleHelp = {"$\textbf{Number of positron hits for different distances}$", "$\textbf{between target and origin}$"};
title(titleHelp)
end