function [X,Y,sigma] = myAvg(xVec, yVec)

X = [min(xVec), max(xVec)];
Y = [mean(yVec), mean(yVec)];
sigma = std(yVec);

end