import numpy as np
import random as rd
import matplotlib.pyplot as plt
# function that returns distance traveled between the points
def f(ps):
    # ps is a matrix of points organized as [[x1,y1],[x2,y2],...,[xn,yn]]
    # the function returns the distance traveled between the points
    dist=0
    dist = np.linalg.norm(ps[0]-ps[-1])
    # save highest distance between points
    #distances = []
    for i in range(cities-1):
        distance = np.linalg.norm(ps[i]-ps[i+1])
        dist = dist + distance
    
    return dist
    

def f_plot(ps):
    # ps is a matrix of points organized as [x1,x2,...,xn;y1,y2,...,yn]
    # the function returns the distance traveled between the points
    dist=0
    dist = np.linalg.norm(ps[0]-ps[-1])
    plt.arrow(ps[-1][0],ps[-1][1],ps[0][0]-ps[-1][0],ps[0][1]-ps[-1][1],
    head_width=0.05, head_length=0.1, fc='b', ec='b')
    for i in range(cities-1):
        dist = dist + np.linalg.norm(ps[i]-ps[i+1])
        plt.arrow(ps[i][0],ps[i][1],ps[i+1][0]-ps[i][0],ps[i+1][1]-ps[i][1],
        head_width=0.05, head_length=0.1, fc='b', ec='b')
    plt.show()
    return dist

    
def vecindad(ps,n=1):
    #Se escogen dos puntos al azar diferentes
    #get the global variable indice
    
    # j=i+1
    # if (j==cities):
    #     j=0
    #Se intercambian los puntos con una variable temporal
    ps2=ps.copy()
    for k in range(n):
        i = rd.randint(0,cities-1)
        j = rd.randint(0,cities-1)
        while (i==j):
            j = rd.randint(0,cities-1)
        ps2[i] = ps[j]
        ps2[j] = ps[i]
    return ps2

# def vecindad(ps):
#     #shuffle ps positions
#     indices=np.linspace(0,cities-1,cities)
#     rd.shuffle(indices)
#     ps2=ps.copy()
#     for i in range(cities):
#         ps2[i]=ps[int(indices[i])]
#     return ps2


def annealing(T_0, L, cities = 3):
    
    T_0_i=T_0
    
    """ COMPUTING THE OPTIMIZATION PATH """          
    ps_0=ps
    #gil_god=ps
    while (T_0>0.000000000001):
        T_0=T_0*0.95
        print(T_0)    
        for i in range(L):
            # aqui es donde se hace el cambio de puntos
            ps_1 = ps_0
            eval_0=f(ps_0)
            ps_1 = vecindad(ps_1,1)
            eval_1=f(ps_1)
            
            if (eval_1<eval_0):
                ps_0=ps_1
                # if (f(ps_0)<f(gil_god)):
                #     gil_god=ps_0
            # if not Boltzmann Gibbz
            else:
                if (rd.uniform(0,1)<np.exp(-eval_1/T_0)):
                    ps_0=ps_1
    return(ps_0)

rd.seed(3)
cities = 100
ps=np.zeros([cities,2])
for i in range(cities):
    ps[i,0]=rd.uniform(-2,2)
    ps[i,1]=rd.uniform(-2,2)

#make a circlular path ps
# for i in range(cities):
#     ps[i,0]=np.cos(2*np.pi*i/cities)
#     ps[i,1]=np.sin(2*np.pi*i/cities)
#randomize the path
# ps=ps[rd.sample(range(cities),cities),:]

#ps override
#ps = np.array([[-2,2],[2,2],[-2,-2],[2,-2]])
# scatter of points
f_plot(ps)
newps=annealing(3,10000, cities)
f_plot(newps)
print(f(ps))
print(f(newps))

""" PLOTTING THE OPTIMIZATION PATH """


