import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


valores = pd.read_csv('data/monte_img.csv', header=None)
valores = valores.values
x = valores[:,0]
y = valores[:,1]
plt.plot(x,y)
plt.show()
