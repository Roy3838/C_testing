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
resultado = montecarlo_simple(f_x, 0, np.sqrt(2)*2, 100000)

print(resultado)

