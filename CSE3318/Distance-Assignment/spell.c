#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "spell.h"

/*  ETHAN CHASE | EGC7646
    CSE 3318-001
*/

/*  COMPILATION INSTRUCTIONS:
gcc spell.c spell_checker.c
./a.out OR valgrind --leak-check=full ./a.out 
inlude < redir1.txt after ./a.out in either execution call to run redirection.
*/


/*  Suggestions
- When you work with 2D arrays, be careful. Either manage the memory yourself, or
work with local 2D arrays. Note C99 allows parameters as array sizes as long as 
they are declared before the array in the parameter list. See: 
https://www.geeksforgeeks.org/pass-2d-array-parameter-c/

Worst case time complexity to compute the edit distance from T test words
 to D dictionary words where all words have length MAX_LEN:
Student answer:  Theta(T * D * (MAX_LEN)^2)


Worst case to do an unsuccessful binary search in a dinctionary with D words, when 
all dictionary words and the searched word have length MAX_LEN 
Student answer:  Theta(MAX_LEN + log(D))
*/

/* You can write helper functions here */
//Returns the minimum of 2 variables
int minOf2(int x, int y){
    if(x > y){
        return y;
    }
    else{
        return x;
    }
    
}

//Returns the minimum of 3 variables
int minOf3(int x, int y, int z) { 
    return minOf2(minOf2(x, y), z); 
} 

//Sets the edit distance array with every value
void getDist(char * str1, char * str2, int m, int n, int Dist[m+1][n+1]) { 

    for(int x = 0; x <= m; x++){
        for(int y = 0; y <= n; y++){
            if(x == 0){
                Dist[x][y] = y;
            }
            else if(y == 0){
                Dist[x][y] = x;
            }
            else if(str2[x-1] == str1[y-1]){
                Dist[x][y] = Dist[x-1][y-1];
            }
            else{
                Dist[x][y] = 1 + minOf3(Dist[x-1][y], Dist[x][y-1], Dist[x-1][y-1]);
            }
        }
    }
} 

//returns the minimum edit distance of 2 strings, and prints a table of the array if asked
int edit_distance(char * first_string, char * second_string, int print_table){
    int edit = -1;

    int size[2] = {strlen(first_string),strlen(second_string)};
    int dist[size[1]+1][size[0]+1];
    
    getDist(first_string, second_string, size[1], size[0], dist);
    edit = dist[size[1]][size[0]];

    if(print_table){
        //PRINTING TABLE
        printf("\n");
        for(int y = -1; y <= size[0]; y++){
            if(y == -1){
                printf("  |   |");
            }
            for(int x = -1; x <= size[1]; x++){
                char curr;
                if(y < 1 || x < 1){
                    curr = ' ';
                }
                if(y > 0 && x == -1){
                    curr = first_string[y-1];
                }
                if(y == -1){
                    if(x > 0)
                        printf("  %c|", second_string[x-1]);
                }
                else{
                    if(x == -1){
                        printf(" %c|", curr);
                    }
                    else{
                        printf("%3d|", dist[x][y]);
                    }
                }
            }
            int i = 0;
            printf("\n---");
            while(i <= size[1]){
                printf("----");
                i++;
            }
            printf("\n");
        }
        printf("\n");
    }
    return edit;
}

//Compares strings for qsort
int compareString(const void* p1, const void* p2){
    const char* s1 = *(const char**)p1;
    const char* s2 = *(const char**)p2;
    return strcmp(s1, s2);
}

//Searches through my dictionary to check for possible words
int binarySearch(char** dic, int low, int high, char* word, char* origWord, int verbose){
    int count = 0;
    while(low <= high){
        count++;
        int mid =low + (high-low)/2;
        if(verbose)
            printf("dict[%d] = %s\n", mid, dic[mid]);

        if(strcmp(dic[mid], word) == 0){
            printf("\n---> |%s| (words compared when searching: %d)\n", origWord, count);
            printf("     - OK\n\n");
            return mid;
        }
        else if(strcmp(dic[mid], word) < 0){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    if(verbose)
        printf("Not found\n");
    printf("\n---> |%s| (words compared when searching: %d)\n", origWord, count);
    return -1;
}

void spell_check(char * testname, char * dictname, int printOn){
    //ADD ERROR CATCHING AND WHAT TO DO IF BAD FILENAME

    char outName[101] = {"out_"};
    strcat(outName, testname);
    printf("Corrected output filename: %s\n", outName);
	FILE *dictFile = fopen(dictname, "r");
    //Test if dictionary file is open
    if(dictFile == NULL){
        printf("Could not open file %s. Exit\n", dictname);
        return;
    }
    printf("\nloading the dictionary file: %s\n", dictname);
    FILE *inFile = fopen(testname, "r");
    //Test if input file is open
    if(inFile == NULL){
        printf("Could not open file %s. Exit\n", testname);
        return;
    }
    FILE *outFile = fopen(outName, "w");
    //Test if output file is open
    if(outFile== NULL){
        printf("Could not open file %s. Exit\n", outName);
        return;
    }
    int dictSize = 0;
    char input[101];
    fscanf(dictFile,"%d", &dictSize);

    printf("\nDictionary has size: %d", dictSize);
    if(printOn)
        printf("\n Original dictionary: \n");
    char **dic = malloc(sizeof(char*) * dictSize);

    //Take in and dictionary and print if verbose
    for(int i = 0; i < dictSize; i++){
        dic[i] = malloc(sizeof(char) * 101);
        fscanf(dictFile,"%s", input);
        strcpy(dic[i], input);
        if(printOn)
            printf("%d. %s\n", i, dic[i]);
    }
    if(printOn)
        printf("\n");


    //Sort dictionary, and then print new
    qsort(dic, dictSize, sizeof(char*), compareString);
    if(printOn){
        printf(" Sorted dictionary (alphabetical order): \n");
        for(int i = 0; i < dictSize; i++){
            printf("%d. %s\n", i, dic[i]);
        }
    }

    //read in file to be checked
    char c = fgetc(inFile);
    int wordPos = 0;
    char temp[101] = "";
    while(c != 10 && c < 256 && c > 0){
        //When the char being read in is in the alphabet, add it to the current word.
        if(isalpha(c)){
            temp[wordPos] = c;
            wordPos++;
        }
        //If the char being read in isn't in the alphabet, end the word.
        else{
            //If there is a current word (not empty), run checks
            if(wordPos > 0){
                
                char tempLower[101];
                char finalword[101];

                //Set the current word to lowercase
                strcpy(tempLower, temp);
                for(int i = 0; i < strlen(tempLower); i++){
                    tempLower[i] = tolower(tempLower[i]);
                } 

                //Run a binary search on the lowercase version of the current word
                if(printOn)
                    printf("\n\nBinary search for: %s\n", tempLower);
                int result = binarySearch(dic, 0, dictSize-1, tempLower, temp, printOn);

                //If the word isn't found:
                if(result < 0){
                    int minDist = 101;
                    int minCount = 0;
                    int checkedWords = 0;
                    //Find the minimum distance and amount of words at that distance
                    for(int i = 0; i < dictSize; i++){
                        checkedWords++;
                        int currDist = edit_distance(tempLower, dic[i],0);
                        if(currDist < minDist){
                            minDist = currDist;
                            minCount = 1;
                        }
                        else if(currDist == minDist){
                            minCount++;
                        }
                    }
                    
                    //Put all words at the minimum distance in an array 
                    char* minWords[minCount];
                    int tempCount = 0;
                    for(int i = 0; i < dictSize; i++){
                        int currDist = edit_distance(tempLower, dic[i],0);
                        if(currDist == minDist){
                            minWords[tempCount] = dic[i];
                            tempCount++;
                        }
                    }

                    //Menu choices
                    printf("-1 - type correction\n 0 - leave word as is (do not fix spelling)\n");
                    printf("     Minimum distance: %d  (computed edit distances: %d)\n", minDist, checkedWords);
                    printf("     Words that give the minimum distance:\n");
                    for(int i = 0; i < minCount; i++){
                        printf(" %d - %s\n", (i+1), minWords[i]);
                    }

                    //Choice input
                    printf("Enter your choice (from the above options): ");
                    int choice = 0;
                    scanf("%d", &choice);
                    
                    //Choice processing. -1 to enter correction. 0 to stay with word. 1+ to choose from list of min dist words
                    switch(choice){
                        case -1:
                            printf("Enter correct word: ");
                            scanf("%s", temp);
                            strcpy(finalword, temp);
                            break;
                        case 0:
                            strcpy(finalword, temp);
                            break;
                    default : 
                        strcpy(finalword, minWords[choice-1]);
                    }
                }
                //If word is found in binary search, then set the output word to the input word.
                else{
                    strcpy(finalword, temp);
                }
                //Print the specified word
                fprintf(outFile, "%s", finalword);
            }
            //Print the current separator
            fprintf(outFile, "%c", c);
            //Reset word
            wordPos = 0;
            memset(temp, 0, 101);
        }
        c = fgetc(inFile);
    }
    //In case there is no separator at the end of the input file, check once again to make sure there is no word.
    if(wordPos > 0){
        
        char tempLower[101];
        char finalword[101];

        //Set the current word to lowercase
        strcpy(tempLower, temp);
        for(int i = 0; i < strlen(tempLower); i++){
            tempLower[i] = tolower(tempLower[i]);
        } 

        //Run a binary search on the lowercase version of the current word
        if(printOn)
            printf("\n\nBinary search for: %s\n", tempLower);
        int result = binarySearch(dic, 0, dictSize-1, tempLower, temp, printOn);

        //If the word isn't found:
        if(result < 0){
            int minDist = 101;
            int minCount = 0;
            int checkedWords = 0;
            //Find the minimum distance and amount of words at that distance
            for(int i = 0; i < dictSize; i++){
                checkedWords++;
                int currDist = edit_distance(tempLower, dic[i],0);
                if(currDist < minDist){
                    minDist = currDist;
                    minCount = 1;
                }
                else if(currDist == minDist){
                    minCount++;
                }
            }
            
            //Put all words at the minimum distance in an array 
            char* minWords[minCount];
            int tempCount = 0;
            for(int i = 0; i < dictSize; i++){
                int currDist = edit_distance(tempLower, dic[i],0);
                if(currDist == minDist){
                    minWords[tempCount] = dic[i];
                    tempCount++;
                }
            }

            //Menu choices
            printf("-1 - type correction\n 0 - leave word as is (do not fix spelling)\n");
            printf("     Minimum distance: %d  (computed edit distances: %d)\n", minDist, checkedWords);
            printf("     Words that give the minimum distance:\n");
            for(int i = 0; i < minCount; i++){
                printf(" %d - %s\n", (i+1), minWords[i]);
            }

            //Choice input
            printf("Enter your choice (from the above options): ");
            int choice = 0;
            scanf("%d", &choice);
            
            //Choice processing. -1 to enter correction. 0 to stay with word. 1+ to choose from list of min dist words
            switch(choice){
                case -1:
                    printf("Enter correct word: ");
                    scanf("%s", temp);
                    strcpy(finalword, temp);
                    break;
                case 0:
                    strcpy(finalword, temp);
                    break;
            default : 
                strcpy(finalword, minWords[choice-1]);
            }
        }
        //If word is found in binary search, then set the output word to the input word.
        else{
            strcpy(finalword, temp);
        }
        //Print the specified word
        fprintf(outFile, "%s", finalword);
    }

    //Freeing memory
    for(int i = 0; i < dictSize; i++){
        free(dic[i]);
    }
    free(dic);
    fclose(dictFile);
    fclose(inFile);
    fclose(outFile);
}