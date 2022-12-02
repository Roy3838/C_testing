
from geneticalgorithm import geneticalgorithm as ga
import numpy as np

C = [0.1,0.2,0.2,0.4,0.4]
A = [[4,4,4,4],[1,1,1,1],[8,8,8,8],[6,6,6,6],[3,7,3,7]]

def f(x):
    sum = 0
    for i in range(1,len(x)):
        sum += 1/C[i]
        for j in range(1,4):
            sum += 1/((x[j]-A[j][i])**2)
    return -sum

# ALGORITMOS GENETICOS

model=ga(function=f,dimension=4,variable_type='real',variable_boundaries=np.array([[0,10]]*4))
model.run()

# RECOCIDO SIMULADO

from scipy import optimize

res = optimize.dual_annealing(f, np.array([[0,10]]*4))
print(res)