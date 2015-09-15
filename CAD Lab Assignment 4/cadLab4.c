#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#define freq 50
#define MAXLENGTH 512

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

struct Node* head;

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

void add(Node *new){
	if(head==NULL){
		head = new;
		return;
	}
	head->prev = new;
	new->next = head;
	head = new;
}

void initializeMap(char map[10][10]){
	int i;
	for(i=0;i<10;i++){
		strcpy(map[i],"blah");
	}
}

void initializeConnection(int connection[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			connection[i][j] = -1;
		}
	}	
}

void initializeMNA(double complex mnaMatrix[20][20]){
	int i,j;
	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			mnaMatrix[i][j] = 0;
		}
	}
}
void initializeVariableMatrix(char variableMatrix[20][10]){
	int i;
	for(i=0;i<20;i++){
		strcpy(variableMatrix[i],"crap");
	}
}
void initializeMapVoltageSources(char mapVoltageSources[10][10]){
	int i;
	for(i=0;i<10;i++){
		strcpy(mapVoltageSources[i],"some");
	}
}

int searchNodeInMap(char n[10],char map[10][10]){
	int i,returnval=0;
	for(i=0;i<10;i++){
		if(strcmp(map[i],n)==0){
			returnval = 1;
		}
	}	
	return returnval;
}


void insertNodeInMap(char n[10],char map[10][10]){
	int i=0;
	while(strcmp(map[i],"blah")!=0){
		i++;
	}	
	strcpy(map[i],n);
}

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


void insertSourcesInMapVoltageSources(char n[10],char mapVoltageSources[10][10]){
	int i=0;
	while(strcmp(mapVoltageSources[i],"some")!=0){
		i++;
	}	
	strcpy(mapVoltageSources[i],n);
}

int searchSourceInMapVoltageSources(char n[10],char mapVoltageSources[10][10]){
	int i,returnval=0;
	for(i=0;i<10;i++){
		if(strcmp(mapVoltageSources[i],n)==0){
			returnval = 1;
		}
	}	
	return returnval;
}

void createMapVoltageSources(Node *node, char mapVoltageSources[10][10]){
	char c = node->name[0];
	if(c == 'v' || c == 'V' ){
		if(searchSourceInMapVoltageSources(node->name,mapVoltageSources)!=1){
			insertSourcesInMapVoltageSources(node->name,mapVoltageSources);
		}
	}
}

int findNumUniqueNodes(char map[10][10]){
	int i=0;
	while(strcmp(map[i],"blah")!=0){
		i++;
	}
	return i;
}

void createVariableMatrix(char mapVoltageSources[10][10],char map[10][10],char variableMatrix[20][10]){
	int i = 0;
	while(strcmp(map[i],"blah")!=0){
		strcpy(variableMatrix[i],map[i]);
		i++;
	}
	/* i = findNumUniqueNodes(map); */
	int j=i;
	while(strcmp(mapVoltageSources[j-i],"some")!=0){
		strcpy(variableMatrix[j],mapVoltageSources[j-i]);
		j++;
	} 
}

int findNumVariableMatrix(char variableMatrix[20][10]){
	int i = 0;
	while(strcmp(variableMatrix[i],"crap")!=0){
		i++;
	}
	return i;
}

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

void createConductanceMatrix(char map[10][10],char variableMatrix[10][10],Node *head, double complex mnaMatrix[20][20],int knownMatrix[20]){
	// int variables = findNumVariableMatrix(variableMatrix);
	Node *current = head;
	Node *next;
	while(current != NULL){
		char c = current->name[0];
		if(c == 'R' || c == 'r'){
			int index1 = findIndex(current->n1,map);
			int index2 = findIndex(current->n2,map);
			mnaMatrix[index1][index1] += 1/(current->valuenum);
			mnaMatrix[index1][index2] -= 1/(current->valuenum);
			mnaMatrix[index2][index1] -= 1/(current->valuenum);
			mnaMatrix[index2][index2] += 1/(current->valuenum);
		}
		else if(c == 'L' || c == 'l'){
			int index1 = findIndex(current->n1,map);
			int index2 = findIndex(current->n2,map);
			mnaMatrix[index1][index1] += (-1*I*(1/(freq*current->valuenum)));
			mnaMatrix[index1][index2] -= (-1*I*(1/(freq*current->valuenum)));
			mnaMatrix[index2][index1] -= (-1*I*(1/(freq*current->valuenum)));
			mnaMatrix[index2][index2] += (-1*I*(1/(freq*current->valuenum)));
		}
		else if(c == 'C' || c == 'c'){
			int index1 = findIndex(current->n1,map);
			int index2 = findIndex(current->n2,map);
			mnaMatrix[index1][index1] += (-1*I*(freq*current->valuenum));
			mnaMatrix[index1][index2] -= (-1*I*(freq*current->valuenum));
			mnaMatrix[index2][index1] -= (-1*I*(freq*current->valuenum));
			mnaMatrix[index2][index2] += (-1*I*(freq*current->valuenum));
		}
		else if(c == 'I' || c == 'i'){
			int index1 = findIndex(current->n1,map);
			int index2 = findIndex(current->n2,map);
			mnaMatrix[index1][index1] += 0;
			mnaMatrix[index1][index2] += 0;
			mnaMatrix[index2][index1] += 0;
			mnaMatrix[index2][index2] += 0;
			knownMatrix[index1] -= 1;
			knownMatrix[index2] += 1;
		}
		else if(c == 'V' || c == 'v'){
			int index1 = findIndex(current->n1,map);
			int index2 = findIndex(current->n2,map);
			char checkstr[10];
			/* strcpy(checkstr,strcat("I",current->name)); */
			strcpy(checkstr,current->name);
			int pos = findIndexInVariableMatrix(checkstr,variableMatrix);
			mnaMatrix[index1][index1] += 0;
			mnaMatrix[index1][index2] += 0;
			mnaMatrix[index1][pos] += 1;
			mnaMatrix[index2][index1] += 0;
			mnaMatrix[index2][index2] += 0;
			mnaMatrix[index2][pos] -= 1;
			mnaMatrix[pos][index1] += 1;
			mnaMatrix[pos][index2] -= 1;
			mnaMatrix[pos][pos] += 0;
			knownMatrix[index1] += 0;
			knownMatrix[index2] += 0;
			knownMatrix[pos] += current->valuenum;
		} 
		next = current->next;
		current = next;
	}
}

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

void validate(Node *node){
	char expr[10];
	float value;
	sscanf(node->value,"%f%s",&value,expr);
	if(strcmp(expr,"n")==0){
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

void traverse(Node *head,int connection[10][10],char map[10][10]){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		createConnection(current,connection,map);
		validate(current);
		//createMapVoltageSources(current,mapVoltageSources);
		next = current->next;
		current = next;
	}
}
void traverse2(Node *head,char mapVoltageSources[10][10]){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		createMapVoltageSources(current,mapVoltageSources);
		next = current->next;
		current = next; 
	}
}

void displayLinkedList(Node *head){
	Node *current = head;
	Node *next;
	while(current!=NULL){
		char c = current->name[0];
		if(c =='r' || c =='l' || c =='c' || c == 'i' || c == 'v' || c == 'R' || c == 'L' || c == 'C' || c == 'I' || c == 'V'){
			if(current->valuenum != -1){
				printf("%s %s %s %f\n",current->name,current->n1,current->n2,current->valuenum);
			}
			/* else{
				printf("%s %s %s %s\n",current->name,current->n1,current->n2,current->value);
			} */
		}
		else if(c == 'e' || c == 'g' || c == 'E' || c == 'G'){
			if(current->valuenum != -1){
				printf("%s %s %s %s %s %f\n",current->name,current->n1,current->n2,current->n3,current->n4,current->valuenum);
			}
			/* else {
				printf("%s %s %s %s %s %s\n",current->name,current->n1,current->n2,current->n3,current->n4,current->value);
			} */
		}
		else if(c == 'f' || c == 'h' || c == 'F' || c == 'H'){
			if(current->valuenum != -1){
				printf("%s %s %s %s %f",current->name,current->n1,current->n2,current->depname,current->valuenum);
			}
			/* else{
				printf("%s %s %s %s %s",current->name,current->n1,current->n2,current->depname,current->value);
			} */
		}
		next = current->next;
		current = next;
	}
}

void displayConductanceMatrix( double complex mnaMatrix[20][20],char variableMatrix[20][10]){
	int length= findNumVariableMatrix(variableMatrix);
	/*while(strcmp(variableMatrix[length],"blah")!=0){
		length++;
	}*/
	int i,j;
	for(i=0;i<length;i++){
		for(j=0;j<length;j++){
			printf("%.2f+i%.2f\t",creal(mnaMatrix[i][j]),cimag(mnaMatrix[i][j]));
		}
		printf("\n");
	}
}

void displayMapping(char map[10][10]){
	int i = 0;
	while(strcmp(map[i],"blah")!=0){
		printf("%d : %s\n",i,map[i]);
		i++;
	}
}
int findNodeCount(char map[10][10]){
	int i = 0;
	while(strcmp(map[i],"blah")!=0){
		i++;
	}
	return i;
}
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

void displayVariableMatrix(char variableMatrix[20][10]){
	int i=0;
	while(strcmp(variableMatrix[i],"crap")!=0){
		printf("%s\n",variableMatrix[i] );
		i++;
	}
}

void displayKnownMatrix(int knownMatrix[20],char variableMatrix[20][10]){
	int i=0; 
	int max = findNumVariableMatrix(variableMatrix);
	for(i=0;i<max;i++){
		printf("%d\n",knownMatrix[i]);
	}
}

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
	char buf[MAXLENGTH];
	char map[10][10];
	initializeMap(map);
	int connection[10][10];
	initializeConnection(connection);
	char mapVoltageSources[10][10];
	initializeMapVoltageSources(mapVoltageSources);
	double complex mnaMatrix[20][20];
	initializeMNA(mnaMatrix);
	char variableMatrix[20][10];
	initializeVariableMatrix(variableMatrix);
	int knownMatrix[20] = {0};
	int flag = 0;
	while(fgets(buf,MAXLENGTH,fp)){
		if(buf[0]=='.' && strcmp(buf,".circuit\n")==0){
			flag = 1;
			continue;
		}
		else if(buf[0]=='.' && strcmp(buf,".end\n")==0){
			flag = 0;
		}
		if(flag==1){
        	Node *new = createNode(buf);
        	createMap(new,map);
        	add(new);
        }
	}
	traverse(head,connection,map);
	traverse2(head,mapVoltageSources);
	createVariableMatrix(mapVoltageSources,map,variableMatrix); 
	createConductanceMatrix(map,variableMatrix,head,mnaMatrix,knownMatrix); 
	displayLinkedList(head);
	printf("\n");
	displayMapping(map);
	printf("\n");
	displayConnections(connection,map);
	printf("\n");
	printf("%s\n","The Conductance Matrix:");
	displayConductanceMatrix(mnaMatrix,variableMatrix); 
	printf("%s\n","The Variable Matrix:");
	displayVariableMatrix(variableMatrix);
	printf("%s\n","The Known Matrix:");
	displayKnownMatrix(knownMatrix,variableMatrix);
	deallocateMemory(head);
	return 0;
}