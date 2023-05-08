% points is metric according to which best metric is found "hits"/"score"
function [xCenter,zCenter,idx,maxPoints,noHits, avgE] = findCircle(wallHit, modRadius, metric, printBool)
pointsEncircled = zeros(length(wallHit),1);
hitsEncircled = zeros(length(wallHit),1);
avgEVec = zeros(length(wallHit),1);
for i=1:length(wallHit)
    xMid = wallHit(1,i);
    zMid = wallHit(3,i);
    for j=1:length(wallHit)
        if sqrt( (xMid - wallHit(1,j))^2 + (zMid - wallHit(3,j))^2 ) <= modRadius
            if metric == "hits"
                pointsEncircled(i) = pointsEncircled(i) + 1;
                hitsEncircled(i) = hitsEncircled(i) + 1; 
                avgEVec(i) = avgEVec(i) + wallHit(4,j);
            elseif  metric == "score"
                pointsEncircled(i) = pointsEncircled(i) + wallHit(5,j);
                hitsEncircled(i) = hitsEncircled(i) + 1;
                avgEVec(i) = avgEVec(i) + wallHit(4,j);
            else
                err("No valid metric chosen!")
            end
        end
    end
end

[maxPoints,idx] = max(pointsEncircled);
xCenter = wallHit(1,idx);
zCenter = wallHit(3,idx);
noHits = hitsEncircled(idx);
avgE = avgEVec(idx) / noHits;


if printBool
    if metric == "hits"
        fprintf("'Optimal' circle hits with radius r=" + string(modRadius) + "cm and midpoint:\n")
        fprintf("x: " + string(xCenter) + "cm\n")
        fprintf("z: " + string(zCenter) + "cm\n")
        fprintf("Number of registered hits in that circle: " + string(noHits) + "\n")
    elseif metric == "score"
        fprintf("\n'Optimal' circle score with radius r=" + string(modRadius) + "cm and midpoint:\n")
        fprintf("x: " + string(xCenter) + "cm\n")
        fprintf("z: " + string(zCenter) + "cm\n")
        fprintf("Score inside this circle: " + string(pointsEncircled(idx)) + "\n")
        fprintf("Number of registered hits in that circle: " + string(noHits) + "\n")
    else
        err("No valid metric chosen!")
    end
end
end
