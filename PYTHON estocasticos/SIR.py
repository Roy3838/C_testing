import numpy as np
import random as rd
import matplotlib.pyplot as plt

def main():
    # Initial conditions
    S0 = 997
    I0 = 3
    R0 = 0
    B=0.25
    G=0.05
    T=100
    dt=0.1
    NT=int(T/dt)
    N=1000
    
    # Time vector  
    t = np.linspace(0,T,NT)

    # Initialize the vectors
    S = np.zeros(NT)
    I = np.zeros(NT)
    R = np.zeros(NT)

    # Initial conditions    
    S[0] = S0
    I[0] = I0
    R[0] = R0

    # Iterate using finite diferences
    for i in range(0,NT-1):
        S[i+1]=S[i]*(-B*I[i]/N*dt + 1)
        I[i+1]=I[i]*(B*S[i]/N*dt - G*dt + 1)
        R[i+1]=G*I[i]*dt + R[i]

    # Plot the results
    plt.plot(t,S,'b',label='Susceptibles')
    plt.plot(t,I,'r',label='Infectados')
    plt.plot(t,R,'g',label='Recuperados')

    plt.show()


if __name__ == "__main__":
    main()