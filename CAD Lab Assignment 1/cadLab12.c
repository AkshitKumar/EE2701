#include<stdio.h> // Library File Access 
#include<stdlib.h> // Library File Access 
#define MAXLENGTH 512 //Defining the MAXLENGTH of string to be taken
/* main() function takes argument from Command Line */
int main(int argc, char **argv){
        /*Program expects a filename. Check that argument was passed */
        if(argc!=2){
                printf("Usage ./a.out <filename>");
                exit(1);
        }
        /* Open file while checking for existence */
        FILE *fp = fopen(argv[1],"r");
        if(fp==NULL){
                printf("File could not be opened");
                exit(2);
        }
        /* Read in lines from file and process. Note the use of fgets() which is */
        /* more secure than gets() */
        char buf[MAXLENGTH]; // Declaring the array buf in which the file stream will be stored
        int lengthFreq[11] = {0}; // Declaring array lenfreq to hold counting information and initialising to 0 
        while(fgets(buf,MAXLENGTH,fp)){
                int count = 0,i=0; // Initialising iteration and counter variable
                char *ptr; // Declaration of a pointer ptr
                ptr = buf; // ptr points to the addr    ess of buf[0]
                while(*ptr!='\0'){
                        /* Checking for word separators like ' ','\t',',' and end of buf array */
                        if(*ptr==' ' || *ptr==',' || *ptr==':' || *ptr=='\t' || *ptr==';' || *(ptr+1)=='\0'){
                                lengthFreq[count]++;
                                count = 0;
                        }
                        else{
                                /* Checking for the alphabet */
                                if((*ptr>='A' && *ptr<='Z') || (*ptr>='a' && *ptr<='z')){
                                        count++;
                                }
                        }
                        ptr++;
                }
        }
        /* Printing out the result of the analysis */
        int k;
        for(k=3;k<=10;k++){
                printf("%d Letter Words: %d\n",k,lengthFreq[k]);
        }
        /* Printing of the horizontal histogram */
        printf("\n");
        /* Printing the line for 10 separately */
        printf("10|");
        for(j=0;j<lengthFreq[10];j++){
                        printf(" * ");
                        }
                printf("\n");
        /* Nested loop to print the frequency of different word lengths */
        for(k=9;k>=1;k--){
                printf("%d | ",k);
                for(j=0;j<lengthFreq[k];j++){
                        printf("* ");
                        }
                printf("\n");
        }
        printf("0 +---------------------------------- \n");
        return 0;
}