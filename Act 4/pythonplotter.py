import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from matplotlib.animation import FuncAnimation
import random

def f(x):
    return (x**2 + x)* np.cos(x)


def fb(x):
    term1 = (np.sin((np.power(x, x)) / (x + 1)) + np.power(x, 2) - np.sqrt(x))
    term2 = (x * np.cos((x + 1) / np.power(x, 2)) - np.power(x, x))
    return  term1/term2 




valores=pd.read_csv('/home/jay/c_aber/data/ej1a_lalo.csv', sep=',', header=None)
# get values in range only from -10 to 10
valores = valores.fillna(0)
valores = valores.values
# get last line
valores = valores[-1]
# turn valores into straight list
valores = valores.tolist()
print(valores)
# turn values into numbers
valores = [float(i) for i in valores]
# get values in range only from 0 to 1
valores = [x for x in valores if x >= -10 and x <= 10]
valoresy = np.zeros(len(valores))
for i in range(len(valores)):
    valoresy[i] = f(valores[i])



fig = plt.figure()
plt.plot(np.linspace(-10,10,1000),f(np.linspace(-10,10,1000)), color='blue', alpha=0.4)
plt.scatter(valores,valoresy, color='red')
plt.show()


# plt.scatter(valores, valoresy, color='red')
# plt.show()

# plt.scatter(valores[0],valores[1])
# plt.show()

