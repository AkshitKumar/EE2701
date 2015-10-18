# Importing all the required modules
import numpy as np 
from pylab import *
import matplotlib.pyplot as plt
import scipy.special as sp

matrix = np.loadtxt('fitting.dat') # Reading the matrix from fitting.dat file
time = matrix[ : ,0] # Extracting the time column from the matrix
data = matrix[ : ,1 : ] # Extracting the data columns from the matrix
sigma = np.logspace(-1,-3,9) # Creating the sigma vector from -1 to -3

# Function to display the graph generated from fitting.dat
def displayPlotNoise():
	plt.figure(0) # Setting plt to figure 0
	plt.plot(time,data) # Plotting the graph of f(t) v/s t
	plt.xlabel(r"$t$") # Setting the X-label
	plt.ylabel(r"$f(t)=g(t)+n(t)$") # Setting the Y-label
	plt.legend(("1","2","3","4","5","6","7","8","9")) # Setting the legend of the graph
	plt.title(r"Plot of $f(t)$ v/s $t$") # Setting the title of the graph
	plt.show() # show() function to display the plot

displayPlotNoise() # Calling the function

data1 = data[:,0]  # Extracting the first column of the data matrix

# Function to calculate the value of function for given A and B
def g(t,A,B):
	return (A*sp.jn(2,t)) + ((B)*t)

y = g(time,1.05,-0.105) #Calling the function for A= 1.05 and B= -0.105

# Function to display the true value of function without the noise
def displayPlot():
	plt.figure(1) # Setting plt to figure 1
	p = plt.plot(time,y,'b-') # Plotting the graph of f(t) v/s t
	plt.xlabel(r"$t$") # Setting the X-label
	plt.ylabel(r"$g(t)$") # Setting the Y-label
	plt.legend(("True Value")) # Setting the legend of the graph
	plt.title(r"Plot of $g(t)$ v/s $t$") # Setting the title of the graph
	plt.show() # show() function to display the plot

displayPlot() # Calling the function

#Function to display the error in the function using errobar
def displayError(t,data1):
	plt.figure(2) # Setting plt to figure 2
	errorbar(t[::5],data1[::5],sigma[0],fmt='ro') # Plotting the errorbar for data1 with sigma = sigma[0] 
	plt.xlabel(r"$t$") # Setting the X-label
	plt.ylabel(r"$Error in data$") # Setting the Y-label
	plt.plot(time,y,'k-') # Plotting the function g(t)
	plt.title(r"Plot of $Error$ v/s $t$") # Setting the title of the graph
	plt.show() # show() function to display the plot

displayError(time,data1) # Calling the function

x = sp.jn(2,time) # defining the x column vector
t = time # defining the time column vector
M = c_[x,t] # Concatanating the x and time column vectors into a matrix of 2 columns

val = np.array([[1.05],[-0.105]]) # Defining the (A0,B0) column matrix

values =  np.mat(M)*np.mat(val) # Matrix multiplication to find the value of g(t)
y2 = np.array(y) # Converting y2 into an array
y2.shape = (len(y),1) # Converting it into a column matrix by changing the shape of the matrix
print y2 - values # Verify that values obtained from the function and matrix multiplication is same

A = np.arange(0.0,2.0,0.1) # A vector
B = np.arange(-0.2,0.0,0.01) # B vector

# Function to calculate the mean square estimation
def meanSquare(data1,time,A,B):
	sum = 0
	for i in range(len(data1)):
		sum = sum + (data1[i] - g(time[i],A,B))**2
	return sum/len(data1)

# Creating a 2D matrix assigning all values to 0
epsilon = [[0 for x in range(len(A))] for x in range(len(A))]

# Iterating through the 2D matrix and assinging calculated values of epsilon
for i in range(len(A)):
	for j in range(len(B)):
		epsilon[i][j] = meanSquare(data1,time,A[i],B[j])

# Function to display the contout plot of epsilon
def displayEpsilon():
	plt.figure(3) # Setting plt to figure 3
	plt.contour(A,B,epsilon) # Plotting the contour plot of epsilon
	plt.xlabel(r"A Values") # Setting the X-label
	plt.ylabel(r"B Values") # Setting the Y-label
	plt.title(r"Contour Plot of $\epsilon$") # Setting the title of the graph
	plt.show() # show() function to display the plot

displayEpsilon() # Calling the function

a,b = np.linalg.lstsq(M,data)[0] # Calculating the best estimate of a,b using lstsq function from scipy.linalg
errorInA = abs(a-1.05) # Calculating the error in values of A
errorInB = abs(b+0.105) # Calculating the error in the values of B

def displayErrorEstimate():
	plt.figure(4) # Setting plt to figure 4
	plt.plot(sigma,errorInA,'ro',sigma,errorInB,'b+') # Plotting the graph
	plt.xlabel(r"Noise $\sigma$") # Setting the X-label
	plt.ylabel(r"Error in values") # Setting the Y-label
	plt.legend(("Error in values of A","Error in values of B"))
	plt.title(r"Plot of error in A and B values") # Setting the title of the graph
	plt.show() # show() function to display the plot

displayErrorEstimate() # Calling the function

def displayErrorEstimateLog():
	plt.figure(5) # Setting plt to figure 4
	plt.loglog(sigma,errorInA,'ro',sigma,errorInB,'b+')# Plotting the graph
	plt.xlabel(r"Noise $\sigma$") # Setting the X-label
	plt.ylabel(r"Error in values") # Setting the Y-label
	plt.title(r" loglog Plot of error in A and B values") # Setting the title of the graph
	plt.legend(("Error in values of A","Error in values of B"))
	plt.show() # show() function to display the plot

displayErrorEstimateLog() # Calling the function