#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
Ethan Chase
CSE 1320-001
1001457646
*/
/*struct to hold all dragon descriptions*/
struct dragon{
    char name[100];
    char color[3];
    int heads;
    int tails;
};
typedef struct dragon dragon;

/*Pulls info from dragon info file*/
void dragon_info(dragon *d){
    char line[200];
    char *token;
    int nameCount = 0;
    int colorCount = 0;
    int tailCount = 0;
    int headCount = 0;
    int subCount = 0;
    fgets(line,200,stdin);
    token = strtok(line,",");
    int i = 0;
    /*Sifting through file to get descriptors*/
    while(i < 24){
        token = strtok(NULL,",");
        
        if(i%6 == 0 || i == 0){
            strcpy(d[nameCount].name,token);
            nameCount++;
        }
        else if(i%6 > 0 && i%6 < 4){
            subCount++;
            d[colorCount].color[subCount] = *token;
            if(subCount == 3){
                colorCount++;
                subCount = 0;
            }
        }
        else if(i%6 == 4){
            d[headCount].heads = atoi(token);
            headCount++;
        }
        else if(i%6 == 5){
            d[tailCount].tails = atoi(token);
            tailCount++;
        }
        i++;
    }
}

/*This function finds all dragons of a specific color and prints them*/
void color(char* color, dragon *d){
    char colorName[20];
    /*Decoding which color*/
    if(*color == 'b'){
        strcpy(colorName,"blue");
    }
    else if(*color == 'r'){
        strcpy(colorName,"red");
    }
    else if(*color == 'w'){
        strcpy(colorName,"white");
    }
    else if(*color == 'g'){
        strcpy(colorName,"green");
    }
    else if(*color == 'y'){
        strcpy(colorName,"yellow");
    }
    /*Sorting through dragons for color*/
    printf("***All the %s dragons:***\n", colorName);
    int x = 0;
    for(x = 0; x < 4; x++){
        int y = 0;
        for(y = 0; y < 3; y++){
            if(d[x].color[y] == *color){
                printf("%s is %s.\n",d[x].name,colorName);
            }
        }
    }
}

/*Main function*/
int main (int argc, char **argv){
    dragon total[4];
    dragon_info(total);
    char c='b';
    color(&c, total);
}