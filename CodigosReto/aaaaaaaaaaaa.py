import torch
from torchvision import datasets, transforms
import psutil
import time
import pandas as pd

# simple model that approximates the data of a function

data = pd.read_csv('/home/jay/Estacoasicos/datosReto/datosSIR_1.csv')
# turn data into pytorch tensors
x = torch.tensor(data['x'].values, dtype=torch.float32)

