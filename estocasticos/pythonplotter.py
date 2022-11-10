import matplotlib.pyplot as plt
import random as rd
import pandas as pd
import numpy as np



# plot the data in data/exp.txt

#plot the data
# plt.hist(pd.read_csv('data/exp.txt', sep='\t', header=None).values, bins=100, rwidth=0.7, density=True)
# #using rd
# plt.hist([rd.expovariate(1) for i in range(1000)], bins=100, rwidth=0.7, density=True)
# plt.show()

# plot data in data/gamma.txt

#using rd
# MATLABvalues=pd.read_csv('data/expMATLAB.csv', sep=',', header=None).values[0:10]
# print(MATLABvalues[0])
# plt.hist(MATLABvalues[0], bins=100, rwidth=0.9, density=True)
# plt.show()

# plt.hist(pd.read_csv('data/exp.txt', sep='\t', header=None).values, bins=100, rwidth=0.9, density=True,color='red')
# plt.show()

# make scatter plot of data/repoio.txt
data=pd.read_csv('data/puntos_repoio.csv', header=None)
print(data.head().values)
# make a gif showing the point movement





