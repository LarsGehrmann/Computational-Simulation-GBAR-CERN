clc; clear all; close all



minE = 0.01;
maxE = 2;
n = 50;
frontLength = 15;
E = linspace(minE, maxE,n);
scVec = zeros(1,n);
for i=1:n
    [sc,dist] = scoreEnergy(E(i),frontLength);
    scVec(i) = sc;
end
plot(E,scVec,'kX')
