clc; clear all; close all

X = [-1 -5 3 6 -1 7];
Y = [-1 -6 3 6 -1 7];
[N,b] = hist3([X', Y'],[numel(X) numel(X)]); 
figure
imagesc(b{1}([1 end]),b{2}([1 end]),N);
colorbar
%axis xy equal tight