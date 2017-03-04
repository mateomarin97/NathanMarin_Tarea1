import numpy as np
import matplotlib.pyplot as plt

datos= np.loadtxt("datos.dat")
a = datos.T
plt.figure(figsize=(20,20))
plt.imshow(a)
plt.savefig("grafico.pdf")
