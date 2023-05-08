function plotRatioScore(modRadius, frontLength)

set(0,'defaultTextInterpreter','latex');
set(0, 'defaultLegendInterpreter','latex');
set(0, 'defaultAxesTickLabelInterpreter','latex');

dirStartWalls ="\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\scoreScalingTarNeRunWalls";
dirMidWalls = "DiRun";
dirEndWalls = "_nt_SampleWalls.csv";
dirStartParameters = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\scoreScalingTarNeRunParameters";
dirMidParameters = "DiRun";
dirEndParameters =  "_nt_Parameters.csv";

noTarNe = 4;
noDi = 16;

TarNeScales = zeros(noTarNe,1);
ratios = zeros(noDi,1);


hits = zeros(noTarNe,noDi);
scores = zeros(noTarNe,noDi);


for TarNeRun=0:noTarNe-1
    for DiRun=0:noDi-1

        wallHit = zeros(4,0);
        dirWalls = dirStartWalls + string(TarNeRun) +  dirMidWalls + string(DiRun) + dirEndWalls;
        allHits = csvread(dirWalls,9,0);
        allHits(:,2:4) = allHits(:,2:4) / 10; % mm->cm

        for i=1:length(allHits)
            if allHits(i,1) == 4
                wallHit(:,end+1) = allHits(i,2:5);
            end
        end
        scRow = zeros(1,length(wallHit));
        distRow = zeros(1,length(wallHit));
        for i=1:length(wallHit)
            [sc,dist]= scoreEnergy(wallHit(4,i), frontLength);
            scRow(i) = sc;
            distRow(i) = dist;
        end
        clear sc dist
        wallHit = [wallHit; scRow; distRow];

        printBool = false;
        metric = "hits";
        [xCenter,zCenter,idx,maxPoints, noHits, avgE] = findCircle(wallHit, modRadius, metric, printBool);
        hits(TarNeRun+1,DiRun+1) = maxPoints;
        metric = "score";
        [xCenter,zCenter,idx,maxPoints, noHits, avgE] = findCircle(wallHit, modRadius, metric, printBool);
        scores(TarNeRun+1,DiRun+1) = maxPoints;
        dirParameters =  dirStartParameters + string(TarNeRun) +  dirMidParameters + string(DiRun) + dirEndParameters;
        parameters = csvread(dirParameters, 14, 0);
        scaleDi = parameters(6);
        ratios(DiRun+1) = scaleDi / parameters(7);
    end
    TarNeScales(TarNeRun+1) = parameters(7);
end


colors = ["r", "b", "k", "m","c", "g", "y"];
figure('Renderer', 'painters', 'Position', [10 10 900 600])
pbaspect([1 1 1])


for i=1:noTarNe
    yyaxis left
    plotMatrix(2*i-1) = plot(ratios,hits(i,:),colors(i) + "-");
    hold on
    yyaxis right
    plotMatrix(2*i) = plot(ratios,scores(i,:), colors(i) + "-.");
    legendHelp(2*i-1) = "$\textrm{Hits, scTarNe} = $" + string(TarNeScales(i));
    legendHelp(2*i) = "$\textrm{Score, scTarNe} = $" + string(TarNeScales(i));

end
hold off
grid on
legend(plotMatrix,legendHelp,'Location','eastoutside')
xlabel('$\textrm{Ratio scaleDi / scaleTar}$')
yyaxis left
ylabel('$\textrm{Number of hits}$')
yyaxis right
ylabel('$\textrm{Score}$')
titleHelp = {"$\textbf{Optimization of dipole coil field scaling}$"
    ,
    };
title(titleHelp)
end
