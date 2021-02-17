#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*Ethan Chase
CSE 1320-001
1001457646
EGC7646*/

typedef struct Node{
    char *color; /*color of the light*/
    int **details; /*holds the brightness and size*/
    struct Node* next;
}Node;

/*This	function	takes	the	filename	and	creates	a	linked	list	of	the	string	of	lights.		It	returns	the	head	of	the	
linked	list*/
Node* light_info(char *filename){
    FILE *fp = fopen(filename, "r");

    char *token;
    char line[100];
    Node *head = NULL;
    Node *current = NULL;
    Node *temp = NULL;

    while(!feof(fp)){
        fgets(line,100,fp);
        token = strtok(line,",");
        /*REMEMBER TO DO IF STATEMENTS FOR MALLOC*/
        temp = malloc(sizeof(Node));
        if(temp == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        temp->color = malloc(20);
        if(temp->color == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        strcpy(temp->color,token);
        token = strtok(NULL,",");
        temp->details = malloc(sizeof(int*) * 2);
        int y = 0;
        for(y=0; y<2; y++){
            temp->details[y] = malloc(sizeof(int));
        }
        if(temp->details == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        *(temp->details[0]) = atoi(token);
        token = strtok(NULL,",");
        *(temp->details[1]) = atoi(token);
        temp->next = NULL;

        if(head == NULL){
            current = head = temp;
        }
        else{
            current = current->next = temp;
        }
    }

    return head;
}

/*This function is used to "flip" the light switch
The head node is provided, so that it can run through the linked list.
The status is provided so that it knows to turn the lights on or off.
No return type as the function is used to identify the necessary printing for the lights, and act upon it.
*/
void flip(Node *head, int status){
    Node *temp = head;
    char colorCode = ' ';

    while(temp != NULL){
        if(!strcmp(temp->color,"blue")){
            colorCode = 'b';
        }
        else if(!strcmp(temp->color,"green")){
            colorCode = 'g';
        }
        else if(!strcmp(temp->color,"red")){
            colorCode = 'r';
        }
        else if(!strcmp(temp->color,"yellow")){
            colorCode = 'y';
        }

        if(*(temp->details[1]) == 1){
            colorCode = toupper(colorCode);
        }
        int i = 0;
        for(i = 0; i < *(temp->details[0]); i++){
            if(status == 0){
                printf("-");
            }
            else if(status == 1){
                printf("%c", colorCode);
            }
        }
        temp = temp->next;
        printf(" ");
    }
    printf("\n\n");
}

/*Main function*/
int main(int argc, char **argv){
    char *fileName = argv[1];
    Node *head = light_info(fileName);
    int choice = 1;
    int status = 0;
    while(choice == 1){
        char *line = malloc(10);
        if(line == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        while(strcmp(line,"exit") && strcmp(line,"on") && strcmp(line,"off")){
            fgets(line,10,stdin);
            char *token;
            line = strtok(line,"\n");
        }
        
        if(!strcmp(line,"exit")){
            printf("Exiting...\n");
            choice = 0;
        }
        else if(!strcmp(line,"on")){
            if(status == 0){
                printf("\n**Turning lights on: \n");
                status = 1;
                flip(head,status);
            }
            else{
                printf("\n--Lights are already on.\n");
            }
        }
        else if(!strcmp(line,"off")){
            if(status == 1){
                printf("\n**Turning lights off: \n");
                status = 0;
                flip(head, status);
            }
            else{
                printf("\n--Lights are already off.\n");
            }
        }

        free(line);
    }
    Node *temp = head;
    while(temp != NULL){
        free(temp->details);
        free(temp->color);
        free(temp);
        temp = temp->next;
    }
}