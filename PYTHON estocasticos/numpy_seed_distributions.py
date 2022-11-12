import numpy as np
import random as rd
import matplotlib.pyplot as plt

# Set the seed
np.random.seed(1234)
rd.seed(1234)

# Generate 1000 random numbers
np_random_numbers = np.random.rand(1000)
rd_random_numbers = [rd.random() for i in range(1000)]

# Beta distribution
np_beta = np.random.beta(0.5, 0.5, 1000)
rd_beta = [rd.betavariate(0.5, 0.5) for i in range(1000)]

# Gamma distribution
np_gamma = np.random.gamma(2, 2, 1000)
rd_gamma = [rd.gammavariate(2, 2) for i in range(1000)]

# Plot the distributions
plt.hist(np_random_numbers, bins=20, alpha=0.5, label='numpy')
plt.hist(rd_random_numbers, bins=20, alpha=0.5, label='random')
plt.legend(loc='upper right')
plt.show()

# Plot the beta distribution
plt.hist(np_beta, bins=20, alpha=0.5, label='numpy')
plt.hist(rd_beta, bins=20, alpha=0.5, label='random')
plt.legend(loc='upper right')
plt.show()

# Plot the gamma distribution
plt.hist(np_gamma, bins=20, alpha=0.5, label='numpy')
plt.hist(rd_gamma, bins=20, alpha=0.5, label='random')
plt.legend(loc='upper right')
plt.show()






