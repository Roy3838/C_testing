import matplotlib.pyplot as plt
import pandas as pd


valores=pd.read_csv('data/ps.csv', sep=',', header=None)
valores2=pd.read_csv('data/ps2.csv', sep=',', header=None)
plt.scatter(valores[0],valores[1])

# plt.arrow(ps[-1][0],ps[-1][1],ps[0][0]-ps[-1][0],ps[0][1]-ps[-1][1],
#     head_width=0.05, head_length=0.1, fc='b', ec='b')
valores=valores.values
c=len(valores)
for i in range(c-1):
    plt.arrow(valores[i][0],valores[i][1],valores[i+1][0]-valores[i][0],valores[i+1][1]-valores[i][1],
    head_width=0.05, head_length=0.1, fc='b', ec='b')
plt.show()
plt.scatter(valores2[0],valores2[1])
valores2=valores2.values
for i in range(c-1):
    plt.arrow(valores2[i][0],valores2[i][1],valores2[i+1][0]-valores2[i][0],valores2[i+1][1]-valores2[i][1],
    head_width=0.05, head_length=0.1, fc='b', ec='b')

plt.show()