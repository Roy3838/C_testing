import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.animation import FuncAnimation
import random

def sigmoid(x):
    return 1/(1 + np.exp(-x))

def f_x(x):
    return (1+np.cos(12*np.sqrt(pow(x,2))))/(0.5*(pow(x,2)) +2 )

    
valores=pd.read_csv('/home/jay/c_aber/data/mijo_lalo.csv', sep=',', header=None)
# get values in range only from -10 to 10
valores = valores.fillna(0)

#valores = valores[(valores[:] > -10) & (valores[:] < 10)]
print(valores)
# # turn valores into straight list
# valores = valores.tolist()

x=np.linspace(-10,10,300)
plt.plot(x,f_x(x),color='red')
plt.scatter(valores[0],f_x(valores[0]))
plt.scatter(valores[99],f_x(valores[99]))
plt.show()


from geneticalgorithm import geneticalgorithm as ga

def f(r):
    d=0
    return -(1+np.cos(12*np.sqrt(pow(r+d,2))))/(0.5*(pow(r+d,2)) +2 )

model=ga(function=f,dimension=1,variable_type='real',variable_boundaries=np.array([[0,10]]))
model.run()
