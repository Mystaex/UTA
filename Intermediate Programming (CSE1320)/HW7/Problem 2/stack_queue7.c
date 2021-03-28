#include "stack_queue7.h"
#include <stdio.h>
#define MAXSIZE 8
/*
Ethan Chase
CSE 1320-001
EGC7646 | 1001457646
*/
struct stack{
    float stk[MAXSIZE];
    int top;
};
typedef struct stack Stack;

float display(Stack *stack){
    int i;
    if(stack->top == -1){
        printf("Stack is empty\n");
        return;
    }
    else{
        for(i=stack->top;i>=0;i--){
            printf("Enter tip: $%0.2f\n",stack->stk[i]);
        }
    }
}
/*Deletes an element from the stack*/
float pop(Stack *stack){
    float num;
    if(stack->top == -1){
        printf("Stack is Empty\n");
        return(stack->top);
    }
    else{
        num = stack->stk[stack->top];
        stack->top = stack->top-1;
    }
    return(num);
}
float push(Stack *stack){
    float num;
    char input[40];
    if(stack->top == (MAXSIZE -1)){
        printf("Stack is full\n");
        return;
    }
    else{
        printf("Enter tip: $");
        fgets(input,20,stdin);
        if(strcmp(input,"done\n")){
            return -60;
        }
        else if(atof(input) > 0){
            num = atof(input);
        }
        stack->top = stack->top+1;
        stack->stk[stack->top] = num;
    }
}


void addTips(Stack *stack){
    printf("***Tip Jar***\n");
    int i = 0;
    for(i = 0; i < MAXSIZE; i++){
        float num = 0;
        num = push(stack);
        if(num == -60){
            return;
        }
    }
}

void updateTips(Stack *stack, float pay){
    printf("***Tip Jar (Updated)***\n");
    float num = 0;
    float dif = 0;
    while(num < pay){
        num += push(stack);
    }
    dif = num-pay;
    display(stack);
    if(dif > 0){
        printf("Enter tip: $0.2f\n",dif);
    }
}

float empPay(Stack *stack){
    float hours = 0;
    float pay = 0;
    char input[40];
    while(atof(input) <= 0){
        printf("Hello, how many hours did you work? ");
        fgets(input,40,stdin);
        if(atof(input) <= 0){
            printf("Not a valid input. Please enter a value greater than 0.\n");
        }
    }
    hours = atof(input);
    pay = hours*2;
    printf("Ok, giving you $%0.2f.\n",pay);

    updateTips(stack,pay);
}