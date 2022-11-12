% recocido simulado y algoritmos geneticos

clear

rng(0);

hacerRecocido = true;
hacerAlgGen = true;
hacerMatlab = true;

% funcion
f2 = @(x,y)  - (1 + cos(12*sqrt(x.^2+y.^2))) ./ (0.5*(x.^2+y.^2) + 2);
f = @(x) f2(x(:,1),x(:,2));

% funcion de fitness
ff = @(x) exp(-f(x));

% ----- a) visualizar -----

% cantidad de puntos
n = 1000;

xmin = -5;
xmax = 10;
ymin = -10;
ymax = 5;

x = linspace(xmin, xmax, n);
y = linspace(ymin, ymax, n);
[X, Y] = meshgrid(x,y);

k = 1;
figure(k)
  k = k+1;
  imagesc(x,y,f2(X,Y))
  set(gca,'YDir','normal')
  colorbar
  axis square 

% ----- b) recocido -----

if hacerRecocido

% parametros para recocido
global a tf L
a = 0.9;
tf = 1e-7;
L = 2500;

% valores iniciales aleatorios
pdx = makedist('Uniform', xmin, xmax);
pdy = makedist('Uniform', ymin, ymax);
x0 = random(pdx, 1, 1);
y0 = random(pdy, 1, 1);

% temperatura inicial
global t0
t0 = 0.5*abs(f([x0 y0]));

tic
xf_rec = recoc([x0 y0], f)
t_rec = toc;
f(xf_rec)

end

% ----- c) algoritmo genetico -----

if hacerAlgGen

% parametros
global n_generations n_elite sig
sig = 0.5;
n_generations = 500;
n_individuals = 100;
n_elite = round(n_individuals*0.03);

% poblacion inicial
pdx = makedist('Uniform', xmin, xmax);
pdy = makedist('Uniform', ymin, ymax);
x0 = random(pdx, n_individuals, 1);
y0 = random(pdy, n_individuals, 1);

% hacer algoritmo genetico
tic
xf_alg = algGen([x0 y0], ff)
t_alg = toc;
f(xf_alg)

end

% ----- d) toolbox de matlab -----

if hacerMatlab

% recocido simulado

pdx = makedist('Uniform', xmin, xmax);
pdy = makedist('Uniform', ymin, ymax);
x0 = random(pdx, 1, 1);
y0 = random(pdy, 1, 1);

tic
xf_recm = simulannealbnd(f, [x0 y0], [xmin ymin], [xmax ymax])
t_recm = toc;
f(xf_recm)

% algoritmo genetico

options = optimoptions(@ga, ...
                       'MaxGenerations', 800, ...
                       'MaxStallGenerations', 200, ...
                       'PopulationSize', 500, ...
                       'FunctionTolerance', 1e-8, ...
                       'UseVectorized', true);

tic
xf_algm = ga(f, 2, [], [], [], [], [xmin ymin], [xmax ymax], [], options)
t_algm = toc;
f(xf_algm)

try
  fprintf('tiempo recocido simulado: %d\n', t_rec)
  fprintf('tiempo algoritmo genetico: %d\n', t_alg)
  fprintf('tiempo recocido simulado (matlab): %d\n', t_recm)
  fprintf('tiempo algoritmo genetico (matlab): %d\n', t_algm)
end

end

% ----- funciones -----

function xbest = recoc(x0, f)
  global t0; global a; global L; global tf
  xbest = x0;
  t = t0;
  while t >= tf
    for i = 1:L
      % encontrar vecino
      xv = random('Normal', 0, 1, size(x0)) + x0;
      % calcular costo
      d = f(xv) - f(x0);
      % ver si se escoge
      p = rand;
      if ((p < exp(-d/t)) || d < 0) && (xv(1) > -5) && (xv(2) < 5)
        % nuevo x actual
        x0 = xv;
        % ver si es mejor que mejor global
        if f(x0) < f(xbest)
          xbest = x0;
        end
      end
    end
    % enfriar T
    t = a*t;
  end
end

function xbest = algGen(x0, f)
  global n_generations; global n_elite;
  n_individuals = height(x0);
  % poblacion inicial
  x = x0;
  % fitness
  y = f(x);

  % mejores historicos
  xbest = x;
  ybest = y;

  for i = 1:n_generations
    % seleccionar padres (n_individuals para que 
    % produzcan n_individuals/2 hijos)
    prob = selection(x,y);
    parent_idx = datasample(1:n_individuals, ...
                            n_individuals, 'Weights', prob);
    idx1 = parent_idx(1:round(n_individuals/2));      % primera mitad
    idx2 = parent_idx(round(n_individuals/2)+1:end);  % segunda mitad

    % reproducir (hijos son la mitad de la nueva poblacion)
    offspring = crossover(x(idx1,:), x(idx2,:));
    % mutate
    mutated = mutation(offspring);

    % poblacion nueva
    [~, elite] = maxk(prob, n_elite);
    old_selected = datasample(1:n_individuals, ...
                              round(n_individuals/2 - n_elite), ...
                              'Weights', prob);
    x = vertcat(x(elite,:), x(old_selected,:), mutated);
    % fitness nuevo
    y = f(x);

    % comparar con los mejores
    [this_ybest, best] = max(y);
    if this_ybest > ybest
      ybest = this_ybest;
      xbest = x(best,:);
    end
  end
end

function prob = selection(x, y)
  % cantidad de individuos
  [n_ind, ~] = size(x);
  % probabilidad segun funcion fitness
  sumfi = sum(y); 
  if sumfi == 0
    prob = rand(n_ind,1);
  else
    prob = y./sumfi;
  end
  % darle probabilidad 0 a los que esten fuera
  % de los limites
  prob(x(:,1) < -5) = 0;
  prob(x(:,2) > 5) = 0;
end

function offspring = crossover(x1, x2)
  [n_ind, ~] = size(x1);
  % distribucion aleatoria uniforme
  pd = makedist('Uniform',0,1);
  % hacer coeficientes para combinaciones
  bet = random(pd, n_ind, 1);
  % hacer hijos
  offspring = bet.*x1 + (1-bet).*x2;
end

function x_mutated = mutation(x)
  global sig;
  [n_individuals, ~] = size(x);
  x_mutated = x + sig * randn(n_individuals, 1);
end

