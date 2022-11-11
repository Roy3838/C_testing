import random as rd
import matplotlib.pyplot as plt
import numpy as np

# reverse engineer the gamma distribution number generator

rd.seed(1234)

#uniform = [rd.random() for i in range(10)]

def gamma(alpha, beta):

    ainv = np.sqrt(2.0 * alpha - 1.0)
    u1 = rd.random()
    u2 = 1.0 - rd.random()
    bbb = alpha - np.log(4)
    ccc = alpha + ainv
    v = np.log(u1 / (1.0 - u1)) / ainv
    x = alpha * np.exp(v)
    z = u1 * u1 * u2
    return x * beta

random_gamma2 = [gamma(1,1) for i in range(10)]
random_gamma = [rd.gammavariate(1, 1) for i in range(10) ]

print(random_gamma)
print(random_gamma2)
