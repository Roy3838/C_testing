import numpy as np
from scipy.optimize import differential_evolution

n = 9

def f(x):
    # Define la función a minimizar
    sum = 0
    for i in range(0, n-1):
        sum += 100 * (x[i+1] - x[i]**2)**2 + (1 - x[i])**2
    return sum

# Define los límites para los valores de x y y
bounds = [(-10, 10)] * n

# Encuentra los valores que minimizan la función utilizando un algoritmo genético
res = differential_evolution(f, bounds)

# Imprime los resultados
print(res.x)