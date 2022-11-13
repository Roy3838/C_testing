import random as rd
import numpy as np
import matplotlib.pyplot as plt


def coso(
    N = 200,
    w0 = 3,
    puntos = 512, #512/2
    l=1
    ):

    xmax = 3*w0
    a = 0.5*w0
    xs = xmax*(2/puntos)*np.arange(-puntos/2, puntos/2)
    # ventana numerica
    [X,Y] = np.meshgrid(xs,xs)

    # hacer funciones de interferencia
    gauss = lambda x,y,w0: np.exp(-x**2/w0**2 - y**2/w0**2)
    interfiere_gauss = lambda x,y,w0,phi: np.exp(1j*phi*x)*gauss(x,y,w0) + np.exp(-1j*phi*x)*gauss(x,y,w0)
    vortex = lambda x,y,w0,l: (np.sqrt(x**2+y**2)**np.abs(l))*np.exp(1j*l*np.arctan2(y,x))*np.exp(-x**2/w0**2 - y**2/w0**2)

    # intensidad
    I = np.zeros([puntos,puntos])
    Iv = np.zeros([puntos,puntos])
    Cv = np.zeros([puntos,puntos])

    # valor esperado

    for ii in range(N):
        # MATLAB w=rand;
        w = rd.random()
        rho = a*np.sqrt(w)
        phi = 2*np.pi*rd.random()
        x = rho*np.cos(phi)
        y = rho*np.sin(phi)

        I = I + interfiere_gauss(X-x,Y-y,w0,phi)*np.conj(interfiere_gauss(X-x,Y-y,w0,phi))

        # vortex
        Iv = Iv + vortex(X-x,Y-y,w0,l)*np.conj(vortex(X-x,Y-y,w0,l))
        Cv = Cv + np.real(vortex(X-x,Y-y,w0,l)*np.conj(vortex(X-x,Y-y,w0,l)))
    I = I/N
    Iv = Iv/N
    Cv = Cv/N
    # graficar
    plt.figure()
    plt.imshow(np.abs(I), cmap='gray')
    plt.title('Gauss')
    #save image
    plt.savefig('/home/jay/C_testing/Optics Simulation/images/gauss a_' + str(a) + ' l_' + str(l) + '.png')

w0 = np.linspace(1, 5, 10)
l_s  = np.linspace(1, 10, 10)

for a in range(10):
    for l in range(10):
        print(a)
        print(l)
        a = 0.5*w0
        coso(w0=w0[a], l=l_s[l])