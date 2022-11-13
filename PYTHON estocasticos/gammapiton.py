import random as rd
import matplotlib.pyplot as plt
import numpy as np
""" Demostrando que la distribucion gamma es la sumatoria de exp()"""
def gamma_dist(alpha, beta):
    sum = 0
    for i in range(alpha):
        sum += rd.expovariate(beta)
    return sum

# Se hacen los dos arreglos, uno con gamma() y otro con el metodo gamma basado en exp().
gamma1=[rd.gammavariate(1.0, 1.0) for i in range(100)]
gamma2=[gamma_dist(1,1) for i in range(100)]

#curva teorica de la distribucion gamma (pdf)
x = np.linspace(0, 10, 100)
y = x**(1-1)*np.exp(-x)

#Sacar la varianza de las distribuciones
var1=np.var(gamma1)
var2=np.var(gamma2)

#Sacar la media de las distribuciones
mean1=np.mean(gamma1)
mean2=np.mean(gamma2)

#graph both distributions
plt.hist(gamma2, alpha=0.5,  label='Gamma Random', color='green', bins=20, density=True)
plt.hist(gamma1, alpha=0.5, label='Ganna Funcion', color='blue', bins=20, density=True)
plt.plot(x, y, label='Gamma Teorica', color='red')
# poner las varianzas y medias en el grafico
plt.text(0.7, 0.5, 'Varianza 1: '+str(np.round(var1,2)), transform=plt.gca().transAxes)
plt.text(0.7, 0.4, 'Varianza 2: '+str(np.round(var2,2)), transform=plt.gca().transAxes)
plt.text(0.7, 0.3, 'Media 1: '+str(np.round(mean1,2)), transform=plt.gca().transAxes)
plt.text(0.7, 0.2, 'Media 2: '+str(np.round(mean2,2)), transform=plt.gca().transAxes)
plt.show()