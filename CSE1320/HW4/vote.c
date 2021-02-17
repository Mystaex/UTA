#include <stdio.h>
#include <string.h>
/*
Ethan Chase
CSE 1320-001
1001457646
*/
/*This function takes a file pointer, goes through the file and prints the file contents to screen. It returns the
number of lines in the file*/
int registered(FILE *fp){
    int lineCount = 0;
    char line[100];
    printf("\n***Registered so far:***\n");
    fgets(line,100,fp); 
    /* Adds outputs the name from the file to the console*/
    while(!feof(fp)){    
        lineCount++; 
        printf("%d. %s",lineCount, line);
        fgets(line,100,fp);  
    }
    printf("\n");

    return lineCount;
}

/*This function takes a file pointer and adds a new line to the file*/
void new_register(FILE *fp){
    char name[100];
    printf("Enter name: ");
    fgets(name,100,stdin);
    printf("Adding: %s\n", name);
    fprintf(fp, "%s", name);
}

int main(int argc, char **argv){
    FILE *fp;
    int askTotal = 0, askCount = 1, regCount = 0;
    char c = ' ';
    fp = fopen(argv[1],"r");
    regCount = registered(fp);
    fclose(fp);
    printf("How many people to ask right now?\n");
    scanf("%d", &askTotal);
    /*Solves my problem with going from scanf to fgets*/
    do{
        c = getchar();
    }while(c != EOF && c != '\n');
    /*Asks the amount of people requested*/
    while(askCount < (askTotal + 1)){
        char input[5];
        printf("-Person %d: Would you like to register to vote?\n", askCount);
        fgets(input,5,stdin);
        if(!strcmp(input,"y\n")){
            fp = fopen(argv[1],"a");
            new_register(fp);
            fclose(fp);
            fp = fopen(argv[1],"r");
            regCount = registered(fp);
            fclose(fp);
        }
        else if(!strcmp(input,"n\n")){
            printf("Ok.\n");
        }
        askCount++;
    }
    printf("%d people asked! Taking a break.\n", askCount-1);
}