import numpy as np
import matplotlib.pyplot as plt


# monte carlo simple
def montecarlo_simple(func, a, b, n):
    x = np.random.uniform(a, b, n)
    y = func(x)
    return (b - a) * np.mean(y)

# funcion a integrar
def f_x(x):
    return np.sqrt(1 - np.exp(-x**2))

# llamar metodo
resultado=[]
for i in range(100):
    tf = np.sqrt(2)*2
    n=i/100
    resultado.append( montecarlo_simple(f_x, 0, n*tf, 1000))

dominio=np.linspace(0,tf,100)

plt.plot(dominio,resultado)
plt.show()

