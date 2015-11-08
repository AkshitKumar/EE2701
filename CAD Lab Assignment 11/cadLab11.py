# Importing necessary libraries
from scipy import *
from matplotlib.pyplot import *
import scipy.signal as signal

# Assigning the time vector
t = linspace(0,20,201) # time constant is unity. So step of 0.1 is ok.

# Function to plot x(t)
def plotX():
	num = poly1d([1,0,2]) # x(0) = 0.1, xdot(0) = 0
	den = poly1d([1,0,3,0]) # denominator of the transform
	sys1 = signal.lti(num,den) # Finding the LTI response
	x = sys1.impulse(T=t)[1] # Finding the inverse transform using impulse method
	figure(0) # Assigning a new figure
	plot(t,x,'r') # Plotting the graph of x(t)
	xlabel(r'$t$') # Setting the X-label
	ylabel(r'$x(t)$') # Setting the Y-label
	title("Q3: Time Response using sys1.impulse of x(t)") # Setting the title of the graph
	show() # Displaying the graph

plotX() # Calling the function 

# Function to plot y(t)
def plotY():
	num = poly1d([2]) # numerator of the transform
	den = poly1d([1,0,3,0]) # denominator of the tranform
	sys1 = signal.lti(num,den) # Finding the LTI transform
	y = sys1.impulse(T=t)[1] # Finding the inverse transform using impulse method
	figure(1) # Assigning a new figure
	plot(t,y,'r') # Plotting the graph of y(t)
	xlabel(r'$t$') # Setting the X-label
	ylabel(r'$y(t)$') # Setting the Y-label
	title("Q3: Time Response using sys1.impulse of y(t)") # Setting the title 
	show() # Display the graph

plotY() # Calling the function

R1 = 10.0 # Assigning value of R1
R2 = 100.0 # Assigning value of R2
L = 1e-3 # Assigning value of L
omega = logspace(3,9,61).reshape((61,1)) # Assigning value of omega
H = R2/((R1+R2) + 1j*omega*L) # Calculating the value of H

def plotResponse():
	figure(1) # Setting up the figure
	cla()
	f = omega/(2*pi) # Converting omega into frequency
	subplot(211) 
	loglog(f,abs(H),'ro') # plotting the magnitude as a loglog plot
	title('Frequency Response') # Setting the title 
	xlabel(r"$f\;(Hz)$") # Setting the X-label
	ylabel(r"$|H|$") # Setting the Y-label
	subplot(212)
	semilogx(f,180*angle(H)/pi,'ro') # plotting the phase as a semilogx plot
	xlabel(r"$f\;(Hz)$") # Setting the X-label
	ylabel(r"Arg$(H)$") # Setting the Y-label
	show() # Display the graph

plotResponse() # Calling the function

t1 = linspace(0,1e-2,100001) # Time vector
t2 = linspace(0,3*1e-5,100001) # time vector

def outputVoltage():
	omega1 = 1e3 
	omega2 = 1e6
	numx = poly1d([1e12 - 1e6,0]) # numerator of X(s)
	denx = poly1d([1,0,1e6+1e12,0,1e18]) # denominator of X(s)
	numh = poly1d([R2]) # numerator of H(s)
	denh = poly1d([L,R1+R2]) # denominator of H(s)
	numy = polymul(numx,numh) # numerator of Y(s)
	deny = polymul(denx,denh) # denominator of Y(s)
	sys = signal.lti(numy,deny) # Finding the LTI transform
	y1 = sys.impulse(T=t1)[1] # Finding the inverse transform using impulse method
	y2 = sys.impulse(T=t2)[1] # Finding the inverse transform using impulse method
	figure(2)
	title("Output Voltage") # Setting of the title
	subplot(211) 
	plot(t1,y1,'r') # plotting output function
	xlabel(r"$t$") # Setting the X-label
	ylabel(r"$v(t)$") # Setting the Y-label
	subplot(212)
	plot(t2,y2,'b')
	xlabel(r"$t$") # Setting the X-label
	ylabel(r"$v(t)$") # Setting the Y-label
	show() # display function

outputVoltage() # calling the function
