clear

global t0 a L tf
a = 0.875;
tf = 1e-5;
L = 1000;

% funcion de costo
f = @(x) -3*x(:,1) + (x(:,2) + 4).^2;
% funcion de restriccion
fr = @(x) x(:,1).^2 < 10;

% valores iniciales aleatorios
x0 = rand(1,2);
t0 = 0.5*f(x0); % temp inicial
disp('empezando recocido...')
tic
xf = recoc(x0, f, fr);
t1 = toc;
fprintf('recocido acabado en %d s\n', t1)

% ---------- funcion ----------

function xbest = recoc(x0, f, fr)
  global t0; global a; global L; global tf
  xbest = x0;
  t = t0;
  while t >= tf
    for i = 1:L
      % encontrar vecino
      xv = random('Normal', 0, 1, size(x0)) + x0;
      % calcular costo
      d = f(xv) - f(x0);
      % ver si se escoge (si cumple con restriccion)
      p = rand;
      if ((p < exp(-d/t)) || d < 0) && fr(xv)
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

