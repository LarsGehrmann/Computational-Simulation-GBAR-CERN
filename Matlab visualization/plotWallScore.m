function plotWallScore(annihis,nBins,offset, saveDirStart, saveName, saveDirEnd, modRadius, L_plus)

nBins = [nBins,nBins];
annihiCount = zeros(nBins(1),nBins(1));
ScoreGrid = zeros(nBins(1),nBins(1));
distGrid = zeros(nBins(1),nBins(1));
step = 2*offset / (nBins(1));

for k = 1:length(annihis)
    i = 1 + floor((annihis(k,1)+offset)/step);
    j = 1 + floor((annihis(k,3)+offset)/step);
    annihiCount(i,j) = annihiCount(i,j) + 1;
    distGrid(i,j) = distGrid(i,j) + annihis(k,2) - 60;
    ScoreGrid(i,j) = ScoreGrid(i,j) + annihis(k,4);
end
for i=1:nBins
    for j =1:nBins
        if annihiCount(i,j) ~= 0
            distGrid(i,j) = distGrid(i,j) / annihiCount(i,j);
        end
    end
end

dir1 = [-offset offset];
dir2 = [-offset offset];
xlabelString = '$x / \textrm{cm}$';
ylabelString = '$z / \textrm{cm}$';


figure
imagesc(dir1,dir2,annihiCount')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$N \textrm{ hits}$','Interpreter','Latex');
titleHelpHelp = "$\textbf{Annihilations in moderator}$";
titleHelp = {titleHelpHelp, "$\textbf{Total annihilations: } $" + string(length(annihis(:,1)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + saveDirEnd;
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
titleHelp = {"$\textbf{Average distance of annihilation location}$", "$\textbf{to moderator surface}$", "$\textbf{Total annihilations: } $" + ...
    string(length(annihis(:,1)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + "dist" +  saveDirEnd;
saveas(gcf,saveDir);


figure
imagesc(dir1,dir2,ScoreGrid')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\textrm{Score}$','Interpreter','Latex');
set(gca,'ColorScale','log')
titleHelp = {"$\textbf{Score}$", "$\textbf{Total annihilations: } $" + string(length(annihis(:,1)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + "Score" +  saveDirEnd;
saveas(gcf,saveDir);

maxIdx = 1;
scoreEncircled = zeros(length(annihis),1);
for i=1:length(annihis)
    xMid = annihis(i,1);
    zMid = annihis(i,3);
    for j=1:length(annihis)
        if sqrt( (xMid - annihis(j,1))^2 + (zMid - annihis(j,3))^2) <= modRadius
            scoreEncircled(i) = scoreEncircled(i) + annihis(j,4);
        end
    end
end
[maxScore,maxIDX] = max(scoreEncircled);
xCenter = annihis(maxIDX,1);
zCenter = annihis(maxIDX,3);
fprintf("'Optimal' circle with radius r=" + string(modRadius) + "cm and midpoint:\n")
fprintf("x: " + string(xCenter) + "cm\n")
fprintf("z: " + string(zCenter) + "cm\n")
fprintf("Score in that circle: " + string(scoreEncircled(maxIDX)) + "\n")

figure
plot(annihis(:,1), annihis(:,3), 'k.','MarkerSize', 5)
xlim([-offset,offset])
hold on
grid on
th = linspace(0,2*pi,1000);
xCircle = modRadius * cos(th) + xCenter;
zCircle = modRadius * sin(th) + zCenter;
plot(xCircle,zCircle,'r')
axis equal
xlabel(xlabelString)
ylabel(ylabelString)
titleHelp = {"$\textbf{Annihilations in moderator with 'optimal' circle based on score}$", "$\textbf{with radius: } r = $" + ...
    string(modRadius) + " $\textbf{cm and center: }c = \textbf{(}$" + string(xCenter) + "$,$" + ...
    string(zCenter) + "$\textbf{)cm}$", "$\textbf{Total score inside circle: }$" + string(maxScore)};
title(titleHelp)


end % plotWall