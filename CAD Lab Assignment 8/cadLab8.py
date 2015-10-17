import numpy as np 
from pylab import *
import matplotlib.pyplot as plt
import scipy.special as sp

matrix = np.loadtxt('fitting.dat')
time = matrix[ : ,0]
data = matrix[ : ,1 : ]
sigma = np.logspace(-1,-3,9)

def displayPlotNoise():
	plt.figure(0)
	plt.plot(time,data)
	plt.xlabel(r"$t$")
	plt.ylabel(r"$f(t)$")
	plt.legend(("1","2","3","4","5","6","7","8","9"))
	plt.show()

displayPlotNoise()

data1 = data[:,0]

def g(t,A,B):
	return (A*sp.jn(2,t)) + ((B)*t)

y = g(time,1.05,-0.105)

def displayPlot():
	plt.figure(1)
	p = plt.plot(time,y,'k-')
	plt.legend(("True Value"))
	plt.show()

displayPlot()

def displayError(t,data1):
	plt.figure(2)
	errorbar(t[::5],data1[::5],sigma[0],fmt='ro')
	plt.plot(time,y,'k-')
	plt.show()

displayError(time,data1)

x = sp.jn(2,time)
t = time
M = c_[x,t]

val = np.array([[1.05],[-0.105]])

values =  np.mat(M)*np.mat(val)
y2 = np.array(y)
y2.shape = (len(y),1)
print y2 - values

A = np.arange(0.0,2.0,0.1)
B = np.arange(-0.2,0.0,0.01)

def meanSquare(data1,time,A,B):
	sum = 0
	for i in range(len(data1)):
		sum = sum + (data1[i] - g(time[i],A,B))**2
	return sum/len(data1)

epsilon = [[0 for x in range(len(A))] for x in range(len(A))]
for i in range(len(A)):
	for j in range(len(B)):
		epsilon[i][j] = meanSquare(data1,time,A[i],B[j])
print epsilon

def displayEpsilon():
	plt.figure(3)
	plt.contour(A,B,epsilon)
	plt.show()

displayEpsilon()

a,b = np.linalg.lstsq(M,data)[0]
errorInA = abs(a-1.05)
errorInB = abs(b+0.105)

def displayErrorEstimate():
	plt.figure(4)
	plt.plot(sigma,errorInA,'ro',sigma,errorInB,'b+')
	plt.show()

displayErrorEstimate()

def displayErrorEstimateLog():
	plt.figure(5)
	plt.loglog(sigma,errorInA,'ro',sigma,errorInB,'b+')
	plt.show()

displayErrorEstimateLog()