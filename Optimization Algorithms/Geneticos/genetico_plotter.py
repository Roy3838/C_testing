import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.animation import FuncAnimation
import random


def f(x):
    return (x + x**2)*np.cos(x)



    
valores=pd.read_csv('/home/jay/c_aber/Optimization Algorithms/data/mijo_lalo.csv', sep=',', header=None)
# get values in range only from -10 to 10
valores = valores[(valores[:] > -10) & (valores[:] < 10)]
valores = valores.fillna(0)
valores = valores.values
# turn valores into straight list
valores = valores.tolist()
valoresy = f(valores)

print(valores)

#print(valores)
#make histogram from values

def animate(i, valores, valoresy):
    plt.cla()
    plt.scatter(valores[i], valoresy[i], color='red')

fig = plt.figure()
plt.plot(np.linspace(-10,10,1000),f(np.linspace(-10,10,1000)), color='blue', alpha=0.4)
ani = FuncAnimation(fig, animate, interval=700)
plt.show()


# plt.scatter(valores, valoresy, color='red')
# plt.show()

# plt.scatter(valores[0],valores[1])
# plt.show()

