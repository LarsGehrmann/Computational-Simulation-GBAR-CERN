function [maxHitsNew, maxENew] = plotWall(wallNo,wallHit,nBins,offset, saveDirStart, saveName, saveDirEnd, modRadius, frontLength, maxHits, maxE)
fontSizeLegend = 25;
fontSizeAxes = 17;
fontSize = 50;
figSize(1) = 1200;
figSize(2) = 1100;
newLabelX = -200;
newLabelY = 540;
colorText = [0.6 0.6 0.6];
colorText = [1 1 1];
idx1 = 0;
idx2 = 0;
if wallNo == 0
    noString = "\textbf{zeroth}";
    xlabelString = '$y / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
%     h(1)=xlabel('$y$/cm');
%     h(2)=ylabel('$z$/cm');
    idx1 = 2;
    idx2 = 3;
elseif wallNo == 1
    noString = "\textbf{first}";
    xlabelString = '$y / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
%     h(1)=xlabel('$y$/cm');
%     h(2)=ylabel('$z$/cm');
    idx1 = 2;
    idx2 = 3;
elseif wallNo == 2
    noString = "\textbf{second}";
    xlabelString = '$y / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
%     h(1)=xlabel('$y$/cm');
%     h(2)=ylabel('$z$/cm');
    idx1 = 2;
    idx2 = 3;
elseif wallNo == 3
    noString = "\textbf{third}";
    xlabelString = '$x / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
%     h(1)=xlabel('$x$/cm');
%     h(2)=ylabel('$z$/cm');
    idx1 = 1;
    idx2 = 3;
elseif wallNo == 4
    noString = "\textbf{fourth}";
    xlabelString = '$x / \textrm{cm}$';
    ylabelString = '$z / \textrm{cm}$';
%     h(1)=xlabel('$x$/cm');
%     h(2)=ylabel('$z$/cm');
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

maxHitsNew = max(max(max(HitGrid)),maxHits);
maxENew = max(max(max(EGrid)),maxE);

dir1 = [-offset offset];
dir2 = [-offset offset];
avgE = round(1000 * avgE / sum(sum(HitGrid))) / 1000;



figure('Renderer', 'painters', 'Position', [10 10 figSize(1) figSize(2)])
%pbaspect([1 1 1])
imagesc(dir1,dir2,HitGrid')
set(gca,'YDir','normal')
%xlabel(xlabelString)
%ylabel(ylabelString)
set(gca,'xtick',[])
set(gca,'xticklabel',[])
set(gca,'ytick',[])
set(gca,'yticklabel',[])
hcb = colorbar;
set(hcb,'position',[.88 .138 .025 .75])
set(hcb,'AxisLocation','in')
hcb.Color = colorText;
%hcb.AxisLocation = 'in'
%caxis([0, maxHitsNew])
colorTitleHandle1 = get(hcb,'title');
set(colorTitleHandle1 ,'String','$N \textrm{ hits}$','Interpreter','Latex');
set(colorTitleHandle1 , 'Color', [1 1 1])
labelPosition = get(colorTitleHandle1, 'Position');
newLabelPosition = labelPosition;
newLabelPosition(1) = newLabelX;
newLabelPosition(2) = newLabelY;

set(colorTitleHandle1, 'Position', newLabelPosition);
%titleHelpHelp = "$\textbf{Positrons passing through }" + noString + "\textbf{ sample wall}$";
%titleHelp = {titleHelpHelp, "$\textbf{Total positrons: } $" + string(length(wallHit(1,:)))};
%title(titleHelp,'FontSize',14)
ax = gca;
ax.FontSize = fontSize;
saveDir = saveDirStart + saveName + string(wallNo) + saveDirEnd;
exportgraphics(gcf,saveDir);



figure('Renderer', 'painters', 'Position', [10 10 figSize(1) figSize(2)])
%pbaspect([1 1 1])
imagesc(dir1,dir2,EGrid')
set(gca,'YDir','normal')
%xlabel(xlabelString)
%ylabel(ylabelString)
set(gca,'xtick',[])
set(gca,'xticklabel',[])
set(gca,'ytick',[])
set(gca,'yticklabel',[])
hcb = colorbar;
set(hcb,'position',[.88 .138 .025 .75])
set(hcb,'AxisLocation','in')
hcb.Color = colorText;
%hcb.AxisLocation = 'in'
%caxis([0, maxENew])
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
set(colorTitleHandle , 'Color', [1 1 1])
labelPosition = get(colorTitleHandle, 'Position');
newLabelPosition = labelPosition;
newLabelPosition(1) = newLabelX + 50;
newLabelPosition(2) = newLabelY - 5;

set(colorTitleHandle, 'Position', newLabelPosition);
%titleHelpHelp = "$\textbf{Positrons passing through }" + noString + "\textbf{ sample wall}$";
%titleHelp = {titleHelpHelp, "$\textbf{Total positrons: } $" + string(length(wallHit(1,:)))};
%title(titleHelp,'FontSize',14)
ax = gca;
ax.FontSize = fontSize;
saveDir = saveDirStart + saveName + string(wallNo) + "E" +  saveDirEnd;
exportgraphics(gcf,saveDir);
%---------------------------------------------------------------------------------------------%

if wallNo ~= 4
    return
end


% printBool = true;
% metric = "hits";
% [xCenterHits,zCenterHits,idxHits,maxPointsHits, noHitsHits, avgEHits] = findCircle(wallHit, modRadius, metric, printBool);
% metric = "score";
% [xCenterScore,zCenterScore,idxScore,maxPointsScore, noHitsScore, avgEScore] = findCircle(wallHit, modRadius, metric, printBool);
% 
% metric = "hits";
% scoreScore = maxPointsScore;
% drawCircle(wallHit, metric, xCenterHits, zCenterHits, noHitsHits, xCenterScore, zCenterScore, noHitsScore, scoreScore, offset, modRadius)




% figure('Renderer', 'painters', 'Position', [10 10 figSize(1) figSize(2)])
% pbaspect([1 1 1])
% imagesc(dir1,dir2,EGrid')
% set(gca,'YDir','normal')
% xlabel(xlabelString)
% ylabel(ylabelString)
% hcb = colorbar;
% colorTitleHandle = get(hcb,'title');
% a = get(gca,'XTickLabel');
% set(gca,'XTickLabel',a,'FontName','Times','fontsize',fontSize)
% %h=xlabel('$y$/cm') %or h=get(gca,'xlabel')
% set(h, 'FontSize', fontSize)
% 
% %h=ylabel('$z$/cm') %or h=get(gca,'xlabel')
% set(h, 'FontSize', fontSize)
% a = get(gca,'YTickLabel');
% set(gca,'YTickLabel',a,'FontName','Times','fontsize',fontSize)
% set(gca,'YDir','normal')
% set(colorTitleHandle ,'String','$\bar{E} / \textrm{MeV}$','Interpreter','Latex');
% titleHelpHelp = "$\bar{E} \textbf{ of positrons passing through }$" + noString + "$\textbf{ sample wall}$";
% titleHelp = {titleHelpHelp, "$\textbf{Total positrons: } $" + string(length(wallHit(1,:))), "$\textbf{Total average: }$" + string(avgE) + "$\textbf{MeV}$"};
% %title(titleHelp,'FontSize',14)
% saveDir = saveDirStart + saveName + string(wallNo) + "E" +  saveDirEnd;
% saveas(gcf,saveDir);
%------------------------------------------------------------------------------------------------------------------------------------------------------------%
%
%
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
%
% figure
% imagesc(dir1,dir2,distGrid')
% set(gca,'YDir','normal')
% xlabel(xlabelString)
% ylabel(ylabelString)
% hcb = colorbar;
% colorTitleHandle = get(hcb,'title');
% set(colorTitleHandle ,'String','$\bar{d} / \textrm{cm}$','Interpreter','Latex');
% %set(gca,'ColorScale','log')
% titleHelp = {"$\textbf{Average distance of annihilation location}$", "$\textbf{to moderator surface}$", "$\textbf{Total hits: } $" + ...
%     string(length(wallHit(1,:)))};
% title(titleHelp,'FontSize',14)
% saveDir = saveDirStart + saveName + "dist" +  saveDirEnd;
% saveas(gcf,saveDir);
%
printBool = true;
metric = "hits";
[xCenterHits,zCenterHits,idxHits,maxPointsHits, noHitsHits, avgEHits] = findCircle(wallHit, modRadius, metric, printBool);
% metric = "score";
% [xCenterScore,zCenterScore,idxScore,maxPointsScore, noHitsScore, avgEScore] = findCircle(wallHit, modRadius, metric, printBool);
%
% metric = "both";
% scoreScore = maxPointsScore;
% drawCircle(wallHit, metric, xCenterHits, zCenterHits, noHitsHits, xCenterScore, zCenterScore, noHitsScore, scoreScore, offset, modRadius)
%
%
% maxEnclosed = maxPointsHits;
%
ECircleHits = zeros(noHitsHits,1);
% ECircleScore = zeros(noHitsScore,1);
circleCount = 1;
for j=1:length(wallHit)
    if sqrt( (xCenterHits - wallHit(1,j))^2 + (zCenterHits - wallHit(3,j))^2 ) <= modRadius
        ECircleHits(circleCount) = wallHit(4,j);
        circleCount = circleCount + 1;
    end
end
%
% circleCount = 1;
% for j=1:length(wallHit)
%     if sqrt( (xCenterScore - wallHit(1,j))^2 + (zCenterScore - wallHit(3,j))^2 ) <= modRadius
%         ECircleScore(circleCount) = wallHit(4,j);
%         circleCount = circleCount + 1;
%     end
% end
%
edges = logspace(-2,1,50);
histHits = histcounts(ECircleHits,edges);
% histScore = histcounts(ECircleScore,edges);
%
%
%
%
figure
barWidth = 1.3;
bar(log10(edges(1:end-1)),histHits'); % plot only optimal hits circle
%bar(log10(edges(1:end-1)),[histHits;histScore]','BarWidth', barWidth); %
%plot optimal hits and optimal score circle
set(gca,'Xtick',-2:1); %// adjust manually; values in log scale
set(gca,'Xticklabel',10.^get(gca,'Xtick')); %// use labels with linear values
grid on
xlabel('$E / \textrm{MeV}$')
ylabel('$\textrm{No}$')
hLegend = findobj(gcf, 'Type', 'Legend');
set(hLegend,'FontSize', fontSizeLegend)
hAxis = findobj(gcf,'Type','Axes')
set(hAxis,'FontSize', fontSizeAxes)
% legend('$\textrm{Optimal circle hits}$','$\textrm{Optimal circle score}$','Location','Northwest')
% % titleHelp = {"$\textbf{Energy distribution}$", "$\textbf{inside optimal hits circle}$",...
% %     "$\textbf{Hits in max hits circle: }$" + string(sum(histHits)) + "$\textbf{ with } \bar{E} = $" + string(round(1000*avgEHits)/1000) + "$\textbf{ MeV}$", ...
% % };
% titleHelp = {"$\textbf{Comparison between energy distribution}$", "$\textbf{inside optimal hits and optimal score circle}$",...
%     "$\textbf{Hits in max hits circle: }$" + string(sum(histHits)) + "$\textbf{ with } \bar{E} = $" + string(round(1000*avgEHits)/1000) + "$\textbf{ MeV}$", ...
%     "$\textbf{Hits in max score circle: }$" + string(sum(histScore)) + "$\textbf{ with } \bar{E} = $" + string(round(1000*avgEScore)/1000) + "$\textbf{ MeV}$"
% };
% title(titleHelp)

%end % if fourth wall

end % plotWall