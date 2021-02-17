#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*
Ethan Chase | 1001457656
CSE 1320-001
*/
/*This function prints out n number of possible flavors*/
void print_out(int *num, char* f[]){
    while(*num > 9){
        printf("There are not %d flavors. Please input a value less than 10: ",*num);
        scanf("%d",num);
    }
    printf("%d Flavors:\n",*num);
    int i;
    for(i = 0; i < *num; i++){
        printf("%s\n",f[i]);
    }
    printf("\n");
}

/*This function prints out the flavors that start with the same letter as the inputted word*/
int name_flavors(char *n, char* f[], int *s){
    int matches = 0;
    int i;
    for(i=0; i<*s; i++){
        char *word = f[i];
        char *fLetter = &word[0];
        if(toupper(*n) == *fLetter){
            printf("Flavour Match! %s\n",word);
            matches++;
        }
    }
    return matches;
}

/*Main*/
int main(int argc, char **argv){
    int input;
    char *flavList[] = {"Chocolate Chocolate Chip", "Classic Vanilla","Red Velvet","White Chocolate Raspberry","Confetti","Carrot","Lemon","Marble","Pecan Praline"};
    int size = 9;
    int *sizeptr = &size;
    while(input != 3){
        printf("***Menu:***\n");
        printf("1-pick how many you want\n2-see if any match the first letter of your name\n3-to exit\n");
        scanf("%d", &input);
        /*Pick how many you want*/
        if(input == 1){
            int flavCount;
            printf("\nHow many do you want? ");
            scanf("%d",&flavCount);
            print_out(&flavCount, flavList);
        }
        /*What to do for matching*/
        if(input == 2){
            char c[50];
            int bool = 0;
            printf("\nEnter a name:\n");
            scanf("%s",c);
            while(!strcmp(c,"abc") || atoi(c) != 0){
                printf("This is not a valid string. Please input a valid string: ");
                scanf("%s",c);
            }
            int matches = name_flavors(&c[0],flavList,sizeptr);
            printf("Number of matches: %d\n\n", matches);
        }
    }
}