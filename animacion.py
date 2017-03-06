import numpy as np
import matplotlib.pyplot as plt

datos= np.loadtxt("datos.dat")
e1=datos[:,0].T
e2=datos[:,1].T
e3=datos[:,2].T

x=np.linspace(0,100,len(e1))
plt.figure(figsize=(20,20))
plt.plot(x,e1,label='e1')
plt.plot(x,e2,label='e2')
plt.plot(x,e3,label='e3')
plt.legend()
plt.savefig("grafico.pdf")

