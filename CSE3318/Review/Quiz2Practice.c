#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *next;
};
typedef struct node *nodePT;

nodePT list_from_arary(int N, int A[]){

    int i; 		
	nodePT prev;
	nodePT L = (nodePT)malloc(sizeof(struct node));
    L->data = 0;
    L->next = NULL;
	
	prev = L;
	for (i = 0; i < N; i++) {
        nodePT temp = (nodePT)malloc(sizeof(struct node));
        temp->data = A[i];
        temp->next = prev->next;
        prev->next = temp;
		prev = temp;
	}	
	return L;
}

nodePT list_from_list(nodePT L){
    nodePT L2 = (nodePT)malloc(sizeof(struct node));
    L2->data = 0;
    L2->next = NULL;

    nodePT current2 = L2;
    nodePT current = L->next;

    while(current != NULL){
        nodePT temp = (nodePT)malloc(sizeof(struct node));
        temp->data = current->data;
        current2->next = temp;
        current2 = current2->next;
        current = current->next;
    }

    return L2;
}

void delete(nodePT L){
    nodePT next;
	nodePT current = L;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    } 
}

void reverse(nodePT L) 
{ 
    struct node* prev = NULL; 
    struct node* current = &L; 
    struct node* next = NULL; 
    while (current != NULL) { 
        // Store next 
        next = current->next; 
  
        // Reverse current node's pointer 
        current->next = prev; 
  
        // Move pointers one position ahead. 
        prev = current; 
        current = next; 
    } 
    L = prev;
} 

void merge(nodePT L1, nodePT L2){
    nodePT list = (nodePT)malloc(sizeof(struct node));
    list->data = 0;
    list->next = NULL;
    nodePT C1 = L1->next;
    nodePT C2 = L2->next;
    nodePT prev = list;

    while(C1 != NULL || C2 != NULL){
        if(C2 == NULL){
            prev->next = C1;
            break;
        }
        else if(C1 == NULL){
            prev->next = C2;
            break;
        }
        else if(C1->data <= C2->data){
            nodePT temp = C1;
            C1 = temp->next;
            temp->next = prev->next;
            prev->next = temp;
        }
        else if(C1->data > C2->data){
            nodePT temp = C2;
            C2 = temp->next;
            temp->next = prev->next;
            prev->next = temp;
        }
        prev = prev->next;

    }
    *L1 = *list;
    L2 = NULL;
    free(list);
}

void removeDuplicates(nodePT L){
    nodePT current;
    nodePT test;
    nodePT del; 
    current = L->next;

    while (current != NULL && current->next != NULL) { 
        test = current; 

        while (test->next != NULL) { 
            if (current->data == test->next->data) { 
                del = test->next; 
                test->next = test->next->next; 
                free(del);
            } 
            else{
                test = test->next; 
            }
        } 
        current = current->next; 
    }
}

nodePT removeKth(nodePT L, int k){
    nodePT kNode;
    nodePT prev;
    nodePT curr = L->next;
    int count = 1;

    while(curr != NULL){
        if(count == k){
            kNode = curr;
            prev->next = curr->next;
        }
        prev = curr;
        curr = curr->next;
        count++;
    }

    return kNode;
}

nodePT removeByValue(nodePT nd, int val){
    nodePT valNode;
    nodePT curr = nd->next;
    nodePT prev;

    while(curr != NULL){
        if(curr->data == val){
            valNode = curr;
            prev->next = curr->next;
        }
        prev = curr;
        curr = curr->next;
    }

    return valNode;
}

void insert(nodePT L, int val){
    nodePT valNode = (nodePT)malloc(sizeof(struct node));
    valNode->data = val;
    valNode->next = NULL;
    nodePT curr = L->next;
    nodePT prev;
    
    while(curr != NULL){
        if(val <= curr->data){
            prev->next = valNode;
            valNode->next = curr;
            break;
        }
        prev = curr;
        curr = curr->next;
    }
}

void insertKth(nodePT L, int k, int val){
    nodePT kNode = (nodePT)malloc(sizeof(struct node));
    kNode->data = val;
    kNode->next = NULL;
    nodePT prev = L;
    nodePT curr = prev->next;
    int count = 1;

    while(curr != NULL){
        if(count == k){
            prev->next = kNode;
            kNode->next = curr;
            break;
        }
        count++;
        prev = curr;
        curr = curr->next;
    }
}