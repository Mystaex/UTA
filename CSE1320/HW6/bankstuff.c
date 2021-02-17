#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Ethan Chase
EGC7646 | 1001457646
CSE 1320-001
*/
typedef struct account{
    char **user_name; /*first name, last name*/
    char *bank_name; /*bank name*/
    int num_accounts; /*number of accounts*/
    int **account_numbers; /*all 6 digits, can have multiple accounts-checking, saving*/
    float **total_in_account; /*amount in each account*/
    struct account *next;
}Account;

/*This function is designed to read from the given file and return the head of the linked list it creates*/
Account *read_file(int size, char *filename){
    FILE *fp = fopen(filename,"r");
    int i = 0;
    Account *temp = NULL;
    Account *current = NULL;
    Account *head = NULL;
    char *token;
    char *line = malloc(100);

    for(i = 0; i<size; i++){
        fgets(line,100,fp);
        line = strtok(line,"\n");
        temp = malloc(sizeof(Account));
        if(temp == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        temp->user_name = malloc(40);
        if(temp->user_name == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        *(temp->user_name) = malloc(40);
        if(*(temp->user_name) == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        strcpy(*(temp->user_name),strtok(line,","));
        temp->bank_name = malloc(30);
        if(temp->bank_name == NULL){
            printf("No memory allocated\n");
            exit(EXIT_FAILURE);
        }
        strcpy(temp->bank_name,strtok(NULL,","));
        temp->num_accounts = atoi(strtok(NULL,","));
        int z = 0;
        temp->total_in_account = malloc(sizeof(float*) * temp->num_accounts);
        temp->account_numbers = malloc(sizeof(int*) * temp->num_accounts);
        for(z = 0; z < temp->num_accounts; z++){
            temp->account_numbers[z] = malloc(sizeof(int));
            temp->total_in_account[z] = malloc(sizeof(float));
        }
        int x = 0;
        int y = 0;
        for(x = 0; x < temp->num_accounts; x++){
            *(temp->account_numbers[x]) = atoi(strtok(NULL,","));
        }
        for(y = 0; y < temp->num_accounts; y++){
            *(temp->total_in_account[y]) = atof(strtok(NULL,","));
        }

        temp->next = NULL;
        if(head == NULL){
            current = head = temp;
        }
        else{
            current = current->next = temp;
        }
    }
    free(line);

    return head;
}

/*This function is used to transfer money between accounts. The head is needed to cycle through the list, the target and actor are needed to know who the transaction is between
and amount and size are to know the transfer amount and size of the list*/
int transfer(Account *head, char *target, char *actor, float amount, int size){
    Account *targetNode = NULL;
    Account *actorNode = NULL;
    Account *current = head;
    float transFee = 1;
    int acc = 0;
    int i = 0;
    /*Cycles through linked list looking for actor and target*/
    for(i = 0; i < size; i++){
        if(!strcmp(*(current->user_name),target)){
            targetNode = current;
        }
        else if(!strcmp(*(current->user_name),actor)){
            actorNode = current;
        }
        current = current->next;
    }

    /*Operation if the actor has more than just a checking account*/
    if(actorNode->num_accounts > 1){
        char *input = malloc(20);
        while(strcmp(input,"savings") && strcmp(input,"checking")){
            printf("From which account? ");
            fgets(input,20,stdin);
            input = strtok(input,"\n");
            if(strcmp(input,"savings") && strcmp(input,"checking")){
                printf("*Not a valid option. Please try either checking or savings.\n");
            }
        }
        if(!strcmp(input,"savings")){
            acc = 1;
        }
        else if(!strcmp(input,"checking")){
            acc = 0;
        }
        free(input);
    }

    /*Operation if the banks of the 2 account holders are different*/
    if(strcmp(actorNode->bank_name,targetNode->bank_name) != 0){
        char input;
        input = 't';
        while(input != 'y' && input != 'n'){
            printf("Recipient is in a different bank. You will be charges a 5%% transaction fee. Continue? y or n\n");
            input = getchar();
            getchar();
            if(input != 'y' && input != 'n'){
                printf("*Not a valid response. Please try again.*\n");
            }
        }
        if(input == 'n'){
            return 0;
        }
        else if(input == 'y'){
            transFee = 1.05;
        }
    }

    /*Actual money transfer section*/
    if(*(actorNode->total_in_account[acc]) > (amount*transFee + 5)){
        printf("\nBefore transfer: $%0.2f\n",*(actorNode->total_in_account[acc]));
        *(actorNode->total_in_account[acc]) -= (amount * transFee);
        printf("After transfer: $%0.2f\n",*(actorNode->total_in_account[acc]));
        *(targetNode->total_in_account[0]) = *(targetNode->total_in_account[0]) + amount;
        return 1;
    }
    else{
        printf("Sorry, you do not have sufficient funds to make this transfer. ");
        return 0;
    }
}

/*Used to ensure that the names entered are names of account holders*/
int nameCheck(Account *head, char *name, int size){
    int i = 0;
    int match = 0;
    Account *current = head;
    for(i = 0; i < size; i++){
        if(!strcmp(*(current->user_name),name)){
            match = 1;
        }
        current = current->next;
    }
    if(!match){
        printf("\n*Not a valid name. Please try again.*\n");
    }
    return match;
}

int main(int argc, char **argv){
    Account *head;
    int size = atoi(argv[1]);
    char *filename = argv[2];
    head = read_file(size,filename);
    int cont = 1;
    char *line = malloc(sizeof(char) * 40);
    if(line == NULL){
        printf("No memory allocated\n");
        exit(EXIT_FAILURE);
    }
    char **name = malloc(80);
    if(name == NULL){
        printf("No memory allocated\n");
        exit(EXIT_FAILURE);
    }
    name[0] = malloc(40);
    if(name[0] == NULL){
        printf("No memory allocated\n");
        exit(EXIT_FAILURE);
    }
    name[1] = malloc(40);
    if(name[1] == NULL){
        printf("No memory allocated\n");
        exit(EXIT_FAILURE);
    }
    char *transTo = malloc(40);
    if(transTo == NULL){
        printf("No memory allocated\n");
        exit(EXIT_FAILURE);
    }
    char *input = malloc(20);
    if(input == NULL){
        printf("No memory allocated\n");
        exit(EXIT_FAILURE);
    }
    /*Continues as long as the user does not type "exit program" for the first and last name*/
    while(cont){
        int session = 0;
        float trans = 0;
        int firstMatch = 0;
        int secMatch = 0;

        printf("******************************************************************\n***Welcome to Money Transfer-Voted the Best 10 Years in a Row!***\n******************************************************************\n");
        while(!firstMatch){
            printf("Enter your first and last name: ");
            fgets(line,40,stdin);
            name[0] = strtok(line, "\n");
            if(!strcmp(name[0],"exit program")){
                firstMatch = 1;
                secMatch = 1;
                cont = 0;
                printf("Exiting...\n");
            }
            else{
                firstMatch = nameCheck(head,name[0],size);
            }
        }

        /*recipient name and ensuring the name is from the linked list*/
        while(!secMatch){
            printf("\nWho do you want to transfer money to? ");
            fgets(transTo,40,stdin);
            name[1] = strtok(transTo,"\n");
            secMatch = nameCheck(head,name[1],size);
        }
        if(cont){
            printf("\nHow much money would you like to transfer? $");
            fgets(input,20,stdin);
            input = strtok(input,"\n");

            trans = atof(input);

            session = transfer(head,name[1],name[0],trans,size);
            if(!session){
                printf("Ending session...\n\n");
            }
            else{
                printf("Transfer successfully completed.\n\n");
            }
        }
    }
    free(name[0]);
    free(name[1]);
    free(input);
    free(transTo);
    free(name);
    free(line);
}