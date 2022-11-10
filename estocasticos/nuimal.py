import random as rd
import matplotlib.pyplot as plt


# make exponential distribution
rd.seed(1)
m = [rd.gammavariate(1,1) for i in range(1000)]
plt.hist(m, bins=100)
plt.show()


