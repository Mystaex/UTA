#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Ethan Chase
CSE 1320-001
1001457646
*/

typedef struct order{
    char name[40];
    char payType;
    int itemCount;
    float amount;
    int orderStatus;
}order;

/*This function should read the file (given on the command line) into the appropriate number of order structs.
The size is the number of orders*/
void input_orders(order *o, int size, char*filename){
    FILE *fp;
    char* token;
    char line[100];
    fp = fopen(filename, "r");
    int i = 0;
    for(i = 0; i < size; i++){
        fgets(line, 100, fp);
        token = strtok(line,",");
        strcpy(o[i].name, token);
        token = strtok(NULL, ",");
        o[i].payType = *token;
        token = strtok(NULL,",");
        o[i].itemCount = atoi(token);
        token = strtok(NULL,",");
        o[i].amount = atof(token);
        token = strtok(NULL,",");
        o[i].orderStatus = atoi(token);
    }
}
/*This function should print out all orders from the order structs depending on the status parameter. The size
parameter indicates the number of structs in the array. */
void print_out(int status, order*o, int size){
    int i = 0;
    for(i = 0; i < size; i++){
        if(o[i].orderStatus == status){
            printf("%s\n", o[i].name);
        }
    }
}
/*This function should take the order structs and return the index of the next order to be fulfilled. If all orders
are fulfilled, the function should return -1. */
int pick_next(order *o, int size_order){
    float topAmount = 0;
    int i = 0;
    char c = ' ';
    int topPlace;
    for(i = 0; i < size_order; i++){
        if(o[i].amount > topAmount && o[i].orderStatus == 2){
            topAmount = o[i].amount;
            topPlace = i;
        }
    }
    char fill = ' ';
    printf("Next order to fill: %s\n", o[topPlace].name);
    while(fill != 'n' && fill != 'y'){
        /*Solves my problem with scanf*/
        do{
            c = getchar();
        }while(c != EOF && c != '\n');
        printf("Go ahead and fulfill this order? y or n\n");
        scanf("%c", &fill);
        if(fill == 'n'){
            printf("Not fulfilled.\n");
        }
        else if(fill == 'y'){
            printf("Fulfilled!\n");
            o[topPlace].orderStatus = 1;
        }
        else{
            printf("Not a valid option.\n");
        }
    }
}
/*This function should output all the current information stored in the order structs into the same file that was
read in.*/
void output_file(char*filename, order *o, int size_order){
    FILE *fp;
    fp = fopen(filename, "w");
    int i = 0;
    for(i = 0; i < size_order; i++){
        fprintf(fp,"%s,%c,%d,%f0.2,%d\n",o[i].name, o[i].payType,o[i].itemCount,o[i].amount,o[i].orderStatus);
    }
}

int main(int argc, char **argv){
    int choice = 0;
    int num = atoi(argv[1]);
    order *ord = (order*)malloc(sizeof(order)*num);
    input_orders(ord, num, argv[2]);
    printf("\n***Buongiorno Chef Bartolomeo!***\n");
    while(choice != 3){
        printf("\nWhat to do?\n1. print out orders\n2. pick next order to fulfill\n3. exit\n");
        scanf("%d", &choice);
        while(choice > 3 || choice < 1){
            printf("Not a valid menu choice.\n\n");
            printf("What to do?\n1. print out orders\n2. pick next order to fulfill\n3. exit\n");
            scanf("%d", &choice);
        }
        /*Print out orders*/
        if(choice == 1){
            char input[10];
            int status = 0;
            printf("\nDo you want to see all orders to fill or orders already completed? Type fill or completed\n");
            scanf("%s", input);
            if(!strcmp(input,"fill")){
                printf("Need to fill:\n");
                status = 2;
            }
            else if(!strcmp(input,"completed")){
                printf("Already filled:\n");
                status = 1;
            }
            print_out(status, ord, num);
        }
        /*Pick next order*/
        else if(choice == 2){
            pick_next(ord,num);
        }
    }
    printf("Saving information...Ciao!\n");
    output_file(argv[2],ord,num);
    free(ord);
}