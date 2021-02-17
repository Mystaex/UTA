#include "line_header.h"
#include <stdio.h>
/*
Ethan Chase
CSE 1320-001
EGC7646 | 1001457646
*/

struct Node{
    int age;
    int inLine;
    struct Node* next;
};

/*Combines both lines in order of youngest to oldest*/
struct Node* combine(struct Node* line_one, struct Node* line_two){
    struct Node* prev = NULL;
    struct Node* head = NULL;
    struct Node* curYoung = NULL;
    struct Node* current = line_one;
    int numCusts = 0;
    while(current != NULL){
        current->inLine = 0;
        current = current->next;
        numCusts++;
    }
    current = line_two;
    while(current != NULL){
        current->inLine = 0;
        current = current->next;
        numCusts++;
    }
    int i = 0;
    while(i <= numCusts){
        int youngAge = 10000;
        current = line_one;
        while(current != NULL){
            if(current->age < youngAge && !current->inLine){
                youngAge = current->age;
                curYoung = current;
            }
            current = current->next;
        }
        current = line_two;
        while(current != NULL){
            if(current->age < youngAge && !current->inLine){
                youngAge = current->age;
                curYoung = current;
            }
            current = current->next;
        }

        if(head == NULL){
            head = prev = curYoung;
        }
        else{
            prev->next = prev = curYoung;
        }
    }

    return head;
}

/*Reverses order of the line using recursion, to make the line oldest to youngest*/
struct Node* reverse_list_rec(struct Node* head_ref){
    if(head_ref->next == NULL){
        return head_ref;
    }
    struct Node* current = reverse_list_rec(head_ref->next);
    head_ref->next->next = head_ref;
    head_ref->next = NULL;

    return current;
}