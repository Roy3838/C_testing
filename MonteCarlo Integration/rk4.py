import matplotlib.pyplot as plt
import numpy as np

def runge_kutta_4(x0,y0,xn,n,f):
    h = (xn-x0)/n
    ym=y0
    xm=x0
    for m in range(n):
        k1 = h * (f(xm))
        k2 = h * (f(xm+h/2))
        k3 = h * (f(xm+h/2))
        k4 = h * (f(xm+h))
        ym = ym + (k1+2*k2+2*k3+k4)/6
        xm = xm+h
    
    return ym

def f(x): # funcion a integrar
    return x**2

xi = -2
xf =  2
yi = xi**3/3 # nota es la integral de x^2 para que se alinee en el 0
n = 1000
x = np.linspace(xi,xf,n) # vector de x de [xi, ... , xf] con 1000 puntos


y = runge_kutta_4(xi,yi,x,n,f) # regresa el valor de la integral [yi, ... , yf]

plt.plot(x, f(x), label='f(x)')
plt.plot(x, y,    label='rk4' )
plt.show()
