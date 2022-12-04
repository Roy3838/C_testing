from math import log
from numpy import prod
import numpy as np
from scipy.optimize import minimize
from scipy.optimize import differential_evolution

def minimize_function(x):
    return sum([np.log((x[i]-2)**2) + np.log((10-x[i])**2) for i in range(10)]) - (np.prod(x)**0.2)


def func(x,y):
    j0=1
    return j0(x**2 + y**2) + 0.1 * abs(1 - x) + 0.1 * abs(1 - y)

# minimize func

