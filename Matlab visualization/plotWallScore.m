function plotWallScore(annihis,nBins,offset, saveDirStart, saveName, saveDirEnd, modRadius, L_plus)

% read moderator height;
dir = "\\wsl.localhost\Ubuntu\home\lars\Geant4\Task3\build\StandardParameters0_nt_Parameters.csv";
M = dlmread(dir, ',', 14, 0);
modHeight = M(1,5) / 10; %% mm->cm

nBins = [nBins,nBins];
annihiCount = zeros(nBins(1),nBins(1));
ScoreGrid = zeros(nBins(1),nBins(1));
step = 2*offset / (nBins(1));
for k = 1:length(annihis)
    i = 1 + floor((annihis(k,1)+offset)/step);
    j = 1 + floor((annihis(k,3)+offset)/step);
    annihiCount(i,j) = annihiCount(i,j) + 1;
    dist = annihis(k,2) - modHeight;
    ScoreGrid(i,j) = ScoreGrid(i,j) + score(dist,L_plus);
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
imagesc(dir1,dir2,ScoreGrid')
set(gca,'YDir','normal')
xlabel(xlabelString)
ylabel(ylabelString)
hcb = colorbar;
colorTitleHandle = get(hcb,'title');
set(colorTitleHandle ,'String','$\textrm{Score}$','Interpreter','Latex');
titleHelp = {"$\textbf{Score}$", "$\textbf{Total positrons: } $" + string(length(annihis(:,1)))};
title(titleHelp,'FontSize',14)
saveDir = saveDirStart + saveName + "Score" +  saveDirEnd;
saveas(gcf,saveDir);

% maxIdx = 1;
% noEncircled = zeros(length(annihis),1);
% countEncircled = 0;
% if wallNo == 4
%     for i=1:length(annihis)
%         countEncircled = 0;
%         xMid = annihis(1,i);
%         zMid = annihis(3,i);
%         for j=1:length(annihis)
%             if sqrt( (xMid - annihis(1,j))^2 + (zMid - annihis(3,j))^2) <= modRadius
%                 countEncircled = countEncircled + 1;
%             end
%         end
%         noEncircled(i) = countEncircled;
%     end
%     [maxEnclosed,maxIDX] = max(noEncircled);
%     xCenter = annihis(1,maxIDX);
%     zCenter = annihis(3,maxIDX);
%     fprintf("'Optimal' circle with radius r=" + string(modRadius) + "cm and midpoint:\n")
%     fprintf("x: " + string(xCenter) + "cm\n")
%     fprintf("z: " + string(zCenter) + "cm\n")
%     fprintf("Number of registered hits in that circle: " + string(noEncircled(maxIDX)) + "\n")
%
%     figure
%     plot(annihis(1,:), annihis(3,:), 'k.','MarkerSize', 5)
%     hold on
%     grid on
%     th = linspace(0,2*pi,1000);
%     xCircle = modRadius * cos(th) + xCenter;
%     zCircle = modRadius * sin(th) + zCenter;
%     plot(xCircle,zCircle,'r')
%     xlim([-offset,offset])
%     axis equal
%     xlabel(xlabelString)
%     ylabel(ylabelString)
%     titleHelp = {"$\textbf{Hits on fourth sample wall with 'optimal' circle}$", "$\textbf{with radius: } r = $" + string(modRadius) + " $\textbf{cm and center: }c = \textbf{(}$" + string(xCenter) + "$,$" + string(zCenter) + "$\textbf{)cm}$", "$\textbf{Total hits inside circle: }$" + string(maxEnclosed)};
%     title(titleHelp)
%
%     ECircle = zeros(maxEnclosed,1);
%     circleCount = 1;
%     for i=1:length(annihis)
%         if sqrt( (xCenter - annihis(1,i))^2 + (zCenter - annihis(3,i))^2 ) <= modRadius
%             ECircle(circleCount) = annihis(4,i);
%             circleCount = circleCount + 1;
%         end
%     end
%     ECircleAvg = round(1000*sum(ECircle) / maxEnclosed) / 1000;
%     fprintf("Average energy inside circle: " + string(ECircleAvg) + "MeV\n");
%     edges = logspace(-2,1,50);
%     figure
%     hist(ECircle, edges)
%     set(gca,'xscale','log')
%     xlim([10^-2,10])
%     grid on
%     titleHelp = {"$\textbf{Kinetic energy of positrons in 'optimal' circle}$", "$\textbf{Number of hits in circle: }$" + string(maxEnclosed) + "$\textbf{; } \bar{E} \textbf{ inside circle: }$" + string(ECircleAvg) + "$\textbf{MeV}$"};
%     title(titleHelp)
%     xlabel('$E / \textrm{MeV}$')
%     ylabel('$\textrm{No}$')
% end % if fourth wall

end % plotWall