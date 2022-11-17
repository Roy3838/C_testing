import numpy as np
import random as rd
import matplotlib.pyplot as plt

# function that returns distance traveled between the points
def f(ps):
    # ps is a matrix of points organized as [x1,x2,...,xn;y1,y2,...,yn]
    for i in range(len(ps)):
        if i == 0:
            dist = np.linalg.norm(ps[i]-ps[-1])
        else:
            dist += np.linalg.norm(ps[i]-ps[i-1])
    return dist

def annealing(T_0, L, delta_uniforme, cities = 3):
    
    T_0_i=T_0
    
    """ COMPUTING THE OPTIMIZATION PATH """
    
    ps=np.zeros([2,cities])
    for i in range(cities):
        ps[0,i]=rd.uniform(-5,5)
        ps[1,i]=rd.uniform(-5,5)
    

    ps_0=ps
    print(ps)
    


    while (T_0>0.01):
        T_0=T_0*0.99
        for i in range(L):
            # aqui es donde se hace el cambio de puntos
            ps_1 = ps_0
            # se recorre la matrix de puntos Ps
            for j in range(cities):
                # hay una probabilidad de dependiendo de la temperaturas de que se cambien los puntos vecinos

                if (rd.uniform(0,1)< T_0/T_0_i):
                    # si es el ultimo punto, se cambia con el primero
                    if (j==cities):
                        temp=ps_1[:,j]
                        ps_1[:,j]=ps_1[:,1]
                        ps_1[:,1]=temp
                    # se cambia el punto j y el j+1
                    else:
                        temp=ps_0[:,j]
                        ps_1[:,j]=ps_1[:,j+1]
                        ps_1[:,j+1]=temp

                    
            if (f(ps_1)<f(ps_0)):
                contador_zi_cuajo+=1
                ps_0=ps_1
            # if not Boltzmann Gibbz
            else:
                if (rd.uniform(0,1)<np.exp(-f(ps_1)/T_0)):
                    contador_boltzmann+=1
                    ps_0=ps_1
    
    return(ps_0)


cities = 3
print(annealing(100,100,0.1, cities))
plt.show()

""" PLOTTING THE OPTIMIZATION PATH """


