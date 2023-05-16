function plot_ratioTarNe()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');


dirStartWalls ="\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\hitsScalingTarNeRunWalls";
dirMidWalls = "NeRun";
dirEndWalls = "_nt_SampleWalls.csv";
dirStartParameters = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\hitsScalingTarNeRunParameters";
dirMidParameters = "NeRun";
dirEndParameters =  "_nt_Parameters.csv";


noTar = 4;
noNe = 15;

tarScales = zeros(1,noTar);
ratio = zeros(1,noNe);

wallHitsNo = zeros(noTar,noNe);
circleHitsNo = zeros(noTar,noNe);
modRadius = 2.5;
metric = "hits";
printBool = false;


for TarRun=0:noTar-1
    for ratioRun=0:noNe-1
        wallHits = zeros(4,0);
        dirWalls = dirStartWalls + string(TarRun) +  dirMidWalls + string(ratioRun) + dirEndWalls;
        allHits = csvread(dirWalls,9,0);
        allHits(:,2:4) = allHits(:,2:4) / 10; % mm->cm
        for i=1:length(allHits)
            if allHits(i,1) == 4
                wallHits(:,end+1) = allHits(i,2:5);
            end
        end
        wallHitsNo(TarRun+1,ratioRun+1) = length(wallHits);
        [xCenter,zCenter,idx,maxPoints,noHits, avgE] = findCircle(wallHits, modRadius, metric, printBool);
        circleHitsNo(TarRun+1,ratioRun+1) = maxPoints;
        dirParameters =  dirStartParameters + string(TarRun) +  dirMidParameters + string(ratioRun) + dirEndParameters;
        parameters = csvread(dirParameters,14,0);
        neScale = parameters(7);
        tarScales(TarRun+1) = parameters(9);
        ratio(ratioRun+1) = neScale/tarScales(TarRun+1);
    end
end

colors = ["r", "b", "k", "m","c", "g", "y"];
figure('Renderer', 'painters', 'Position', [10 10 900 600])
pbaspect([1 1 1])

for i=1:noTar
    yyaxis left
    plotMatrix(2*i-1) = plot(ratio,wallHitsNo(i,:),colors(i) + "-");
    hold on
    yyaxis right
    plotMatrix(2*i) = plot(ratio,circleHitsNo(i,:), colors(i) + "-.");
    legendHelp(2*i-1) = "$\textrm{Hits fourth wall, scTar} = $" + string(tarScales(i));
    legendHelp(2*i) = "$\textrm{Hits circle, scTar} = $" + string(tarScales(i));
end


hold off
grid on
legend(plotMatrix,legendHelp,'Location','eastoutside')
xlabel('$\textrm{Ratio scaleNe / scaleTar}$')
yyaxis left
ylabel('$\textrm{No. hits on fourth sample wall}$')
yyaxis right
ylabel('$\textrm{No. hits inside circle}$')
titleHelp = {"$\textbf{Number of hits as a function of ratio of}$",
    "$\textbf{scaling of neon coil and target coil}$"
    };
title(titleHelp)

end
