function plot_ratioTargetDipole()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStart1 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\ratioTarDiWalls";
dirStart2 = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\ratioTarDiParameters";
dirEnd1 = "_nt_SampleWalls.csv";
dirEnd2 = "_nt_Parameters.csv";

maxRun = 4;
dipoleScale = zeros(1,maxRun);
lastWallHit = zeros(maxRun,0);
stdDev = zeros(maxRun,0);

ratio = -1;

innerNumber = 0;

for i=1:maxRun
    ratioCount = 0;
    clear ratio
    ratio(1) = 0.5;
    while ratio(end) < 2.1 - 0.00001 % ??
        dir1 = dirStart1 + string(ratioCount + (i-1) * innerNumber) + dirEnd1;
        dir2 = dirStart2 + string(ratioCount + (i-1) * innerNumber) + dirEnd2;
        try
            M = csvread(dir1, 8, 0);
            if i == 1
                lastWallHit(:,end+1) = zeros(maxRun,1);
                stdDev(:,end+1) = zeros(maxRun,1);
            end

            lastWallHit(i,ratioCount+1) = 0;
            stdDev(i,ratioCount+1) = 0;
            tempStore = zeros(3,1);
            for k = 1:length(M)
                if M(k,1) == 4
                    lastWallHit(i,ratioCount+1) = lastWallHit(i,ratioCount+1) + 1;
                    tempStore(:,lastWallHit(i,ratioCount+1)) = [M(k,2), M(k,3), M(k,4)] / 10; % mm -> cm
                end
            end
            stdDev(i,ratioCount+1) = std(tempStore(1,:)) + std(tempStore(3,:));
            % read parameters
            M = csvread(dir2, 14, 0);
            dipoleScale(i) = M(1,6);
            ratio(ratioCount+1) = M(1,9) / dipoleScale(i);
            ratioCount = ratioCount + 1;
        catch ME
            break
        end
    end
    innerNumber = ratioCount;
end

colors = ["b","g","r","c","m"];
figure
hold on
grid on
legendHelp = "empty";
for i = 1:maxRun
    plot(ratio,lastWallHit(i,:),colors(i))
    legendHelp(i) = "scaleDipole = " + string(dipoleScale(i));
end
xlabel('$\textrm{scaleTarget / scaleDipole}$')
ylabel('$\textrm{No. hits}$')
legend(legendHelp,'Location','Northwest')
title('$\textbf{Number of hits vs. ratio}$')

figure
hold on
grid on
for i = 1:maxRun
    plot(ratio,stdDev(i,:),colors(i))
    legendHelp(i) = "scaleDipole = " + string(dipoleScale(i));
end
xlabel('$\textrm{scaleDipole / scaleDipole}$')
ylabel('$(\sigma_x + \sigma_z) / \textrm{cm}$')
legend(legendHelp)
title('$\textbf{Standard deviation vs. ratio}$')

end
