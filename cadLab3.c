#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 512
#define CHECK "OOOOO"
#include <stdbool.h>

typedef struct Node{
	struct Node *next;
	char name[5];
	char n1[5];
	char n2[5];
	char value[5];
} Node;

typedef struct List{
	Node *head;
	int count;
} List;

List* createListHead(Node *new){
	List *list = malloc(sizeof(List));
	list->head = new;
	list->count = 0;
	return list;
}

Node *createNode(char buf[MAXLENGTH]){
	Node *new = (Node *) malloc(sizeof(Node));
	sscanf(buf,"%s %s %s %s",new->name,new->n1,new->n2,new->value);
	new->next = NULL;
	return new;
}

void initializeArr(char arr[10][5]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<5;j++){
			arr[i][j] = 'O';
		}
	}
}

void initializeConn(int conn[10][10]){
	int i,j;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			conn[i][j] = -1;
		}
	}
}

void add(List *list,Node *node){
    node->next = list->head; // Node points where head points
    list->head = node; // Head points to node
    list->count += 1; // Count of list increased by 1
}

bool findNode(char n[5], char arr[10][5]){
	int i;
	for(i=0;i<10;i++){
		if(strcmp(arr[i],n)){
			return true;
			break;
		}
	}
	return false;
}

void insertNode(char n[5],char arr[10][5]){
	int i = 0;
	while(!strcmp(arr[i],CHECK)){
		i++;
	}
	strcpy(arr[i],n);
}

void createMap(Node *new, char arr[10][5]){
	if(!findNode(new->n1,arr)){
		insertNode(new->n1,arr);
	}
	if(!findNode(new->n2,arr)){
		insertNode(new->n2,arr);
	}
}
int findIndex(char n[5],char arr[10][5]){
	int i,index;
	for(i=0;i<10;i++){
		if(strcmp(arr[i],n)){
			index = i;
			break;
		}
	}
	return index;
}

void makeConnections(int conn[10][10],int index1,int index2){
	int j = 0;
	while(!(conn[index1][j]!=-1)){
		j++;
	}
	conn[index1][j] = index2;
	int k = 0;
	while(!(conn[index2][k]!=-1)){
		k++;
	}
	conn[index2][k] = index1;
}

void createRelation(Node *new,int conn[10][10],char arr[10][5]){
	int index1,index2;
	index1 = findIndex(new->n1,arr);
	index2 = findIndex(new->n2,arr);
	makeConnections(conn,index1,index2);
}

void displayReverse(Node* head){
    Node *temp = head; // temp points where head points
    if(temp==NULL) // If temp points to NULL
        return; // Return nothing
    displayReverse(temp->next); // Recursive call of display
    printf("%s %s %s %s \n",temp->name,temp->n1,temp->n2,temp->value); //Printing the details of node
}
void displayMapping(char arr[10][5]){
	int i=0;
	while(!strcmp(arr[i],CHECK)){
		printf("%d %s\n",i,arr[i]);
		i++;
	}
}
void displayConnections(char arr[10][5],int conn[10][10]){
	int i = 0;
	int k,l;
	while(!strcmp(arr[i],CHECK)){
		i++;
	}
	for(k=0;k<i;k++){
		int j =0;
		while(!(conn[k][j]!=-1)){
			j++;
		}
		printf("%s : ",arr[k]);
		for(l=0;l<j;l++){
			printf("%s ,",arr[(conn[k][l])]);
		}
		printf("\n");
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
	char buf[MAXLENGTH];
	int conn[10][10];
	initializeConn(conn);
	char arr[10][5];
	initializeArr(arr);
	fgets(buf,MAXLENGTH,fp);
	Node *new = createNode(buf);
	createMap(new,arr);
	createRelation(new,conn,arr);
	List *list = createListHead(new);
	while(fgets(buf,MAXLENGTH,fp)){
		Node *new = createNode(buf);
		createMap(new,arr);
		createRelation(new,conn,arr);
		add(list,new);
	}
	Node *head = list->head; 
	displayReverse(head);
	displayMapping(arr);
	displayConnections(arr,conn);
}