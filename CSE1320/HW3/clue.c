#include <stdio.h>
#include <string.h>
/*
Ethan Chase | 1001457656
CSE 1320-001
*/

/*This function finds a suspect and adds a meeting to that suspects record if the suspect is found*/
int meet_with_suspect(char** suspects, int* meet, char* name){
    int selection = 0;
    int i;
    int result = 0;
    /*Loop to run through suspect list checking for matches*/
    for(i = 0; i < 3; i++){
        if(!strcmp(name, suspects[i])){
            meet[i]++;
            selection = 1;
        }
    }
    /*What happens if the suspect is not found*/
    if(!selection){
        printf("Suspect not found.\n");

    }
    else{
        printf("Suspect found. Adding meeting.\n");
    }
        char input[3];
        printf("--Would you like to continue meeting?");
        fgets(input,100,stdin);
        strtok(input,"\n");
        if(!strcmp(input,"yes")){
            result = 1;
        }
    return result;
}

/*Main*/
int main (int argc, char **argv){
    char* all_suspects[]={"Mustard", "Scarlet","Plum"};
    int meet[3]={0};
    char name[100];
    int check=1;
    while(check){
        printf("\n***Enter a suspect's name: ");
        fgets(name,100,stdin);
        strtok(name,"\n");
        if(!strcmp(name,"exit")){
            check=0;
        }
        else{
            check=meet_with_suspect(all_suspects,meet,name);
        }
    }
    printf("Total meets for Mustard: %d\n",meet[0]);
    printf("Total meets for Scarlet: %d\n",meet[1]);
    printf("Total meets for Plum: %d\n",meet[2]);
}