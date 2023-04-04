% Compute the total number of electrons per second of the LINAC

Tbunch = 3*10^(-6); % [s] time period of a bunch
I = 0.3; % [Q/s] current during a bunch
f = 300; % [1/s] frequency
noBunch = Tbunch * I / (1.602*10^(-19)) % [1] no electrons per bunch
noSecond = noBunch * f % [1/s] no of electrons per second