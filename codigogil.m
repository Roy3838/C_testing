%% Segundo caso
clear; close all; clc

%Número de eventos
N = 100000000;

%eventos posibles (truncado hasya 2^20) y respectivas probabilidades
pVal = 2.^(1:20);
probVal = 0.5.^(1:20);

%Bacterias obtenidas en cada evento
vec = randsample(pVal,N,true,probVal);

%Acumulada de las bacterias
acum = cumsum(vec);

%Bins para el histograma
%C = categorical(vec,pVal,{'yes','no','undecided'})
nbins = 20;

figure(1)
plot(1:N,acum)

r1vec = find(vec==2);
r1 = length(r1vec);
fr1 = zeros(1,r1);
for ii = 1:length(fr1)
        fr1(ii) = ii/r1vec(ii);
end
figure(3)
plot(fr1)

bpi = zeros(1,N);
for ii = 1:N
        bpi(ii) = sum(vec(1:ii))/ii;
end
figure(4)
plot(bpi)