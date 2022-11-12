import numpy as np
import random as rd
import matplotlib.pyplot as plt

def f(x,y):
    return x**2 + y**2 + 25*(np.sin(x)**2 + np.sin(y)**2)

def annealing(T_0, L, delta_uniforme):

    """ COMPUTING THE OPTIMIZATION PATH """
    x_0=rd.uniform(-5,5)
    y_0=rd.uniform(-5,5)
    p_0=np.array([x_0,y_0])
    T_0_i=T_0
    p_1=p_0
    ciclos=0
    contador_boltzmann=0
    contador_zi_cuajo=0


    while (T_0>0.01):
        T_0=T_0*0.99
        #print(p_1)
        # make color change according to temperature RED -> BLUE
        color=(T_0/T_0_i,0,1-T_0/T_0_i)
        plt.plot(p_0[0],p_0[1],'ro',color=color)
        for i in range(L):
            ciclos+=1
            p_1=[rd.uniform(-0.1,0.1)+p_0[0],rd.uniform(-0.1,0.1)+p_0[1]]
            if (f(p_1[0],p_1[1])<f(p_0[0],p_0[1])):
                contador_zi_cuajo+=1
                p_0=p_1
            # if not Boltzmann Gibbz
            else:
                if (rd.uniform(0,1)<np.exp(-f(p_1[0],p_1[1])/T_0)):
                    contador_boltzmann+=1
                    p_0=p_1
    
    return(np.abs(p_1))



x=np.linspace(-5,5,100)
y=np.linspace(-5,5,100)
X,Y=np.meshgrid(x,y)
Z=f(X,Y)

plt.contour(X,Y,Z,100)
print(annealing(100,100,0.1))
plt.show()

""" PLOTTING THE OPTIMIZATION PATH """


