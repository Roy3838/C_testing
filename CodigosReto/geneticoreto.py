
from pathlib import Path
from geneticalgorithm import geneticalgorithm as ga
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

ROOT_DIR = Path(__file__).parents[2]

dataSIR = pd.read_csv(ROOT_DIR/ "c_aber" / "Data.csv")
dataSIR = dataSIR.to_numpy()
S_data = dataSIR[:,0]
I_data = dataSIR[:,1]
R_data = dataSIR[:,2]

# SIR funtion
def f(x):
    beta = x[0]
    gamma = x[1]
    sum = 0
    for i in range(99):
        sum += (S_data[i] - (S_data[i-1] - beta*S_data[i-1]*I_data[i-1]))**2 + (
            I_data[i] - (I_data[i-1] + beta*S_data[i-1]*I_data[i-1] - gamma*I_data[i-1]))**2 + (
                R_data[i] - (R_data[i-1] + gamma*I_data[i-1]))**2
    return sum
    
# ALGORITMOS GENETICOS
model=ga(function=f,dimension=2,variable_type='real',variable_boundaries=np.array([[0,1]]*2))
model.run()
coso = model.output_dict
variable = coso['variable']
r0 = 100*variable[0]/variable[1]
print('r0 :' , r0)

