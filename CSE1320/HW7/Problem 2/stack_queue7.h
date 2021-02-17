#ifndef STACK_QUEUE7
#define STACK_QUEUE7
#define MAXSIZE 8;
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

float display(Stack *stack);
float pop(Stack *stack);
float push(Stack *stack);
void addTip(Stack *stack);
void updateTips(Stack *stack, float pay);
float empPay(Stack *stack);

#endif