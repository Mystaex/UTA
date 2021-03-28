#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*  ETHAN CHASE | EGC7646
    CSE 3318-001
    RUNS IN CSE VM
*/

//Reads in the amount of courses in a file
int readAmountOfVertices(char* filename){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Could not open file %s. Exit\n\n", filename);
        printf("Failed to read from file. Program will terminate.\n\n");
        exit(-1);
    }
    char input[1001];
    int N = 0;

    fgets(input, 1000, fp);
    while(!feof(fp)){
        N++;
        fgets(input, 1000, fp);
        if(strcmp(input, "\n") == 0){
            break;
        }
    }
    fclose(fp);
    return N;
}

//Reads in courses from a file into an array of strings
void readInVertices(char* filename, char** courses, int N){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Could not open file %s. Exit\n\n", filename);
        printf("Failed to read from file. Program will terminate.\n\n");
        exit(-1);
    }
    char input [1001];
    char delim[] = " \n";
    printf("Vertex - coursename correspondance\n");

    int i = 0;
    fgets(input, 1000, fp);
    while(!feof(fp)){
        char* temp;
        temp = strtok(input, delim);
        strcpy(courses[i], temp);
        printf("%d - %s\n", i, courses[i]);
        fgets(input, 1000, fp);
        if(strcmp(input, "\n") == 0){
            break;
        }
        i++;
    }
    fclose(fp);
    printf("\n");
}

//Reads in the adjacency matrix from a file into a 2D int array
void readInAdjMat(char* filename, int N, int edges[N][N], char** courses){
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Could not open file %s. Exit\n\n", filename);
        printf("Failed to read from file. Program will terminate.\n\n");
        exit(-1);
    }
    char input[1001];
    int i = 0;
    fgets(input, 1000, fp);

    for(int x = 0; x < N; x++){
        for(int y = 0; y < N; y++){
            edges[x][y] = 0;
        }
    }

    while(!feof(fp)){
        strtok(input, "\n");
        char* token;
        token = strtok(input, " ");

        int m = 0;
        while(token != NULL){
            if(m > 0)
                for(int j = 0; j < N; j++)
                    if(strcmp(courses[j], token) == 0)
                        edges[i][j] = 1;
            token = strtok(NULL, " ");
            m++;
        }
        i++;
        fgets(input, 1000, fp);
        if(strcmp(input, "\n") == 0){
            break;
        }
    }
    fclose(fp);
}

//Prints out a formatted 2D int array
void printMatrix(int N, int edges[N][N]){
    printf("Adjacency Matrix: \n");
    for(int y = -1; y < N; y++){
        for(int x = -1; x < N; x++){
            if(y == -1){
                if(x == -1){
                    printf("    |");
                }
                else{
                    printf("%4d", x);
                }
            }
            else if(x == -1){
                printf("%4d|", y);
            }
            else{
                printf("%4d", edges[x][y]);
            }
        }
        printf("\n");
        if(y == -1){
            int lineSize = 6 + (N * 4);
            char line[lineSize];
            strcpy(line, "-----");
            for(int i = 0; i < N; i++){
                strcat(line, "----");
            }
            printf("%s\n", line);
        }
    }
    printf("\n");
}

//Topological sorting with depth-first-search
int DFS_visit(int N, int G[][N],int u,char color[], int pred[], int order[]){
    color[u] = 'G';
    for(int v = 0; v < N; v++){         //For each v adjacent to u{ // explore edge (u,v) // use increasing order for neighbors
        if(G[v][u] == 1){
            if (color[v]=='W'){
                pred[v] = u;
                if(DFS_visit(N, G,v, color, pred, order) == -1){
                    return -1;
                }
            }
            if(color[v] == 'G'){
                return -1;
            }
        }
    }
    color[u] = 'B';
    for(int i = 0; i < N; i++){
        if(order[i] == -1){
            order[i] = u;
            return 1;
        }
    }
}

//Performs depth-first-search on a given directed adjacency matrix 
int DFS(int N, int G[][N], int order[]){
    for(int i = 0; i < N; i++){
        order[i] = -1;
    }
    int pred[N];
    char color[N];
    for(int u = 0; u < N; u++){ /*For each vertex u of G*/
        color[u] = 'W';
        pred[u] = -1;
    }
    for (int u = 0; u < N; u++){    // for each vertex u of G
        if(color[u] == 'W'){
            if(DFS_visit(N, G,u, color, pred, order) == -1){
                return -1;
            }
        }
    }
}

//Reverses a given int array
void reverse(int order[], int N){
    for(int i = 0; i < N/2; i++){
        int high = N-1-i;
        int temp = order[i];
        order[i] = order[high];
        order[high] = temp;
    }
}

int isEmpty(int N, int G[][N]){
    for(int x = 0; x < N; x++){
        for(int y = 0; y < N; y++){
            if(G[x][y] == 1){
                return 0;
            }
        }
    }
    return 1;
}

//Given a file with courses and their prerequisites, this program prints out the order in which you should take those classes
int main(int argc, char** argv){
    printf("\nThis program will read, from a file, a list of courses and their prerequisites and will print the list in which to take cousres.\n");
    printf("Enter filename: ");
    char filename[31];
    scanf("%s", filename);
    int vertCount = readAmountOfVertices(filename);
    printf("Number of vertices in built graph: N = %d\n", vertCount);

    //Creating array of coursenames with # assignment
    char** courses = malloc(sizeof(char*) * vertCount);
    for(int i = 0; i < vertCount; i++){
        courses[i] = malloc(sizeof(char) * 30);
    }
    readInVertices(filename, courses, vertCount);

    //Creating Adjacency matrix
    int edges[vertCount][vertCount];
    readInAdjMat(filename, vertCount, edges, courses);
    printMatrix(vertCount, edges);

    if(isEmpty(vertCount, edges)){
        for(int i = 0; i < vertCount; i++){
            printf("%d. - %s (corresponds to graph vertex %d)\n", (i+1), courses[i], i);
        }
    }
    else{
        int order[vertCount];
        if(DFS(vertCount, edges, order) == -1){
            printf("There was at least one cycle. There is no possible ordering of the courses.\n\n");
        }
        else{
            reverse(order,vertCount);

            for(int i = 0; i < vertCount; i++){
                printf("%d. - %s (corresponds to graph vertex %d)\n", (i+1), courses[order[i]], order[i]);
            }
            printf("\n");
        }
    }

    for(int i = 0; i < vertCount; i++){
        free(courses[i]);
    }

    free(courses);
}