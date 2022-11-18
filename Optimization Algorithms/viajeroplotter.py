import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

def makescatter(valores):
    c=len(valores)
    plt.scatter(valores[:,0],valores[:,1])
    distance=np.linalg.norm(valores[0]-valores[-1])
    plt.arrow(valores[0][0],valores[0][1],valores[-1][0]-valores[0][0],valores[-1][1]-valores[0][1],
    head_width=0.05, head_length=0.1, fc='b', ec='b')
    for i in range(c-1):
        distance+=np.linalg.norm(valores[i]-valores[i+1])
        plt.arrow(valores[i][0],valores[i][1],valores[i+1][0]-valores[i][0],valores[i+1][1]-valores[i][1],
        head_width=0.05, head_length=0.1, fc='b', ec='b')
    plt.text(-2,2.3,'Distance: '+str(distance))
    plt.show()


""" DATA BEFORE OPTIMIZATION"""
valores=pd.read_csv('data/ps.csv', sep=',', header=None)

makescatter(valores.values)

""" DATA AFTER OPTIMIZATION"""
valores2=pd.read_csv('data/ps2.csv', sep=',', header=None)

makescatter(valores2.values)

