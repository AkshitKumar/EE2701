/* Inclusion of all the header files */
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#define MAXLENGTH 512 // Defining the maximum size of the buffer

/* Declaration of the struct Node to form a doubly linked list*/
typedef struct Node{
	struct Node *prev;
	struct Node *next;
	char n1[10];
	char n2[10];
	char n3[10];
	char n4[10];
	char depname[10];
	char name[10];
	char value[10];
	float valuenum;
} Node;

/* Declaration of global head*/
struct Node* head;

/* Function to create a Node in the linked list depending on the type of element it is */
Node *createNode(char buf[MAXLENGTH]){
	Node *new = (Node *) malloc(sizeof(Node));
	if(buf[0]=='r' || buf[0]=='l' || buf[0]=='c' || buf[0]=='i' || buf[0]=='v' || buf[0]=='R' || buf[0]=='L' || buf[0]=='C' || buf[0]=='I' || buf[0]=='V'){
		sscanf(buf,"%s %s %s %s",new->name,new->n1,new->n2,new->value);
	}
	else if(buf[0]=='e' || buf[0]=='g' || buf[0]=='E'|| buf[0]=='G'){
		sscanf(buf,"%s %s %s %s %s %s",new->name,new->n1,new->n2,new->n3,new->n4,new->value);
	}
	else if(buf[0]=='f' || buf[0]=='h' || buf[0]=='F' || buf[0]=='H'){
		sscanf(buf,"%s %s %s %s %s",new->name,new->n1,new->n2,new->depname,new->value);
	}
	new->prev = NULL;
	new->next = NULL;
	return new;
}

/* Function to add a node to the linked list */
void add(Node *new){
	if(head==NULL){
		head = new;
		return;
	}
	head->prev = new;
	new->next = head;
	head = new;
}

/* Function to initialise all the values of map matrix to "blah" */
void initializeMap(char map[10][10]){
	int i;
	for(i=0;i<10;i++){
		strcpy(map[i],"blah");
	}
}

/*Function to initialise all the value of the connection matrix to -1 */
void initializeConnection(int connection[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			connection[i][j] = -1;
		}
	}	
}

/*Function to initialise all the elements of the mnaMatrix to 0 */
void initializeMNA(double complex mnaMatrix[20][20]){
	int i,j;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			mnaMatrix[i][j] = 0;
		}
	}
}

/* Function to initialise all the values of the variableMatrix to "crap" */
void initializeVariableMatrix(char variableMatrix[20][10]){
	int i;
	for(i=0;i<20;i++){
		strcpy(variableMatrix[i],"crap");
	}
}

/* Function to initialise all the values of the mapVoltageSource to "some" */
void initializeMapVoltageSources(char mapVoltageSources[10][10]){
	int i;
	for(i=0;i<10;i++){
		strcpy(mapVoltageSources[i],"some");
	}
}

/* Function to search for a Node name in the map matrix */
int searchNodeInMap(char n[10],char map[10][10]){
	int i,returnval=0;
	for(i=0;i<10;i++){
		if(strcmp(map[i],n)==0){
			returnval = 1;
		}
	}	
	return returnval;
}

/* Function to search for the index of a node name in the map matrix */
int searchIndexInMap(char n[10],char map[10][10]){
	int i,returnval;
	for(i=0;i<10;i++){
		if(strcmp(map[i],n)==0){
			returnval = i;
			break;
		}
	}
	return returnval;
}

/* Function to insert a Node in the map matrix if it is unique */
void insertNodeInMap(char n[10],char map[10][10]){
	int i=0;
	while(strcmp(map[i],"blah")!=0){
		i++;
	}	
	strcpy(map[i],n);
}

/* Function to create a map for all the unique nodes that are present in the circuit */
void createMap(Node *new, char map[10][10]){
	char c = new->name[0];
	if(c =='r' || c =='l' || c =='c' || c == 'i' || c == 'v' || c == 'R' || c == 'L' || c == 'C' || c == 'I' || c == 'V'){
		if(searchNodeInMap(new->n1,map)!=1){
			insertNodeInMap(new->n1,map);
		}
		if(searchNodeInMap(new->n2,map)!=1){
			insertNodeInMap(new->n2,map);
		}
	}
	else if(c == 'e' || c == 'g' || c == 'E' || c == 'G'){
		if(searchNodeInMap(new->n1,map)!=1){
			insertNodeInMap(new->n1,map);
		}
		if(searchNodeInMap(new->n2,map)!=1){
			insertNodeInMap(new->n2,map);
		}
		if(searchNodeInMap(new->n3,map)!=1){
			insertNodeInMap(new->n3,map);
		}
		if(searchNodeInMap(new->n4,map)!=1){
			insertNodeInMap(new->n4,map);
		}
	}
	else if(c == 'f' || c == 'h' || c == 'F' || c == 'H'){
		if(searchNodeInMap(new->n1,map)){
			insertNodeInMap(new->n1,map);
		}
		if(searchNodeInMap(new->n2,map)){
			insertNodeInMap(new->n2,map);
		}
	}
	
}

/* Function to insert unique voltage sources into mapVolatageSources */
void insertSourcesInMapVoltageSources(char n[10],char mapVoltageSources[10][10]){
	int i=0;
	while(strcmp(mapVoltageSources[i],"some")!=0){
		i++;
	}	
	strcpy(mapVoltageSources[i],n);
}

/* Function to search for the voltage source name in mapVoltageSources matrix */
int searchSourceInMapVoltageSources(char n[10],char mapVoltageSources[10][10]){
	int i,returnval=0;
	for(i=0;i<10;i++){
		if(strcmp(mapVoltageSources[i],n)==0){
			returnval = 1;
		}
	}	
	return returnval;
}

/* Function to create a map for unique voltage sources that are present in the circuit */
void createMapVoltageSources(Node *node, char mapVoltageSources[10][10]){
	char c = node->name[0];
	if(c == 'v' || c == 'V' ){
		if(searchSourceInMapVoltageSources(node->name,mapVoltageSources)!=1){
			insertSourcesInMapVoltageSources(node->name,mapVoltageSources);
		}
	}
}

/* Function to find the number of unique nodes in the circuit */
int findNumUniqueNodes(char map[10][10]){
	int i=0;
	while(strcmp(map[i],"blah")!=0){
		i++;
	}
	return i;
}

/* Function to create the variable matrix which contains the voltage at n-1 nodes and current through k Voltage Sources */
void createVariableMatrix(char mapVoltageSources[10][10],char map2[10][10],char variableMatrix[20][10]){
	int i = 0;
	while(strcmp(map2[i],"blah")!=0){
		strcpy(variableMatrix[i],map2[i]);
		i++;
	}
	int j=i;
	while(strcmp(mapVoltageSources[j-i],"some")!=0){
		strcpy(variableMatrix[j],mapVoltageSources[j-i]);
		j++;
	} 
}

/*Function to find the number of variables in variableMatrix */
int findNumVariableMatrix(char variableMatrix[20][10]){
	int i = 0;
	while(strcmp(variableMatrix[i],"crap")!=0){
		i++;
	}
	return i;
}

/* Function to find the index of a node in the map matrix */
int findIndex(char n[10],char map[10][10]){
	int i;
    int returnval;
    for(i=0;i<20;i++){
        if(strcmp(map[i],n)==0){
            returnval = i;
            break;
        }
    }
    return returnval;
}

/* Function to find the index of a node or current through voltage source in the variableMatrix */
int findIndexV(char n[10],char variableMatrix[20][10]){
	int i;
    int returnval;
    for(i=0;i<20;i++){
        if(strcmp(variableMatrix[i],n)==0){
            returnval = i;
            break;
        }
    }
    return returnval;
}

/* Function to find the index of a node or current through voltage source in the variableMatrix */
int findIndexInVariableMatrix(char n[10],char variableMatrix[20][10]){
	int i;
	int returnval;
	for(i=0;i<20;i++){
		if(strcmp(variableMatrix[i],n)==0){
			returnval = i;
			break;
		}
	}
	return returnval;
}

/* Function to create the MNA Matrix in the case of AC Analysis */
void createConductanceMatrixAC(char map[10][10],char variableMatrix[10][10],Node *head, double complex mnaMatrix[20][20],double complex knownMatrix[20],float w){
	Node *current = head;
	Node *next;
	while(current != NULL){
		char c = current->name[0];
		int index1 = findIndex(current->n1,map);
		int index2 = findIndex(current->n2,map);
		double complex imp;
		if(c=='R' || c=='r'){
			imp = current->valuenum + 0.00 * I;
			mnaMatrix[index1][index1] += 1.0/imp;
			mnaMatrix[index1][index2] -= 1.0/imp;
			mnaMatrix[index2][index1] -= 1.0/imp;
			mnaMatrix[index2][index2] += 1.0/imp;
		}
		else if(c=='L' || c=='l'){
			imp = 0.0 + I*(w*(current->valuenum));
			mnaMatrix[index1][index1] += 1.0/imp;
			mnaMatrix[index1][index2] -= 1.0/imp;
			mnaMatrix[index2][index1] -= 1.0/imp;
			mnaMatrix[index2][index2] += 1.0/imp;
		}
		else if(c=='C' || c=='c'){
			imp = 0.0 - I*(1.0/(w*(current->valuenum)));
			mnaMatrix[index1][index1] += 1.0/imp;
			mnaMatrix[index1][index2] -= 1.0/imp;
			mnaMatrix[index2][index1] -= 1.0/imp;
			mnaMatrix[index2][index2] += 1.0/imp;
		}
		else if(c=='I' || c=='i'){
			knownMatrix[index1] += current->valuenum;
			knownMatrix[index2] -= current->valuenum;
		}
		else if(c=='V' || c=='v'){
			int pos = findIndexInVariableMatrix(current->name,variableMatrix);
			mnaMatrix[index1][pos] += 1.0;
			mnaMatrix[index2][pos] += -1.0;
			mnaMatrix[pos][index1] += 1.0;
			mnaMatrix[pos][index2] += -1.0;
			knownMatrix[pos] += current->valuenum;
		}
		next = current->next;
		current = next;
	}
}

/* Function to create the MNA Matrix for purely resisive circuit in case of the DC Analysis */
void createConductanceMatrixDC(char map[10][10],char variableMatrix[10][10],Node *head, double complex mnaMatrix[20][20],double complex knownMatrix[20]){
	Node *current = head;
	Node *next;
	while(current != NULL){
		char c = current->name[0];
		int index1 = findIndex(current->n1,map);
		int index2 = findIndex(current->n2,map);
		double complex imp;
		if(c=='R' || c=='r'){
			imp = current->valuenum + 0.00 * I;
			mnaMatrix[index1][index1] += 1.0/imp;
			mnaMatrix[index1][index2] -= 1.0/imp;
			mnaMatrix[index2][index1] -= 1.0/imp;
			mnaMatrix[index2][index2] += 1.0/imp;
		}
		else if(c=='L' || c=='l'){
			printf("%s\n"," The circuit consists of inductive elements.You are doing DC Analysis.Please change to purely resistive network.\n" );
			exit(5);
		}
		else if(c=='C' || c=='c'){
			printf("%s\n"," The circuit consists of capacitive elements.You are doing DC Analysis.Please change to purely resistive network.\n" );
			exit(6);
		}
		else if(c=='I' || c=='i'){
			knownMatrix[index1] += current->valuenum;
			knownMatrix[index2] -= current->valuenum;
		}
		else if(c=='V' || c=='v'){
			int pos = findIndexInVariableMatrix(current->name,variableMatrix);
			mnaMatrix[index1][pos] += 1.0;
			mnaMatrix[index2][pos] += -1.0;
			mnaMatrix[pos][index1] += 1.0;
			mnaMatrix[pos][index2] += -1.0;
			knownMatrix[pos] += current->valuenum;
		}
		next = current->next;
		current = next;
	}
}

/* Function to make the cofficients of the GND node to zero in the MNA Matrix */
void makeGNDzero(double complex mnaMatrix[20][20],char map[10][10],char variableMatrix[20][10]){
	int indexGND = findIndex("GND",map);
	int size = findNumVariableMatrix(variableMatrix);
	int i;
	for(i=0;i<size;i++){
		mnaMatrix[i][indexGND] = 0;
		mnaMatrix[indexGND][i] = 0;
	}
	mnaMatrix[indexGND][indexGND] = 1;
}

/* Function to create Connections between different nodes */
void createConnection(Node *new, int connection[10][10],char map[10][10]){
	char c = new->name[0];
	if(c =='r' || c =='l' || c =='c' || c == 'i' || c == 'v' || c == 'R' || c == 'L' || c == 'C' || c == 'I' || c == 'V'){
		int index1 = findIndex(new->n1,map);
		int index2 = findIndex(new->n2,map);
		connection[index1][index2] = 1;
		connection[index2][index1] = 1;
	}
	else if(c == 'e' || c == 'g' || c == 'E' || c == 'G'){
		int index1 = findIndex(new->n1,map);
		int index2 = findIndex(new->n2,map);
		int index3 = findIndex(new->n3,map);
		int index4 = findIndex(new->n4,map);
		connection[index1][index2] = 1;
		connection[index2][index1] = 1;
		connection[index3][index4] = 1;
		connection[index4][index3] = 1;
	}
	else if(c == 'f' || c == 'h' || c == 'F' || c == 'H'){
		int index1 = findIndex(new->n1,map);
		int index2 = findIndex(new->n2,map);
		connection[index1][index2] = 1;
		connection[index2][index1] = 1;
	}

}

/* Function to modify the value of the circuit elements by parsing their value */
void validate(Node *node){
	char expr[10];
	float value;
	int returnval;
	returnval = sscanf(node->value,"%f%s",&value,expr);
	if(returnval==0){
		printf("Incorrect Format : %s\n",node->value);
		exit(4);
	}
	else if(strcmp(expr,"n")==0){
		node->valuenum = value * pow(10,-9);
	}
	else if(strcmp(expr,"u")==0){
		node->valuenum = value * pow(10,-6);
	}
	else if(strcmp(expr,"m")==0){
		node->valuenum = value * pow(10,-3);
	}
	else if(strcmp(expr,"k")==0){
		node->valuenum = value * pow(10,3);
	}
	else if(strcmp(expr,"meg")==0){
		node->valuenum = value * pow(10,6);
	}
	else if(strcmp(expr,"")==0){
		node->valuenum = value;
	}
	else{
		printf("Invalid Unit Usage : %s\n",expr);
		exit(3);
	}
}

/* Function to traverse the linked list to make connections and validate the circuit elements */
void traverse(Node *head,int connection[10][10],char map[10][10]){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		createConnection(current,connection,map);
		validate(current);
		next = current->next;
		current = next;
	}
}

/* Function to traverse the linked list to make mapping of voltage sources */
void traverse2(Node *head,char mapVoltageSources[10][10]){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		createMapVoltageSources(current,mapVoltageSources);
		next = current->next;
		current = next; 
	}
}

/* Function to display the linked list */
void displayLinkedList(Node *head){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		char c = current->name[0];
		if(c =='r' || c =='l' || c =='c' || c == 'i' || c == 'v' || c == 'R' || c == 'L' || c == 'C' || c == 'I' || c == 'V'){
			if(current->valuenum != -1){
				printf("%s %s %s %f\n",current->name,current->n1,current->n2,current->valuenum);
			}
		}
		else if(c == 'e' || c == 'g' || c == 'E' || c == 'G'){
			if(current->valuenum != -1){
				printf("%s %s %s %s %s %f\n",current->name,current->n1,current->n2,current->n3,current->n4,current->valuenum);
			}
		}
		else if(c == 'f' || c == 'h' || c == 'F' || c == 'H'){
			if(current->valuenum != -1){
				printf("%s %s %s %s %f",current->name,current->n1,current->n2,current->depname,current->valuenum);
			}
		}
		next = current->next;
		current = next;
	}
}

/* Function to diplay the MNA matrix */
void displayConductanceMatrix( double complex mnaMatrix[20][20],char variableMatrix[20][10]){
	int length= findNumVariableMatrix(variableMatrix);
	int i,j;
	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			printf("%.2f+i%.2f\t",creal(mnaMatrix[i][j]),cimag(mnaMatrix[i][j]));
		}
		printf("\n");
	}
}

/* Function to display the mapping of unique nodes with an array index */
void displayMapping(char map[10][10]){
	int i = 0;
	while(strcmp(map[i],"blah")!=0){
		printf("%d : %s\n",i,map[i]);
		i++;
	}
}

/* Function to find the node count */
int findNodeCount(char map[10][10]){
	int i = 0;
	while(strcmp(map[i],"blah")!=0){
		i++;
	}
	return i;
}

/* Function to display the various connections between different nodes */
void displayConnections(int connection[10][10],char map[10][10]){
	int i,j;
	int nodecount = findNodeCount(map);
	for(i=0;i<nodecount;i++){
		printf("%s :", map[i]);
		for(j=0;j<nodecount;j++){
			if(connection[i][j]==1){
				printf(" %s", map[j] );
			}
		}
		printf("\n");
	}
}

/* Function to display the variableMatrix */
void displayVariableMatrix(char variableMatrix[20][10]){
	int i=0;
	while(strcmp(variableMatrix[i],"crap")!=0){
		printf("%s\n",variableMatrix[i] );
		i++;
	}
}

/* Function to display the knownMatrix */
void displayKnownMatrix(double complex knownMatrix[20],char variableMatrix[20][10]){
	int i=0; 
	int max = findNumVariableMatrix(variableMatrix);
	for(i=0;i<max;i++){
		printf("%f + i%f\n",creal(knownMatrix[i]),cimag(knownMatrix[i]));
	}
}

/* Function to deallocate the linked list to free the heap memory */
void deallocateMemory(Node *head){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		next = current->next;
		free(current);
		current = next;
	}
	head = NULL;
}

/* Function to perform the Gaussian Elimination  */
void gaussianElimination(double complex mnaMatrix[20][20],char variableMatrix[20][10],double complex knownMatrix[20],double complex results[20]){
	int n = findNumVariableMatrix(variableMatrix);
	int i,j;
	double complex ratio;
	int count;
	/* Perform the Forward Reduction */
	for(i=0;i<(n-1);i++){
		for(j=i+1;j<n;j++){
			ratio = mnaMatrix[j][i]/mnaMatrix[i][i];
			for(count=i;count<n+1;count++){
				mnaMatrix[j][count] -= (ratio * mnaMatrix[i][count]);
			}
			knownMatrix[j] -= (ratio * knownMatrix[i]);
		}
	}
	/* Perform the back substitution */
	results[n-1] = knownMatrix[n-1]/mnaMatrix[n-1][n-1];
	double complex temp;
	for(i=n-2;i>=0;i--){
		temp = knownMatrix[i];
		for(j=i+1;j<n;j++){
			temp -= (mnaMatrix[i][j] * results[j]);
		}
		results[i] = temp/mnaMatrix[i][i];
	}
}

void displayAugmentedMatrix(double complex augMatrix[20][21],char variableMatrix[20][10]){
	int n = findNumVariableMatrix(variableMatrix);
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<=n;j++){
			printf("%f + i%f\t",creal(augMatrix[i][j]),cimag(augMatrix[i][j]));
		}
		printf("\n");
	}
}

/* Function to display the results */
void displayResults(double complex results[20],char variableMatrix[20][10]){
	int n = findNumVariableMatrix(variableMatrix);
	int i;
	for(i=0;i<n;i++){
		printf("%f + i%f\n",creal(results[i]),cimag(results[i]));
	}
}

/* Function to do the DC Analysis for the circuit */
void dcAnalysis(char buf[MAXLENGTH],Node *head, char mapVoltageSources[10][10],char map[10][10],double complex mnaMatrix[20][20],double complex results[20],double complex knownMatrix[20],char variableMatrix[20][10],int connection[10][10]){
	char mode[5];
	char name[5];
	float vmax,vmin,vstep;
	sscanf(buf,"%s %s %f %f %f",mode,name,&vmin,&vmax,&vstep);
	FILE *fout = fopen("spice.out","w+");
	while(vmin<=vmax){
		traverse(head,connection,map);
		Node *current = head;
		Node *next;
		while(current!=NULL){
			if(strcmp(name,current->name)==0){
				current->valuenum = vmin;
			}
			next = current->next;
			current = next;
		}
		traverse2(head,mapVoltageSources);
		createVariableMatrix(mapVoltageSources,map,variableMatrix); 
		double complex knownMatrix[20] = {0};
		double complex mnaMatrix[20][20] = {0};
		createConductanceMatrixDC(map,variableMatrix,head,mnaMatrix,knownMatrix); 
		makeGNDzero(mnaMatrix,map,variableMatrix);
		gaussianElimination(mnaMatrix,variableMatrix,knownMatrix,results);
		displayResults(results,variableMatrix);
		vmin = vmin + vstep;
		int n = findNumVariableMatrix(variableMatrix);
		int i;
		for(i=0;i<n;i++){
			fprintf(fout,"%f + i%f\t",creal(results[i]),cimag(results[i]));
		}
		fprintf(fout,"\n");
	} 
	fclose(fout);
}

/*Function to do the AC analysis for the circuit */
void acAnalysis(char buf[MAXLENGTH],Node *head, char mapVoltageSources[10][10],char map[10][10],double complex mnaMatrix[20][20],double complex results[20],double complex knownMatrix[20],char variableMatrix[20][10],int connection[10][10]){
	char mode[5];
	char name[5];
	float f_min,f_max,n;
	sscanf(buf,"%s %s %f %f %f",mode,name,&f_min,&f_max,&n);
	FILE *fout = fopen("spice.out","w+");
	float lf_min = log(f_min);
	float lf_max = log(f_max);
	float lstep = log(10)/n;
	while(lf_min<=lf_max){
		float w = exp(lf_min)*2*3.14;
		traverse(head,connection,map);
		traverse2(head,mapVoltageSources);
		createVariableMatrix(mapVoltageSources,map,variableMatrix); 
		double complex knownMatrix[20] = {0};
		double complex mnaMatrix[20][20] = {0};
		createConductanceMatrixAC(map,variableMatrix,head,mnaMatrix,knownMatrix,w); 
		makeGNDzero(mnaMatrix,map,variableMatrix);
		gaussianElimination(mnaMatrix,variableMatrix,knownMatrix,results);
		lf_min = lf_min + lstep;
		int n = findNumVariableMatrix(variableMatrix);
		int i;
		for(i=0;i<n;i++){
			fprintf(fout,"%farg(%f)\t",cabs(results[i]),carg(results[i]));
		}
		fprintf(fout,"\n");
	}

}

int main(int argc,char **argv){
	if(argc!=2){
		printf("%s\n","Usage ./a.out <filename>");
		exit(1);
	}
	FILE *fp = fopen(argv[1],"r");
	if(fp==NULL){
		printf("%s\n","File could not be opened");
		exit(2);
	}
	/* Declaration & Initialization of matrices we make use of for analysis */
	char buf[MAXLENGTH];
	char map[10][10];
	initializeMap(map);
	int connection[10][10];
	initializeConnection(connection);
	char mapVoltageSources[10][10];
	initializeMapVoltageSources(mapVoltageSources);
	double complex mnaMatrix[20][20];
	double complex augMatrix[20][21] = {0};
	initializeMNA(mnaMatrix);
	char variableMatrix[20][10];
	initializeVariableMatrix(variableMatrix);
	double complex knownMatrix[20] = {0};
	int flag = 0;
	double complex results[20] = {0};
	while(fgets(buf,MAXLENGTH,fp)){
		/* Check for ".circuit" */
		if(buf[0]=='.' && strcmp(buf,".circuit\n")==0){
			flag = 1;
			continue;
		}
		/* Check for ".command" */
		if(buf[0]=='.' && strcmp(buf,".command\n")==0){
			flag = 2;
			continue;
		}
		/* Check for ".end" */
		if(buf[0]=='.' && strcmp(buf,".end\n")==0){
			flag = 0;
			continue;
		}
		/* Enter the ".circuit" mode */
		if(flag==1){
        	Node *new = createNode(buf);
        	createMap(new,map);
        	add(new);
        }
        /* Enter the ".command" mode */
        if(flag==2){
        	char mode[5],name[5];
        	float vmin,vmax,vstep;
        	sscanf(buf,"%s %s %f %f %f",mode,name,&vmin,&vmax,&vstep);
        	if(strcmp(mode,"dc")==0){
        		dcAnalysis(buf,head,mapVoltageSources,map,mnaMatrix,results,knownMatrix,variableMatrix,connection);
        	}
        	else if(strcmp(mode,"ac")==0){
        		acAnalysis(buf,head,mapVoltageSources,map,mnaMatrix,results,knownMatrix,variableMatrix,connection);
        	}
        }
	}
	deallocateMemory(head);
	return 0;
}