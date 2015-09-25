# Importing necessary library
from sys import argv
import re

# Reading in the name of the file
script , filename = argv

# Opening the file
fp = open(filename)

# Declaration of nodes Dictionary
nodes = dict()

# Assigning GND as zero
nodes['GND'] = 0

# Declaring lists for name, node1 , node2 and value
elename = []
elenode1 = []
elenode2 = []
elevalue = []
elevaluenum = []
uniquenodes = []

# Declaring modifier dictionary
mods = {
	'p':1e-12,
	'n':1e-9,
	'u':1e-6,
	'm':1e-3,
	'':1,
	'k':1e3,
	'meg':1e6
} 

# Defining modify function
def modify(str):
	k = re.search("^([+-]?[0-9]*[\.]?[0-9]*)(e[+-]?[0-9]+)?(.*)",str)
	return float(k.groups()[0]) * mods[k.groups()[2]]

# Defining the dictionary for unique nodes
def makeDict(uniquenodes):
	nodeidx = 1
	for i in range(len(uniquenodes)):
		if uniquenodes[i] not in nodes:
			nodes[uniquenodes[i]] = nodeidx
			nodeidx += 1
	return nodes

# Defining the uniquenodes for containing all the uniquenode
def makeUniquenodes(str1,str2):
	if str1 not in uniquenodes:
		uniquenodes.append(str1)
	if str2 not in uniquenodes:
		uniquenodes.append(str2)

# Reading line from the files
for line in fp:
	if ".circuit" in line: # Checking for .circuit keyword in line
		continue
	elif ".end" in line: # Checking for .end keyword in line
		break
	words = line.split() # Splitting the line into words and storing in a list
	elename.append(words[0]) # Adding the name to list elename 
	elenode1.append(words[1]) # Adding node 1 to list elenode1
	elenode2.append(words[2]) # Adding node 2 to list elenode2
	makeUniquenodes(words[1],words[2]) # Adding node 1 and node 2 to the list uniquenodes
	elevalue.append(words[3]) # Adding the value to list elevalue
	elevaluenum.append(modify(words[3])) # Adding the value to list elevaluenum

makeDict(uniquenodes) # Making the dictionary of unique nodes

# Printing the circuit specification
for i in range(len(elename)):
	print "%s %s %s %s" %(elename[i],elenode1[i],elenode2[i],elevalue[i])

# Printing reconstructed matrix
print "Reconstructed listing"
for i in range(len(elename)):
	print "%s %s %s %s" %(elename[i],elenode1[i],elenode2[i],elevaluenum[i])

# Printing the mapping of nodes
print "List of nodes:"
for key, value in sorted(nodes.iteritems(), key=lambda (k,v): (v,k)):
    print "%s: %s" % (value, key)	


