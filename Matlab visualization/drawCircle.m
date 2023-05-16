function drawCircle(wallHit, metric, xCenterHits, zCenterHits, noHitsHits, xCenterScore, zCenterScore, noHitsScore, scoreScore, offset, modRadius)

xlabelString = '$x / \textrm{cm}$';
ylabelString = '$z / \textrm{cm}$';
th = linspace(0,2*pi,1000);
if metric == "hits"
    xCircleHits = modRadius * cos(th) + xCenterHits;
    zCircleHits = modRadius * sin(th) + zCenterHits;
    plot(xCircleHits,zCircleHits,'r')
    xlim([-offset,offset])
    xlabel(xlabelString)
    ylabel(ylabelString)
    axis equal
    titleHelp = {"$\textbf{Hits on fourth sample wall with circle radius: } r = $" + string(modRadius) + "$\textbf{ cm}$",
        "$\textbf{Center of maximum hits circle: (}$" + string(round(100*xCenterHits) / 100) + "$\textbf{,}$" + string(round(100*zCenterHits) / 100) + ...
        "$\textbf{)cm with }$" + string(noHitsHits) + "$\textbf{ hits}$"};
    title(titleHelp)
elseif metric == "score"
    xCircleScore = modRadius * cos(th) + xCenterScore;
    zCircleScore = modRadius * sin(th) + zCenterScore;
    plot(xCircleScore,zCircleScore,'r')
    xlim([-offset,offset])
    xlabel(xlabelString)
    ylabel(ylabelString)
    axis equal
    titleHelp = {"$\textbf{Hits on fourth sample wall with circle radius: } r = $" + string(modRadius) + "$\textbf{ cm}$",
        "$\textbf{Center of maximum score circle: (}$" + string(round(100*xCenterScore) / 100) + "$\textbf{,}$" + string(round(100*xCenterScore) / 100) + ...
        "$\textbf{)cm with }$" + string(noHitsScore) + "$\textbf{ hits}$",
        "$\textbf{Score of max score circle: }$" + string(round(100*scoreScore)/100)};
    title(titleHelp);
else metric == "both"
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
    xlabel(xlabelString)
    ylabel(ylabelString)
    axis equal
    xlabel(xlabelString)
    ylabel(ylabelString)
    titleHelp = {"$\textbf{Hits on fourth sample wall with circle radius: } r = $" + string(modRadius) + "$\textbf{ cm}$",
        "$\textbf{Center of maximum hits circle: (}$" + string(round(100*xCenterHits) / 100) + "$\textbf{,}$" + string(round(100*zCenterHits) / 100) + ...
        "$\textbf{)cm with }$" + string(noHitsHits) + "$\textbf{ hits}$",
        "$\textbf{Center of maximum score circle: (}$" + string(round(100*xCenterScore) / 100) + "$\textbf{,}$" + string(round(100*xCenterScore) / 100) + ...
        "$\textbf{)cm with }$" + string(noHitsScore) + "$\textbf{ hits}$",
        "$\textbf{Score of max score circle: }$" + string(round(100*scoreScore)/100)
        };

    title(titleHelp)
end


end % function