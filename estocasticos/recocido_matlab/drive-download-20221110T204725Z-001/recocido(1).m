% 17/08/2021
% recocido simple

clear
do2d = false;

% parametros
a = 0.875;
Tf = 1e-6;
L = 1000;

if do2d

% funcion 1
f1 = @(x,y) x.^2 + y.^2 + 25*(sin(x).^2 + sin(y).^2);
x01 = random('Normal', 0, 10);
y01 = random('Normal', 0, 10);
T01 = 0.5*f1(x01, y01);
disp('funcion evaluada en valores iniciales')
f1(x01,y01)
disp('resultados')
xo1 = recocidoSimple(f1, T01, a, L, Tf, [x01, y01])
disp('funcion evaluada en resultados')
f1(xo1(1), xo1(2))

% funcion 2
f2 = @(x,y) (1-x).^2 + 100*(y-x.^2).^2;
x02 = random('Normal', 0, 10);
y02 = random('Normal', 0, 10);
T02 = 0.5*f1(x02, y02);
disp('funcion evaluada en valores iniciales')
f1(x02,y02)
disp('resultados')
xo2 = recocidoSimple(f2, T02, a, L, Tf, [x02, y02])
disp('funcion evaluada en resultados')
f2(xo2(1), xo2(2))

% ver graficas
x = linspace(-100, 100, 100);
y = linspace(-100, 100, 100);
[X, Y] = meshgrid(x,y);
F1 = f1(X, Y);
F2 = f2(X, Y);

figure(1)
clf
surf(X, Y, F1)
hold on
plot3(xo1(1), xo1(2), f1(xo1(1), xo1(2)), '.', 'Color', 'r', 'MarkerSize', 10)
hold off

figure(2)
clf
surf(X, Y, F2)
hold on
plot3(xo2(1), xo2(2), f2(xo2(1), xo2(2)), '.', 'Color', 'r', 'MarkerSize', 10)
hold off

end

% ---------------------------

f3 = @(a,b,c,d) cosh((a-1).^2 + (b-2).^2 + (c+1).^2 + d.^2);
x03 = random('Normal', 0, 1, [1,4]);
x03args = num2cell(x03);
T03 = 0.5*f3(x03args{:});
disp('funcion evaluada en valores iniciales')
f3(x03args{:})
disp('resultados')
xo3 = recocidoSimple(f3, T03, a, L, Tf, x03)
xo3args = num2cell(xo3);
disp('funcion evaluada en resultados')
f3(xo3args{:})


function x0 = recocidoSimple(f, T0, a, L, Tf, x0)
  T = T0;
  x0args = num2cell(x0);
  while T >= Tf
    for i = 1:L
      % encontrar vecino
      xv = random('Normal', 0, 1, size(x0)) + x0;
      xvargs = num2cell(xv);
      % calcular costo
      d = f(xvargs{:}) - f(x0args{:});
      % ver si se escoge
      p = rand;
      if (p < exp(-d/T)) || d < 0
        % nuevo x actual
        x0 = xv;
        x0args = xvargs;
      end
    end
    % enfriar T
    T = a*T;
  end
end

