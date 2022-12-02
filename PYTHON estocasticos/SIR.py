import numpy as np
import random as rd
import matplotlib.pyplot as plt

def main():
    # Initial conditions
    S0 = 1000
    E0 = 100
    I0 = 10
    R0 = 0
    B=2.75
    G=0.04
    sigma=0.12
    T=120
    dt=0.1
    NT=int(T/dt)
    N=1000

    
    # Time vector  
    t = np.linspace(0,T,NT)

    # Initialize the vectors
    S = np.zeros(NT)
    E = np.zeros(NT)
    I = np.zeros(NT)
    R = np.zeros(NT)

    # Initial conditions    
    S[0] = S0
    E[0] = E0
    I[0] = I0
    R[0] = R0

    

    # Iterate using finite diferences
    for i in range(0,NT-1):

        S[i+1]=S[i]*(-B*I[i]/N*dt + 1) + np.random.uniform(-5,5)
        E[i+1]=(B*S[i]*I[i]/N - sigma*E[i])*dt + E[i]  + np.random.uniform(-5,5)
        I[i+1]=(sigma*E[i]-G*I[i])*dt + I[i] + np.random.uniform(-5,5)
        R[i+1]=G*I[i]*dt + R[i] + np.random.uniform(-5,5)

    # Plot the results
    plt.plot(t,S,'b',label='Susceptibles')
    plt.plot(t,E,'y',label='Expuestos')
    plt.plot(t,I,'r',label='Infectados')
    plt.plot(t,R,'g',label='Recuperados')

    print("Max value of E: ", max(E))
    print("Max value of I: ", max(I))

    # make a moving average of the values
    for i in range(20,NT-1):
        S[i+1]=np.mean(S[i-20:i+20])
        E[i+1]=np.mean(E[i-20:i+20])
        I[i+1]=np.mean(I[i-20:i+20])
        R[i+1]=np.mean(R[i-20:i+20])

    plt.plot(t,S,'black',label='Susceptibles')
    plt.plot(t,E,'black',label='Expuestos')
    plt.plot(t,I,'black',label='Infectados')
    plt.plot(t,R,'black',label='Recuperados')

    plt.show()


if __name__ == "__main__":
    main()

