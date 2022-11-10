import numpy as np
import random as rd
import matplotlib.pyplot as plt
import time

def f(x,y):
    return x**2 + y**2 + 25*(np.sin(x)**2 + np.sin(y)**2)

def annealing(T_0, L, dt):

    """ COMPUTING THE OPTIMIZATION PATH """
    x_0=rd.uniform(-5,5)
    y_0=rd.uniform(-5,5)
    p_0=np.array([x_0,y_0])
    p_1=p_0
    while (T_0>0.01):
        T_0=T_0*0.99
        for i in range(L):
            p_1=[rd.uniform(-dt,dt)+p_0[0],rd.uniform(-dt,dt)+p_0[1]]
            if (f(p_1[0],p_1[1])<f(p_0[0],p_0[1])):
                p_0=p_1
            # if not Boltzmann Gibbz
            else:
                if (rd.uniform(0,1)<np.exp(-f(p_1[0],p_1[1])/T_0)):
                    p_0=p_1
    # return total distance to the minimum
    return np.sqrt(p_1[0]**2+p_1[1]**2)



""" USANDO SIMULATED ANNEALING PARA ENCONTRAR EL MINIMO DE LA FUNCION ANNEALING """
T_0_p=rd.uniform(0,100)
L_p=rd.uniform(0,100)
dt_p=rd.uniform(0,1)
param_0=np.array([T_0_p,L_p,dt_p])
param_0=[int(np.ceil(param_0[0])),int(np.ceil(param_0[1])),param_0[2]]
param_1=param_0
T_0=20
print(param_0)
f_eval_0=annealing(param_0[0],param_0[1],param_0[2])
saving_parameter_history=[]
while (T_0>0.5):
    T_0=T_0*0.85
    saving_parameter_history.append(param_0)
    for i in range(10):
        params_1=[np.abs(rd.uniform(-50,50)+param_0[0]),np.abs(rd.uniform(-50,50)+param_0[1]), np.abs(rd.uniform(-0.5,0.5)+param_0[2])]
        params_1=[int(np.ceil(params_1[0])),int(np.ceil(params_1[1])),params_1[2]]
        f_eval_1=annealing(params_1[0],params_1[1],params_1[2])
        print("Temperatura: " + str(T_0) + " con " + str(params_1) + " dando un resultado " + str(f_eval_1))
        if (f_eval_1<f_eval_0):
            f_eval_0=f_eval_1
            param_0=params_1
        # if not Boltzmann Gibbz
        else:
            if (rd.uniform(0,1)<np.exp(f_eval_1)/T_0):
                f_eval_0=f_eval_1
                param_0=params_1
    
# return total distance to the minimum
print(saving_parameter_history)

x=np.linspace(-5,5,100)
y=np.linspace(-5,5,100)
X,Y=np.meshgrid(x,y)
Z=f(X,Y)

plt.contour(X,Y,Z,100)
plt.show()

""" PLOTTING THE OPTIMIZATION PATH """
