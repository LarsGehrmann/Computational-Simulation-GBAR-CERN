% Task3, starting with sampling of positrons

clear all, clc, close all;

modRadius = 2.5; % cm
L_plus = 1*10^(-4); % cm diffusion length of solid neon
%L_plus = 130*10^(-7); % cm diffusion length of solid neon

%sample();
%plot_scaleB();
%plot_distTargetOrigin();
%plot_Annihis();
%showPosTableHisto()
plot_sampleWalls(modRadius)
plot_sampleWallsScore(modRadius, L_plus);
%plot_Sample4distTargetOrigin()
%plot_Sample4ModeratorHeight()
%plot_Sample4Fields()
%plot_scaleBTargetHits()
%plot_scaleBDipoleHits()
%plot_scaleBNeonHits()
%plot_ratioTargetNeon()
%plot_ratioTargetDipole()
%plot_ratioDipoleNeon()
