function [X,Y,r2] = myLinReg(xVec, yVec)

C = polyfit(xVec,yVec,1);
X = [min(xVec), max(xVec)];
Y = [min(xVec)*C(1) + C(2), max(xVec)*C(1) + C(2)];

linearCoefficients = polyfit(xVec, yVec, 1);          % Coefficients
yfit = polyval(linearCoefficients, xVec);          % Estimated  Regression Line
SStot = sum((yVec-mean(yVec)).^2);                    % Total Sum-Of-Squares
SSres = sum((yVec-yfit).^2);                       % Residual Sum-Of-Squares
r2 = 1-SSres/SStot;                            % R^2

end