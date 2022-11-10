clear

rng(0);
doNormal = true;
doPlot = false;
doGridSearch = false;

% parametros para recocido
global t0 tf a L

% ----------  hacer con valores dados ---------

if doNormal

tf = 1e-6;
a = 0.875;
L = 10000;

% cantidad de ciudades
nc = 14;

% crear matriz con coordenadas de ciudades
% cada hilera es una ciudad
cc = rand(nc, 2) * 100;

% orden aleatorio
o = randperm(nc);
d0 = distancia(o,cc)

% definir temp inicial
t0 = 0.5*d0;

% hacer recocido
newo1 = recoc(o,cc);
distancia(newo1,cc)
newo2 = recoc(newo1,cc);
distancia(newo2,cc)
newo3 = recoc(newo2,cc);
distancia(newo3,cc)
newo4 = recoc(newo3,cc);
distancia(newo4,cc)

end

% ----------  grid search ---------

if doGridSearch

% cantidad de ciudades
nc = 200;

% grids de parametros
np = 5; % cantidad de parametros
coefs = linspace(0.1, 1, np);
tfs = logspace(-20, -1, np);
as = linspace(0.85, 0.9, np);
Ls = logspace(1, 4, np);

% cantidad de repeticiones para cada combinacion
nr = 5;

% matriz para almacenar resultados de distancias obtenidas 
% dimensiones son coefs, tfs, as, Ls
res = zeros(np, np, np, np);

% iterar sobre coeficientes
tic
for ic = 1:np
  coef = coefs(ic);
  % iterar sobre tfs
  for it = 1:np
    tf = tfs(it);
    % iterar sobre as
    for ia = 1:np
      a = as(ia);
      % iterar sobre Ls
      for il = 1:np
        L = Ls(il);
        % repetir calculo
        for i = 1:nr
          % coordenadas
          cc = rand(nc,2) * 100;
          % valor inicial para orden
          o = randperm(nc);
          % distancia con orden inicial
          d = distancia(o,cc);
          % definir temp inicial
          t0 = coef * d;
          % mejorar orden
          newo = recoc(o,cc);
          % almacenar distancia
          res(ic, it, ia, il) = distancia(o,cc);
        end
      end
    end
  end
  fprintf('done with ic %i\n', ic)
end
toc

% encontrar minimo en resultados
[mind, minidx] = min(res, [], 'all', 'linear');
[mic, mit, mia, mil] = ind2sub(size(res), minidx);

disp('mejores parametros:')
fprintf('coef para t0: %e\n', coefs(mic))
fprintf('tf: %e\n', tfs(mit))
fprintf('a: %e\n', as(mia))
fprintf('L: %e\n', Ls(mil))

end

% ----------  graficar ---------

if doPlot
figure(1)
  clf
  plot(cc(newo,1), cc(newo,2), '.-', 'color', 'red')
  hold on
  plot([cc(newo(end),1), cc(newo(1),1)], [cc(newo(end),2), cc(newo(1),2)], '.-', 'color', 'red')
  hold off
end

% ---------- funciones ----------

% funcion para calcular distancia total de ruta
function d = distancia(orden, cc)
  % distancia desde primera ciudad hasta llegar a la ultima
  % luego distancia de la ultima a la primera
  d = sum(vecnorm(cc(orden(2:end),:) - cc(orden(1:end-1),:), 2, 2)) ...
      + vecnorm(cc(orden(1),:) - cc(orden(end), :), 2, 2);
end

% funcion para intercambiar elementos
function nuevo = intercambiar(arreglo)
  idx = round(rand * (length(arreglo)-1)) + 1;
  nuevo = arreglo;
  if idx == length(arreglo)
    nuevo([1 length(arreglo)]) = arreglo([length(arreglo) 1]);
  else
    nuevo([idx idx+1]) = arreglo([idx+1 idx]);
  end
end

function best = recoc(o, cc)
  global t0; global tf; global a; global L;
  % valor inicial de temperatura
  t = t0;
  % distancia con orden inicial
  d0 = distancia(o, cc);
  % mejor hasta ahora
  best = o;
  bestd = d0;
  while t > tf
    for i = 1:L
      % pseudovecino
      newo = intercambiar(o);
      % calcular costo
      d = distancia(newo, cc);
      % ver si se escoge
      p = rand;
      if d < d0 || (p < exp(-0.001*d/t))
        % nuevo orden
        o = newo; 
        d0 = d;
        % comparar con el mejor
        if d0 < bestd
          best = o;
          bestd = d0;
        end
      end
    end
    % enfriar
    t = a*t;
  end
end

%function d = distanciaLenta(orden, cc)
%  d = 0;
%  % de la primera ciudad a la ultima
%  for i = 2:length(orden)
%    d = d + vecnorm(cc(orden(i),:) - cc(orden(i-1),:), 2, 2);
%  end
%  % de la ultima a la primera
%  d = d + vecnorm(cc(orden(1),:) - cc(orden(end),:), 2, 2);
%end

