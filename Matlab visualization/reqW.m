function W = reqW(eDepeV)

ePerSecond = 1.7 * 10^15;
PeVs = ePerSecond * eDepeV;
W = PeVs * 1.602* 10^(-19);
end