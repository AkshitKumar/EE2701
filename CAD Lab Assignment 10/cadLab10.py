# Importing all the required modules
import sys # Module required for command line arguments
from pylab import * # Module for using numpy and matplotlib
import mpl_toolkits.mplot3d.axes3d as p3 # Module for plotting surface plots

# Checking for command line arguments
if(len(sys.argv)!=6):
	print "Usage <Nx> <Ny> <Nbegin> <Nend> <Niter>" # Correct syntax of command line arguments
	exit(1)
else:
	script , Nx , Ny , Nbegin , Nend , Niter = sys.argv

# Converting the arguments into corresponding integers
Nx = int(Nx) # Size along X
Ny = int(Ny) # Size along Y
Nbegin = int(Nbegin) # Start of electrode on each side
Nend = int(Nend) # End of electrode on each side
Niter = int(Niter) # Number of iterations to perform

# Creation of the phi matrix
phi = zeros((Nx,Ny))
phi[0,Nbegin:Nend] = 1

# Decalring an errors list
errors = [] 

# Running the simulation Niter times
for k in range(Niter):
	oldphi = phi.copy() # Making a copy of phi and storing in oldphi
	# Updating the inner values of phi
	phi[1:-1,1:-1] = 0.25*(phi[1:-1,0:-2] + phi[1:-1,2:] + phi[0:-2,1:-1] + phi[2:,1:-1])
	# updating the boundary conditions
	phi[1:-1,0] = phi[1:-1,1] # Updating the left boundary
	phi[1:-1,-1] = phi[1:-1,-2] # Updating the right boundary
	# Updating the top boundary
	phi[0,Nend:] = phi[1,Nend:]
	phi[0,1:Nbegin] = phi[1,1:Nbegin] 
	phi[-1,1:Nbegin] = phi[-2,1:Nbegin]
	# Updating the bottom boundary
	phi[0,Nend:] = phi[1,Nend:]
	phi[-1,Nend:] = phi[-2,Nend:]
	# List of errors
	errors.append(abs(phi-oldphi).max())

xk = arange(0,Niter) # Niter vector
M0 = [1 for i in range(Niter)] # 1 vector
M = c_[M0,xk] 
logA1, B1 = lstsq(M,log(errors))[0] # Least square estimation to find the cofficients for all values of xk
logA2, B2 = lstsq(M[500::],log(errors[500::]))[0]  # Least square estimation to find the cofficients for some values of xk

A1 = exp(logA1) # Calculating A1
y1 = A1*exp(B1*xk) # Calculating y1
A2 = exp(logA2) # Calculating A2
y2 = A2*exp(B2*xk[500:]) # Calculating y2

def plotError():
	title("Evolution of error with iteration") # Setting the title
	legend(("error","fit1","fit2")) # Setting the legend
	xlabel("iteration") # xlabel
	ylabel(r"$log$ error") # y label
	#fit1 = semilogy(xk,y1) # Fit1 curve
	#fit2 = semilogy(xk[500:],y2) # Fit2 curve
	err = semilogy(xk[::50],errors[::50],'ro',xk,y1,xk[500:],y2) # Error Plot
	legend((err),("error","fit1","fit2"))
	show() # Display of plot

plotError() # Calling of function

x = arange(1,Nx+1) # Defining the x axis
y = arange(1,Ny+1) # Defining the y axis
X,Y = meshgrid(x,y) # Making a meshgrid

def plotSurfacePlot():
	fig1 = figure(1) # Assigning a figure
	ax = p3.Axes3D(fig1) 
	title('The 3-D surface plot of the potential') # Setting the title
	surf = ax.plot_surface(Y,X,phi,rstride=1,cstride=1,cmap=cm.jet,linewidth=0,antialiased=False)
	show()

plotSurfacePlot() # Calling the function

def plotContour():
	title('Contour Plot of Potential') # Setting the title
	contour(X,Y,phi) # Contour plot
	show()

plotContour()# Calling of function

def plotVector():
	Jx = zeros((Nx,Ny)) 
	Jy = zeros((Nx,Ny))
	Jx[:,1:-1] = 0.5*(phi[:,0:-2]-phi[:,2:])
	Jy[1:-1,:] = 0.5*(phi[0:-2,:]-phi[2:,:])
	title("The vector plot of current flow") # Setting the title
	quiver(y,x,Jy.transpose(),Jx.transpose()) # Vector Plot
	show()

plotVector()
