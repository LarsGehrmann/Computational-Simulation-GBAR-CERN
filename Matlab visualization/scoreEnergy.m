function [sc,dist] = scoreEnergy(E,frontLength)

C = [1.597969595942218   1.057824226241920];
dist = exp(C(2))*E^C(1);
% sc = exp(-dist/L);

switch frontLength
    case 15
        if E < 0.03
            sc = 1;
        else
            C = [-2.117682728595330, 3.418870148139924];
            sc = exp(C(2)) * E^C(1);
            sc = sc / 10^5;
        end
    case 100
        if E < 0.07
            sc = 1;
        else
            C = [-1.858544557901239, 6.294299828938515];
            sc = exp(C(2)) * E^C(1);
            sc = sc / 10^5;
        end
    case 200
        if E < 0.11
            sc = 1;
        else
            C = [-1.943775922001810,  7.054883008624326];
            sc = exp(C(2)) * E^C(1);
            sc = sc / 10^5;
        end
    case 500
        if E < 0.2
            sc = 1;
        else
            C = [-1.993070142894966,  8.249588284150995];
            sc = exp(C(2)) * E^C(1);
            sc = sc / 10^5;
        end
    case 14000
        if E < 2
            sc = 1;
        else
            C = [ -2.570747667315423,  13.431409899766923];
            sc = exp(C(2)) * E^C(1);
            sc = sc / 10^5;
        end
end
C = [1.597969595942218   1.057824226241920];
dist = exp(C(2))*E^C(1);
end