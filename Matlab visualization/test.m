clc; clear all; close all

A = rand(1,10);
B = rand(1,15);
C = rand(1,20);
D = rand(1,30);


plotMatrix =[];

figure
hold on
yyaxis left
plotMatrix(1) = plot(A);
yyaxis right
plotMatrix(2) = plot(B);
yyaxis left
plotMatrix(3) = plot(C);
yyaxis right
plotMatrix(4) = plot(D);
hold off
legend(plotMatrix, 'A','B','C','D')