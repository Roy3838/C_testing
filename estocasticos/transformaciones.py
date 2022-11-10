import numpy as np
import random as rd
import matplotlib.pyplot as plt

N=5000
alf=4
bet=1/10

rng=np.random.default_rng()
pd=np.random.gamma(alf,bet,N)

# make a transformation given 1/y
pd2=1/pd


""" GRAFICAS DE LA DISTRUBUCION DE PROBABILIDAD """
#graph the gamma
plt.hist(pd, bins=20, alpha=0.5, label='gamma distribution, beta value = '+str(bet))
plt.legend(loc='upper right')

#graph the transformed gamma
plt.hist(pd2, bins=20, alpha=0.5, label='transformed gamma distribution, beta value = '+str(bet))  
plt.legend(loc='upper right')


""" VALORES ESPERADOS """
#calculate E(X)
E=np.mean(pd)
#make a line at E(X)
plt.axvline(E, color='r', linestyle='dashed', linewidth=2)

#calculate E(1/X)
E2=np.mean(pd2)
#make a line at E(1/X)
plt.axvline(E2, color='g', linestyle='dashed', linewidth=2)



plt.show()





