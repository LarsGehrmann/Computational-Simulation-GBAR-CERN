% Estimates regarding the heating with Stefan-Boltzmann law

clear all; close all; clc


sigma = 5.67 * 10^(-8); % [W/(m^2*K^4)]
ATarget = 2 * pi * (2.5*10^(-3))^2; % [m^2]
T = 300;   % [K]
Ptotal = sigma * ATarget * T^4
