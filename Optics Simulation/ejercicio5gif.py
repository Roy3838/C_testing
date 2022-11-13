import matplotlib.pyplot as plt
import numpy as np
import random as rd



# hacer un gif usando las imagenes guardadas
#plt.savefig('/home/jay/C_testing/Optics Simulation/images/gauss a_' + str(a) + ' l_' + str(l) + '.png')


w0 = np.linspace(1, 5, 10)
l_s  = np.linspace(1, 10, 10)

for i in range(10):
    for l in range(10):
        
        a = 0.5*w0
        # load values
        img = plt.imread('/home/jay/C_testing/Optics Simulation/images/gauss a_' + str(a) + ' l_' + str(l) + '.png')
        plt.imshow(img)
        plt.show()
        plt.pause(0.1)
        plt.clf()
        
        

