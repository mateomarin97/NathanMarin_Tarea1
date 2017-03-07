import numpy as np
import matplotlib.pyplot as plt

t1= np.loadtxt("t1.dat")
t2= np.loadtxt("t2.dat")
t4=np.loadtxt("t4.dat")
x=[1,2,4]

T=[t1,t2,t4]

plt.figure(figsize=(20,20))
plt.scatter(x,T,label="Tiempos")
plt.xlabel("# procesadores",size=30);
plt.ylabel(r"$\mathrm{t(s)}$",size=30);
plt.legend()
plt.savefig("tiempo.pdf");
