#include <stdio.h>
#include <string.h>
/*
Ethan Chase | 1001457656
CSE 1320-001
*/
/*This function finds where the filename is in argv*/
int find_filename(int n, char **b){
    int i;
    int counter=0; /*equals -1 if didnt find*/
    int check=0;
    for(i=0;i<n&&check==0;i++){
        if(strcmp(*b, "filename")==0){
            check=1;
        }
        counter++;
        b++;
    }
    if(check!=1){
        counter=0;
    }
    return (counter-1);
}

/*This function prints the contents of the file given*/
void print_contents(FILE *fp){
    char line[100];
    while(!feof(fp)){
        fgets(line,100,fp);
        printf("%s",line);
    }
    printf("\n");
}
/*Main*/
int main(int argc,char **argv){
    char *mode = "r";
    FILE *fp;
    char filename[50];
    int place = find_filename(argc,argv) + 1;
    char *infotype;
    int current = 0, previous = 0;
    /*Processing of the file*/
    if(place > 0){
        fp = fopen(argv[place],mode);

        printf("Filename: %s\n", argv[place]);
        if(!strcmp(argv[place+1],"numbers")){
            infotype = "number";
        }
        else{
            infotype = "string";
        }
        printf("We're dealing with %s info.\n\n", infotype);
        printf("Contents of the file:\n");

        print_contents(fp);
        fclose(fp);
    }
    /*If place is at 0, then there is no filename*/
    else{
        printf("No filename given. Bye!\n");
    }
}