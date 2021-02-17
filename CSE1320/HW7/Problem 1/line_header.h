#ifndef LINE_HEADER
#define LINE_HEADER
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

struct Node* combine(struct Node* line_one, struct Node* line_two);
struct Node* reverse_list_rec(struct Node* head_ref);

#endif