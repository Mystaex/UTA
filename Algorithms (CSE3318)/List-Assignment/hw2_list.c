#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"

void fillList(struct node *L1, struct node *L2, char *filename){
    FILE *fp = fopen(filename,"r");
    char *token;
    char *line = malloc(100);

    for(int i = 0; i < 2; i++){
        struct node *list;
        int value;

        fgets(line, 100, fp);
        int size = atoi(strtok(line, " "));
        int *nums = malloc(sizeof(int) * size);
        for(int x = 0; x < size; x++){
            token = strtok(NULL, " ");
            printf("%s", token);

            nums[x] = atoi(token);
        }
        list = array_2_list(nums, size);
        if(i == 0){
            *L1 = *list;
        }
        else{
            *L2 = *list;
        }
        free(list);
        free(nums);
    }
    free(line);
    fclose(fp);
}

void removeDup(struct node *list){
    struct node *current;
    struct node *test;
    struct node *del; 
    current = list->next;

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

int isSorted(struct node *list){
    int orderInfo = 1;
    struct node* current = list->next;

    while(current != NULL && current->next != NULL){
        if(current->data > current->next->data){
            orderInfo = 0;
            break;
        }
        current = current->next;
    }

    return orderInfo;
}

void merge(struct node *L1, struct node *L2){
    struct node *list = new_list();
    struct node *C1 = L1->next;
    struct node *C2 = L2->next;
    struct node *prev = list;

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
            struct node* temp = C1;
            C1 = temp->next;
            temp->next = prev->next;
            prev->next = temp;
        }
        else if(C1->data > C2->data){
            struct node* temp = C2;
            C2 = temp->next;
            temp->next = prev->next;
            prev->next = temp;
        }
        prev = prev->next;

    }
    *L1 = *list;
    L2 = NULL;
    free(list);
    print_list_vert(L1, 1);
}

int main(int argc, char **argv){
    int loop = 1;
    struct node *L1;
    struct node *L2;
    int listFilled = 0;
    int listFilled2 = 0;

    while(loop){
        printf("\n****MENU****\n1 - load from a file 2 linked list. The numbers to go as data for the nodes are given in the file.\n2 - check if L1 is sorted and print a message about it\n3 - merge L1 and L2 and have L1 reference the resulting list. (that is, after merging,if I use L1 it will be the list with merged nodes). Print L1 again.\n4 - remove duplicates from L1 and print L1 again.\n5 - print L1 and L2\n6 - destroy L1 and L2\n0 - exit the loop for the menu.\nOption: ");
        char *input = malloc(100);
        for(int i = 0; i < 8; i ++){
            input[i] = '0';
        }
        fgets(input, 100, stdin);
        printf("\n");
        int option = 0;
        option = atoi(input);
        free(input);
        while(option < 0 || option > 6){
            printf("\n***That option is not available. Please select 0-6 from the above menu: ");
            char *input = malloc(100);
            for(int i = 0; i < 8; i ++){
                input[i] = '0';
            }
            fgets(input, 100, stdin);
            printf("\n");
            int option;
            option = atoi(input);
            free(input);
        }
        if(option == 0){
            if(listFilled){
                destroy_list(L1);
                if(listFilled2){
                    destroy_list(L2);
                }
            }
            loop = 0;
        }
        else if(option == 1){
            L1 = malloc(sizeof(struct node));
            L2 = malloc(sizeof(struct node));
            char *filename = malloc(sizeof(char)*100);
            printf("Input file name: ");
            fgets(filename, 100, stdin);
            filename = strtok(filename, "\n");
            fillList(L1, L2, filename);

            free(filename);
            listFilled = 1;
            listFilled2 = 1;
        }
        else if(option == 2){
            if(listFilled){
                int sorted = isSorted(L1);
                if(sorted){
                    printf("L1 is sorted.\n");
                }
                else{
                    printf("L1 is NOT sorted.\n");
                }
            }
            else{
                printf("L1 is empty. Cannot check for sorted status.\n");
            }
        } 
        else if(option == 3){
            if(listFilled){
                if(isSorted(L1) && isSorted(L2)){
                    merge(L1, L2);
                    free(L2);
                    listFilled2 = 0;
                }
                else{
                    printf("Either L1 or L2 aren't sorted. Cannot merge at this time. Both must be sorted to merge. \n");
                }
            }
            else{
                printf("L1 and L2 are empty. Cannot merge.\n");
            }
        }
        else if(option == 4){
            if(listFilled){
                removeDup(L1);
                print_list_vert(L1, 1);
            }
            else{
                printf("L1 is empty. Cannot remove duplicates.\n");
            }
        }
        else if(option == 5){
            if(listFilled){
                print_list_vert(L1, 1);
                if(listFilled2){
                    print_list_vert(L2, 2);
                }
            }
            else{
                printf("lists are empty. Cannot print.\n");
            }
        }

        else if(option == 6){
            if(listFilled){
                destroy_list(L1);
                if(listFilled2){
                    destroy_list(L2);
                }
                listFilled = 0;
            }
            else{
                printf("Lists are already empty.\n");
            }
        }
    }
}