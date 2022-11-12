import numpy as np
import random as rd

# Makeshift pseudo-random number generator

def PRNG(a, m, x_0, iterations):
    # a : multiplicador
    # m : modulo
    # x_0 : semilla
    # iterations : numero de iteraciones
    # returns a list of pseudo-random numbers
    # initialize the list
    x = np.zeros(iterations)
    x[0]=x_0
    u_x = np.zeros(iterations)

    # generate the pseudo-random numbers
    for i in range(1,iterations):
        x[i]=(a*x[i-1])%m
        u_x[i]=x[i]/m

    return(u_x)

a=7**5
m=2**31-1
x_0=470211272/(a)%m
print(PRNG(a, m, x_0, 100))
    



