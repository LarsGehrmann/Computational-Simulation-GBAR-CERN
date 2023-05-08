function plotWall(wallNo,wallHit,nBins,offset, saveDirStart, saveName, saveDirEnd, modRadius, frontLength)
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
distGrid = zeros(nBins(1),nBins(1));
scoreGrid = zeros(nBins(1),nBins(1));

scRow = zeros(1,length(wallHit));
distRow = zeros(1,length(wallHit));
for i=1:length(wallHit)
    [sc,dist]= scoreEnergy(wallHit(4,i), frontLength);
    scRow(i) = sc;
    distRow(i) = dist;
end
clear sc dist
wallHit = [wallHit; scRow; distRow];


avgE = 0;
step = 2*offset / (nBins(1));
for k = 1:length(wallHit)
    i = 1 + floor((wallHit(idx1,k)+offset)/step);
    j = 1 + floor((wallHit(idx2,k)+offset)/step);
    HitGrid(i,j) = HitGrid(i,j) + 1;
    EGrid(i,j) = EGrid(i,j) + wallHit(4,k);

    scoreGrid(i,j) = scoreGrid(i,j) + wallHit(5,k);
    distGrid(i,j) = distGrid(i,j) + wallHit(6,k);

    avgE = wallHit(4,k) + avgE;
end
for i = 1:nBins
    for j = 1:nBins
        if HitGrid(i,j) ~= 0
            EGrid(i,j) = EGrid(i,j) / HitGrid(i,j);
            distGrid(i,j) = distGrid(i,j) / HitGrid(i,j);
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


figure
imagesc(dir1,dir2,scoreGrid')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\textrm{Score}$','Interpreter','Latex');
%set(gca,'ColorScale','log')
titleHelp = {"$\textbf{Score}$", "$\textbf{Total score: } $" + string(sum(wallHit(5,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + "Score" +  saveDirEnd;
saveas(gcf,saveDir);


figure
imagesc(dir1,dir2,distGrid')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{d} / \textrm{cm}$','Interpreter','Latex');
%set(gca,'ColorScale','log')
titleHelp = {"$\textbf{Average distance of annihilation location}$", "$\textbf{to moderator surface}$", "$\textbf{Total hits: } $" + ...
    string(length(wallHit(1,:)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + "dist" +  saveDirEnd;
saveas(gcf,saveDir);

printBool = true;
metric = "hits";
[xCenterHits,zCenterHits,idxHits,maxPointsHits, noHitsHits, avgEHits] = findCircle(wallHit, modRadius, metric, printBool);
metric = "score";
[xCenterScore,zCenterScore,idxScore,maxPointsScore, noHitsScore, avgEScore] = findCircle(wallHit, modRadius, metric, printBool);



figure
plot(wallHit(1,:), wallHit(3,:), 'k.','MarkerSize', 5)
hold on
grid on
th = linspace(0,2*pi,1000);
xCircleHits = modRadius * cos(th) + xCenterHits;
zCircleHits = modRadius * sin(th) + zCenterHits;
xCircleScore = modRadius * cos(th) + xCenterScore;
zCircleScore = modRadius * sin(th) + zCenterScore;
plot(xCircleHits,zCircleHits,'r')
plot(xCircleScore,zCircleScore,'b')
legend("$\textrm{Hits}$", "$\textrm{Maximum hits}$", "$\textrm{Maximum score}$", 'Location', 'Northwest')
xlim([-offset,offset])
axis equal
xlabel(xlabelString)
ylabel(ylabelString)
titleHelp = {"$\textbf{Hits on fourth sample wall with circle radius: } r = $" + string(modRadius) + "$\textbf{ cm}$",
    "$\textbf{Center of maximum hits circle: (}$" + string(round(100*xCenterHits) / 100) + "$\textbf{,}$" + string(round(100*zCenterHits) / 100) + ...
    "$\textbf{)cm with }$" + string(noHitsHits) + "$\textbf{ hits}$",
    "$\textbf{Center of maximum score circle: (}$" + string(round(100*xCenterScore) / 100) + "$\textbf{,}$" + string(round(100*xCenterScore) / 100) + ...
    "$\textbf{)cm with }$" + string(noHitsScore) + "$\textbf{ hits}$",
    "$\textbf{Score of max score circle: }$" + string(round(100*maxPointsScore)/100)
    };

title(titleHelp)

ECircleHits = zeros(noHitsHits,1);
ECircleScore = zeros(noHitsScore,1);
circleCount = 1;
for j=1:length(wallHit)
    if sqrt( (xCenterHits - wallHit(1,j))^2 + (zCenterHits - wallHit(3,j))^2 ) <= modRadius
        ECircleHits(circleCount) = wallHit(4,j);
        circleCount = circleCount + 1;
    end
end

circleCount = 1;
for j=1:length(wallHit)
    if sqrt( (xCenterScore - wallHit(1,j))^2 + (zCenterScore - wallHit(3,j))^2 ) <= modRadius
        ECircleScore(circleCount) = wallHit(4,j);
        circleCount = circleCount + 1;
    end
end

edges = logspace(-2,1,50);
histHits = histcounts(ECircleHits,edges);
histScore = histcounts(ECircleScore,edges);




figure
barWidth = 1.3;
bar(log10(edges(1:end-1)),[histHits;histScore]','BarWidth', barWidth);
set(gca,'Xtick',-2:1); %// adjust manually; values in log scale
set(gca,'Xticklabel',10.^get(gca,'Xtick')); %// use labels with linear values
grid on
xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{No}$')
legend('$\textrm{Optimal circle hits}$','$\textrm{Optimal circle score}$','Location','Northwest')
titleHelp = {"$\textbf{Comparison between energy distribution}$", "$\textbf{inside optimal hits and optimal score circle}$",...
    "$\textbf{Hits in max hits circle: }$" + string(sum(histHits)) + "$\textbf{ with } \bar{E} = $" + string(round(1000*avgEHits)/1000) + "$\textbf{ MeV}$", ...
    "$\textbf{Hits in max score circle: }$" + string(sum(histScore)) + "$\textbf{ with } \bar{E} = $" + string(round(1000*avgEScore)/1000) + "$\textbf{ MeV}$"
};
title(titleHelp)



%
% ECircleHits = zeros(maxEnclosed,1);
% circleCount = 1;
% for i=1:length(wallHit)
%     if sqrt( (xCenter - wallHit(1,i))^2 + (zCenter - wallHit(3,i))^2 ) <= modRadius
%         ECircleHits(circleCount) = wallHit(4,i);
%         circleCount = circleCount + 1;
%     end
% end
% ECircleAvgHits = round(1000*sum(ECircleHits) / maxEnclosed) / 1000;
% fprintf("Average energy inside circle: " + string(ECircleAvgHits) + "MeV\n");
% edges = logspace(-2,1,50);
%
% figure
% hist(ECircleHits, edges)
% set(gca,'xscale','log')
% xlim([10^-2,10])
% grid on
% titleHelp = {"$\textbf{Kinetic energy of positrons in 'optimal' circle hits}$", "$\textbf{Number of hits in circle: }$" + string(maxEnclosed) + "$\textbf{; } \bar{E} \textbf{ inside circle: }$" + string(ECircleAvgHits) + "$\textbf{MeV}$"};
% title(titleHelp)
% xlabel('$E / \textrm{MeV}$')
% ylabel('$\textrm{No}$')
%

% %--------------------------------------------------------------------------------------------------------------------------------------%
% figure
% imagesc(dir1,dir2,scoreGrid')
% set(gca,'YDir','normal')
% xlabel(xlabelString)
% ylabel(ylabelString)
% hcb = colorbar;
% colorTitleHandle = get(hcb,'title');
% set(colorTitleHandle ,'String','$\textrm{Score}$','Interpreter','Latex');
% %set(gca,'ColorScale','log')
% titleHelp = {"$\textbf{Score}$", "$\textbf{Total score: } $" + string(sum(wallHit(5,:)))};
% title(titleHelp,'FontSize',14)
% saveDir = saveDirStart + saveName + "Score" +  saveDirEnd;
% saveas(gcf,saveDir);
%

% ECircleAvgScore = round(1000*sum(ECircleScore) / circleCount) / 1000;
% fprintf("Average energy inside circle score: " + string(ECircleAvgScore) + "MeV\n");
% edges = logspace(-2,1,50);
%

%end % if fourth wall

end % plotWall