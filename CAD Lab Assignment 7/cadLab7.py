# Importing the necessary plot for vectroizing and plotting 
from pylab import *
import numpy as np
import matplotlib.pyplot as plt
from scipy.integrate import quad

# Defining the function 1/1+x^2
def func(x):
	return 1.0/(1.0 + (x*x))

# Vectorizing the function to take a vector as an input
func = np.vectorize(func)

# Defining the ftrap function to give back new value of x,y and h
def ftrap(x):
	h = (max(x) - min(x))/(2*(len(x)-1))
	x = np.arange(min(x),max(x),h)
	y = (np.cumsum(func(x),dtype=float) - ((1.0/2.0)*(func(0)+func(x)))) * h
	return (x,y,h)

# Making a vector which holds values from 0.0 to 5.0 in steps of 0.1
x = np.arange(0.0,5.1,0.1)

# Defining an anonymous function to take a single input
f = lambda t: 1.0/(1.0 + t*t)

# Declaration of useful lists
quadValue = [] # To hold the value obtained from quad function
quadError = [] # To hold the error obtained from quad function
errors = [] # To hold the error between quad and arctan function
valueh = [] # To hold the values of h
valueEstimateErr = [] # To hold the values of the estimate errors
valueExactErr = [] # To hold the values of the exact error

# Iterating through the vector x and finding corresponding value of quad
for i in range(len(x)):
	y,err = quad(f,0,x[i])
	quadValue.append(y)
	quadError.append(err)

# Defining the display of plot of func v/s x
def displayfuncx(x):
	plt.figure(1) # Setting it on figure 1
	plt.plot(x,func(x),'ro',x,func(x)) # Plotting the graph 
	plt.title(r"Plot of $1/(1+t^{2})$") # Setting the title of the graph
	plt.xlabel(r"$t$") # Setting the X-label 
	plt.ylabel(r"$1/(1+t^{2})$") # Setting the Y-label
	plt.show() # Displaying the plot

displayfuncx(x) # Calling the display function

# Creating a taninv vector by using in-built arctan function
taninv = np.arctan(x)

# Defining the display of plot of taninv v/s x
def displaytaninv(x):
	plt.figure(2) # Setting it on figure 2
	plt.plot(x,quadValue,'ro',x,taninv,'k-') # Plotting quadValue v/s x as red dots and taninv function as black line
	plt.title(r"Plot of $arctan(x)$ v/s $x$") # Setting the title of the plot
	plt.xlabel(r"$u$") # Setting the X-label
	plt.ylabel(r"$\int du/(1+u^{2})$") # Setting the Y-label
	plt.legend(("quad fn",r"$arctan(u)$")) # Setting the Legend for the plot
	plt.show() # Displaying the plot

displaytaninv(x) # Calling the display funtion

# Iterating through vector x to calculate the error and appending in the errors list
for i in range(len(x)):
	errors.append(abs(taninv[i] - quadValue[i]))

# Defining the display of plot of Error v/s x
def displayerror():
	plt.figure(3) # Setting it on figure 3
	plt.title(r"Error in $\int dx/(1+x^{2})$") # Setting the title of the plot
	plt.xlabel(r"$x$") # Setting the X - label
	plt.ylabel("Error") # Setting the Y-label
	plt.semilogy(x,errors,"ro") # Plotting the semilog graph of log error v/s x
	plt.show() # Displaying the plot

displayerror() # Calling the display function

def displayIntegral(x):
	h = 0.1 # Initializing the value of h
	plt.figure(4) # Setting the plot to figure 4
	y = np.cumsum(func(x),dtype=float) - ((1.0/2.0)*(func(0)+func(x))) # Calculating the value of y
	y = y * h # Making y = y*h
	plt.title(r"Plot of $arctan(x)$ v/s $x$ using Trapezoid Rule") # Setting the title of the plot
	plt.xlabel(r"$x$") # Setting the X -label
	plt.ylabel(r"$arctan(x)$") # Setting the Y-label
	plt.plot(x,y) # Plotting the x and y
	plt.show() # Displaying the plot

displayIntegral(x) # Calling the display function

# Defining the trapezoid rule for calculating the integral
def TrapezoidRule(x):
	temp = x # Declaring a temp vector
	err = [] # List initialization
	h = 0.1 # Initialising the value of h
	err.append(0.5) # Setting initial value of error
	while (max(err) > 1e-8):
		err = [] # list initialization
		yprev = (np.cumsum(func(temp),dtype=float) - ((1.0/2.0)*(func(0)+func(temp)))) * h # Calculating the value of yprev
		tempnew , ynew , h = ftrap(temp) # Getting the value of new temp, new y and new h
		valueExactErr.append(max(abs(yprev - np.arctan(temp)))) # Adding the value of the exact error
		for k in range(len(temp)-1):
			err.append(ynew[2*k] - yprev[k]) # Adding the value of the err list
		valueh.append(h) # Appending the new value of h
		valueEstimateErr.append(max(err)) # Appending the value of the estimate error
		temp = tempnew # Assigning old temp value to new temp value

TrapezoidRule(x) # Calling the trapezoidrule function

# Defining the display Error Plot function
def displayErrorPlot():
	plt.figure(5) # Setting it to figure 5
	plt.xlabel(r"$log$ $h$") # Setting the X-label
	plt.ylabel(r"Error ($log$ $err$)") # Setting the Y-label
	plt.title(r"$log$ - $log$ plot of $Error$ v/s $h$") # Setting the title of the plot
	plt.plot(log10(valueh),log10(valueEstimateErr),"g+",log10(valueh),log10(valueExactErr),'ro') # Plotting the log10 - log10 graph
	plt.legend(("Estimated Error","Exact Error")) # Setting the legend for the graph
	plt.show() # Displaying the plot

displayErrorPlot() # Calling the Error plot function