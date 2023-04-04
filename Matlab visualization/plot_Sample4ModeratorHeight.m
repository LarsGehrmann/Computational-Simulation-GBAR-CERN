%visualize the deposited energy in the moderator because Geant4 is not working properly with that

function plot_Sample4ModeratorHeight()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\height";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\heightParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";

modHeight = -1;
lastWallHit = -1;
i = 1;

while true
    dir1 = dirStart1 + num2str(i-1) + dirEnd1
    dir2 = dirStart2 + num2str(i-1) + dirEnd2
    try
        M = csvread(dir1, 8, 0);
        lastWallHit(i) = 0;
        for k = 1:length(M)
            if (M(k,1) == 4)
                lastWallHit(i) = lastWallHit(i) + 1; % hits on last sampling wall
            end
        end
        M = csvread(dir2, 14, 0);   %% read parameters
        modHeight(i) = M(1,5) / 10; % mm->cm
    catch ME
        break
    end
    i = i + 1;
end
fprintf("Number of heights: " + i + "\n");
figure 
plot(modHeight, lastWallHit, 'kX')
hold on
grid on
xlabel('$\textrm{moderator height/cm}$')
ylabel('$\textrm{Number of hits}$')
titleHelp = "$\textbf{Number of positron hits for different moderator heights}$";
title(titleHelp)
end