function plotWall(wallNo,wallHit,nBins,offset, saveDirStart, saveName, saveDirEnd, modRadius)
idx1 = 0;
idx2 = 0;
if wallNo == 0
    noString = "\textbf{zeroth}";
    xlabelString = '$y / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
    idx1 = 2;
    idx2 = 3;
elseif wallNo == 1
    noString = "\textbf{first}";
    xlabelString = '$y / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
    idx1 = 2;
    idx2 = 3;
elseif wallNo == 2
    noString = "\textbf{second}";
    xlabelString = '$y / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
    idx1 = 2;
    idx2 = 3;
elseif wallNo == 3
    noString = "\textbf{third}";
    xlabelString = '$x / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
    idx1 = 1;
    idx2 = 3;
elseif wallNo == 4
    noString = "\textbf{fourth}";
    xlabelString = '$x / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
    idx1 = 1;
    idx2 = 3;
end
nBins = [nBins,nBins];
HitGrid = zeros(nBins(1),nBins(1));
EGrid = zeros(nBins(1),nBins(1));
EGridCount = zeros(nBins(1),nBins(1));
avgE = 0;
step = 2*offset / (nBins(1));
for k = 1:length(wallHit)
    i = 1 + floor((wallHit(idx1,k)+offset)/step);
    j = 1 + floor((wallHit(idx2,k)+offset)/step);
    HitGrid(i,j) = HitGrid(i,j) + 1;
    EGrid(i,j) = EGrid(i,j) + wallHit(4,k);
    avgE = wallHit(4,k) + avgE;
end
for i = 1:nBins
    for j = 1:nBins
        if HitGrid(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / HitGrid(i,j);
        end
    end
end
dir1 = [-offset offset];
dir2 = [-offset offset];
avgE = round(1000 * avgE / sum(sum(HitGrid))) / 1000;

figure
imagesc(dir1,dir2,HitGrid')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
titleHelpHelp = "$\textbf{Positrons passing through }" + noString + "\textbf{ sample wall}$";
titleHelp = {titleHelpHelp, "$\textbf{Total positrons: } $" + string(length(wallHit(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(wallNo) + saveDirEnd;
saveas(gcf,saveDir);

figure
imagesc(dir1,dir2,EGrid')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
titleHelpHelp = "$\bar{E} \textbf{ of positrons passing through }$" + noString + "$\textbf{ sample wall}$";
titleHelp = {titleHelpHelp, "$\textbf{Total positrons: } $" + string(length(wallHit(1,:))), "$\textbf{Total average: }$" + string(avgE) + "$\textbf{MeV}$"};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + string(wallNo) + "E" +  saveDirEnd;
saveas(gcf,saveDir);

maxIdx = 1;
noEncircled = zeros(length(wallHit),1);
countEncircled = 0;
if wallNo == 4
    for i=1:length(wallHit)
        countEncircled = 0;
        xMid = wallHit(1,i);
        zMid = wallHit(3,i);
        for j=1:length(wallHit)
            if sqrt( (xMid - wallHit(1,j))^2 + (zMid - wallHit(3,j))^2) <= modRadius
                countEncircled = countEncircled + 1;
            end
        end
        noEncircled(i) = countEncircled;
    end
    [maxEnclosed,maxIDX] = max(noEncircled);
    xCenter = wallHit(1,maxIDX);
    zCenter = wallHit(3,maxIDX);
    fprintf("'Optimal' circle with radius r=" + string(modRadius) + "cm and midpoint:\n")
    fprintf("x: " + string(xCenter) + "cm\n")
    fprintf("z: " + string(zCenter) + "cm\n")
    fprintf("Number of registered hits in that circle: " + string(noEncircled(maxIDX)) + "\n")

    figure
    plot(wallHit(1,:), wallHit(3,:), 'k.','MarkerSize', 5)
    hold on
    grid on
    th = linspace(0,2*pi,1000);
    xCircle = modRadius * cos(th) + xCenter;
    zCircle = modRadius * sin(th) + zCenter;
    plot(xCircle,zCircle,'r')
    xlim([-offset,offset])
    axis equal
    xlabel(xlabelString)
    ylabel(ylabelString)
    titleHelp = {"$\textbf{Hits on fourth sample wall with 'optimal' circle}$", "$\textbf{with radius: } r = $" + string(modRadius) + " $\textbf{cm and center: }c = \textbf{(}$" + string(xCenter) + "$,$" + string(zCenter) + "$\textbf{)cm}$", "$\textbf{Total hits inside circle: }$" + string(maxEnclosed)};
    title(titleHelp)

    ECircle = zeros(maxEnclosed,1);
    circleCount = 1;
    for i=1:length(wallHit)
        if sqrt( (xCenter - wallHit(1,i))^2 + (zCenter - wallHit(3,i))^2 ) <= modRadius
            ECircle(circleCount) = wallHit(4,i);
            circleCount = circleCount + 1;
        end
    end
    ECircleAvg = round(1000*sum(ECircle) / maxEnclosed) / 1000;
    fprintf("Average energy inside circle: " + string(ECircleAvg) + "MeV\n");
    edges = logspace(-2,1,50);
    figure
    hist(ECircle, edges)
    set(gca,'xscale','log')
    xlim([10^-2,10])
    grid on
    titleHelp = {"$\textbf{Kinetic energy of positrons in 'optimal' circle}$", "$\textbf{Number of hits in circle: }$" + string(maxEnclosed) + "$\textbf{; } \bar{E} \textbf{ inside circle: }$" + string(ECircleAvg) + "$\textbf{MeV}$"};
    title(titleHelp)
    xlabel('$E / \textrm{MeV}$')
    ylabel('$\textrm{No}$')
end % if fourth wall

end % plotWall