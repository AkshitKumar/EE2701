# Importing necessary libraries
import sys # Used for taking command line arguments
import numpy as np # Used for importing numpy
from pylab import * # Used for plotting and making use of array

# Check for command line arguments
if(len(sys.argv)!=6):
	print "Usage <n> <M> <nk> <u0> <p>"
	exit(1)
else:
	script,n,M,nk,u0,p = sys.argv

# Converting string values into integers and float
n = int(n) 
M = int(M)
nk = int(nk)
u0 = int(u0)
p = float(p)

# Setting up the standard deviation
Msig = 2

# Creating zero vectors 
xx = np.zeros(n*M) # Electron position xx
u = np.zeros(n*M) # Electron velocity u
dx = np.zeros(n*M) # Displacement in current turn dx

I = [] # Intensity of emitted light
X = [] # Electron position
V = [] # Electron Velocity

# Iterating nk times
for i in range(nk):
	m = (randn() * Msig) + M # Inserting m electrons everytime
	jj = array(where(xx==0)) # Taking all the values where xx = 0
	jj = jj[[0],0:m] # Selecting the first m electrons out of it
	xx[jj[0]] = 1 # Assigning those indices as 1
	ii = array(where(xx>0)) # Checking for where xx>0 and taking in the indices
	X.extend(xx[ii[0]].tolist()) # Adding those position to electron position list
	V.extend(u[ii[0]].tolist()) # Adding those position to electron velocity list
	dx[ii[0]] = u[ii[0]] + 0.5 # Accelerating the dx vector
	xx[ii[0]] = xx[ii[0]] + dx[ii] # Incrementing the xx vector
	u[ii[0]] = u[ii[0]] + 1 # Incrementing the velocity vector
	bb = array(where(xx>n)) # Checking for if the electron has crossed the tube length
	xx[bb[0]] = 0 # Making it's position 0
	dx[bb[0]] = 0 # Making it's displacement 0
	u[bb[0]] = 0 # Making it's velocity 0
	kk = array(where(u>u0)) # Checking for where the velocity has crossed the threshold velocity
	if(size(kk[0])>0):
		pp = array([p for i in range(0,size(kk[0]))]) # Creating a array of probability p
		ll = array(where(random_sample(size(kk[0],))<=pp)) 
		kl = kk[[0],ll[0]]
		if (size(kl)>0):
			u[kl] = 0 # Assigning velocity back to 0
			xx[kl] = xx[kl] - ( dx[kl] * random_sample(size(kl[0]),) ) # Reducing the position
			I.extend(xx[kl].tolist()) # Appending to Intensity list

# Function to display the Position Histogram
def plotPositionHistogram():
	figure(0)
	hist(X,bins=100,range=[0,100])
	xlabel("Position")
	ylabel("Electron Density")
	title("Population Plot of X")
	show()

# Function to display the Intensity Histogram
def plotIntensityHistogram():
	figure(1)
	count = hist(I,bins=100,range=[0,100])
	xlabel("Position")
	ylabel("Population count/intensity")
	title("Histogram of the light intensity")
	show()
	return count

# Function to display the Electron Phase Space Plot
def plotElectronPhaseSpace():
	figure(2)
	plot(X,V,'ro')
	xlabel("Position")
	ylabel("Velocity")
	title("Electron Phase Space")
	show()

# Tabulating the Intensity Plot
def printIntensity(count):
	print "Intensity Data:"
	print "-------------"
	print "xpos | count"
	print "-------------"
	for i in range(len(count[0])):
		if (i>=9):
			print "%d   |    %d" %(count[1][i]+1,count[0][i])
		else:
			print "%d    |    %d" %(count[1][i]+1,count[0][i])

# Calling of declared functions
plotPositionHistogram()
count = plotIntensityHistogram()
plotElectronPhaseSpace()
printIntensity(count)

r"$E\_{0}$"

