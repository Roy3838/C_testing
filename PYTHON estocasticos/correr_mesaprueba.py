import numpy as np
from mesaprueba import MoneyModel
import matplotlib.pyplot as plt

model = MoneyModel(1000, 300, 300)
for i in range(20):
    model.step()


agent_counts = np.zeros((model.grid.width, model.grid.height))
for cell in model.grid.coord_iter():
    cell_content, x, y = cell
    agent_count = len(cell_content)
    agent_counts[x][y] = agent_count

plt.scatter(agent_counts, interpolation="nearest")
plt.show()
