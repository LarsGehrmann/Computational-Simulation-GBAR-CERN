function plot_ratioDiNe()
set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');


dirStartWalls ="\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\hitsScalingDiNeRunWalls";
dirMidWalls = "NeRun";
dirEndWalls = "_nt_SampleWalls.csv";
dirStartParameters = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\hitsScalingDiNeRunParameters";
dirMidParameters = "DiRun";
dirEndParameters =  "_nt_Parameters.csv";


noDi = 4;
noNe = 15;

diScales = zeros(1,noDi);
ratio = zeros(1,noNe);

wallHitsNo = zeros(noDi,noNe);
circleHitsNo = zeros(noDi,noNe);
modRadius = 2.5;
metric = "hits";
printBool = false;


for DiRun=0:noDi-1
    for ratioRun=0:noNe-1
        wallHits = zeros(4,0);
        dirWalls = dirStartWalls + string(DiRun) +  dirMidWalls + string(ratioRun) + dirEndWalls;
        allHits = csvread(dirWalls,9,0);
        allHits(:,2:4) = allHits(:,2:4) / 10; % mm->cm
        for i=1:length(allHits)
            if allHits(i,1) == 4
                wallHits(:,end+1) = allHits(i,2:5);
            end
        end
        wallHitsNo(DiRun+1,ratioRun+1) = length(wallHits);
        [xCenter,zCenter,idx,maxPoints,noHits, avgE] = findCircle(wallHits, modRadius, metric, printBool);
        circleHitsNo(DiRun+1,ratioRun+1) = maxPoints;
        dirParameters =  dirStartParameters + string(DiRun) +  dirMidParameters + string(ratioRun) + dirEndParameters;
        parameters = csvread(dirParameters,14,0);
        neScale = parameters(7);
        diScales(DiRun+1) = parameters(6);
        ratio(ratioRun+1) = neScale/diScales(DiRun+1);
    end
end

colors = ["r", "b", "k", "m","c", "g", "y"];
figure('Renderer', 'painters', 'Position', [10 10 900 600])
pbaspect([1 1 1])

for i=1:noDi
    yyaxis left
    plotMatrix(2*i-1) = plot(ratio,wallHitsNo(i,:),colors(i) + "-");
    hold on
    yyaxis right
    plotMatrix(2*i) = plot(ratio,circleHitsNo(i,:), colors(i) + "-.");
    legendHelp(2*i-1) = "$\textrm{Hits fourth wall, scDi} = $" + string(diScales(i));
    legendHelp(2*i) = "$\textrm{Hits circle, scDi} = $" + string(diScales(i));
end


hold off
grid on
legend(plotMatrix,legendHelp,'Location','eastoutside')
xlabel('$\textrm{Ratio scaleNe / scaleDi}$')
yyaxis left
ylabel('$\textrm{No. hits on fourth sample wall}$')
yyaxis right
ylabel('$\textrm{No. hits inside circle}$')
titleHelp = {"$\textbf{Number of hits as a function of ratio of}$",
    "$\textbf{scaling of neon coil and dipole coil}$"
    };
title(titleHelp)

end
