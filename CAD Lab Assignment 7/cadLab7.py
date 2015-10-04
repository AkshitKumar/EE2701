from pylab import *
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad


def func(x):
	return 1.0/(1.0 + (x*x))

func = np.vectorize(func)

def ftrap(x):
	h = (max(x) - min(x))/(2*(len(x)-1))
	x = np.arange(min(x),max(x),h)
	y = np.cumsum(func(x),dtype=float) - ((1.0/2.0)*(func(0)+func(x)))
	y = y * h
	return (x,y,h)

x = np.arange(0.0,5.1,0.1)

f = lambda t: 1.0/(1.0 + t*t)

quadValue = []
quadError = []
errors = []

for i in range(len(x)):
	y,err = quad(f,0,x[i])
	quadValue.append(y)
	quadError.append(err)

def displayfuncx(x):
	plt.figure(1)
	plt.plot(x,func(x),'ro',x,func(x))
	plt.title(r"Plot of $1/(1+t^{2})$")
	plt.xlabel(r"$t$")
	plt.ylabel(r"$1/(1+t^{2})$")
	plt.show()

displayfuncx(x)

taninv = np.arctan(x)

def displaytaninv(x):
	plt.figure(2)
	plt.plot(x,quadValue,'ro',x,taninv,'k-')
	plt.title(r"Plot of $arctan(x)$ v/s $x$")
	plt.xlabel(r"$u$")
	plt.ylabel(r"$\int du/(1+u^{2})$")
	plt.legend(("quad fn",r"$arctan(u)$"))
	plt.show()

displaytaninv(x)

for i in range(len(x)):
	errors.append(abs(taninv[i] - quadValue[i]))

def displayerror():
	plt.figure(3)
	plt.title(r"Error in $\int dx/(1+x^{2})$")
	plt.xlabel(r"$x$")
	plt.ylabel("Error")
	plt.semilogy(x,errors,"ro")
	plt.show()

displayerror()

def displayIntegral(x):
	h = 0.1
	plt.figure(4)
	y = np.cumsum(func(x),dtype=float) - ((1.0/2.0)*(func(0)+func(x)))
	y = y * h
	plt.title(r"Plot of $arctan(x)$ v/s $x$ using Trapezoid Rule")
	plt.xlabel(r"$x$")
	plt.ylabel(r"$arctan(x)$")
	plt.plot(x,y)
	plt.show()

displayIntegral(x)

valueh = []
valueEstimateErr = []
valueExactErr = []

def TrapezoidRule(x):
	temp = x
	err = []
	h = 0.1
	err.append(0.5)
	while (max(err) > 1e-8):
		err = []
		yprev = np.cumsum(func(temp),dtype=float) - ((1.0/2.0)*(func(0)+func(temp)))
		yprev = yprev * h
		tempnew , ynew , h = ftrap(temp)
		valueExactErr.append(max(abs(yprev - np.arctan(temp))))
		for k in range(len(temp)-1):
			err.append(ynew[2*k] - yprev[k])
		valueh.append(h)
		valueEstimateErr.append(max(err))
		temp = tempnew

TrapezoidRule(x)

def displayErrorPlot():
	plt.figure(5)
	plt.xlabel(r"$log$ $h$")
	plt.ylabel(r"Error ($log$ $err$)")
	plt.title(r"$log$ - $log$ plot of $Error$ v/s $h$")
	plt.plot(log10(valueh),log10(valueEstimateErr),"g+",log10(valueh),log10(valueExactErr),'ro')
	plt.legend(("Estimated Error","Exact Error"))
	plt.show()

displayErrorPlot()

