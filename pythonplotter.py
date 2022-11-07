import matplotlib.pyplot as plt
import random as rd
import pandas as pd
import numpy as np



# plot the data in data/exp.txt

#plot the data
plt.hist(pd.read_csv('data/exp.txt', sep='\t', header=None).values, bins=100, rwidth=0.7, density=True)
#using rd
plt.hist([rd.expovariate(1) for i in range(1000)], bins=100, rwidth=0.7, density=True)
plt.show()

# plot data in data/gamma.txt
plt.hist(pd.read_csv('data/gamma.txt', sep='\t', header=None).values, bins=100, rwidth=0.9, density=True)
#using rd
plt.hist([np.random.gamma(1,2) for i in range(1000)], bins=100, rwidth=0.9, density=True)
plt.show()
