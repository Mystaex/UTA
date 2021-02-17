#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct treeNode{
	int count;
	char symbol;
	struct treeNode * left;
	struct treeNode * right;
}treeNode;

int * readForFreq(char *filename){
    
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        printf("File cannot be opened.\n");
        exit(1);
    }
    else{
        char inChar;
        
        inChar = fgetc(fp);
        int * characters = (int*)malloc(sizeof(int) * 128);
        for(int i = 0; i < 128; i++){
            characters[i] = 0;
        }
        while(inChar > 0 && inChar != 10){
            characters[inChar] += 1;
            inChar = fgetc(fp);
        }
        fclose(fp);
        return characters;
    }
    
}

treeNode* newNode(char sym, int count, treeNode* t1, treeNode* t2){
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->symbol = sym;
    temp->count = count;
    temp->left = t1;
    temp->right = t2;

    return temp;
}

treeNode** swap(treeNode** A, int p, int index){
    treeNode* temp;
    temp = A[p];
    A[p] = A[index];
    A[index] = temp;

    return A;
}

treeNode** insert(treeNode** A, treeNode* newKey, int * N){
    (*N) = (*N)+1;
    int i = (*N);
    A[i] = newKey;
    while ((i>1)&&(A[i]->count < A[i/2]->count)) {
        A = swap(A, i, i/2);
        i = i/2;
    }
    return A;
}

treeNode** sinkDown(treeNode** A,int p,int size){
    int left = 2*p; // index of left child of p
    int right = (2*p)+1; // index of right child of p
    int index = p;
    if ((left<= size)&&(A[left]->count < A[index]->count)){
        index = left;
    }
    if ((right<= size)&&(A[right]->count < A[index]->count)){
        index = right;
    }
    if (index!=p) {
        A = swap(A, p, index);
        A = sinkDown(A,index,size);
    }
    return A;
}

treeNode** buildMinHeap(treeNode** A,int size){
    for (int p = size/2; p>=1; p--){
        A = sinkDown(A,p,size);
    }
    return A;
}

treeNode** buildPreHeap(int * characters, int size){
    treeNode** preHeap = (treeNode**)malloc(sizeof(treeNode*) * (size));

    preHeap[0] = newNode(0, 0, NULL, NULL);
    int a = 0;
    for(int i = 0; i < 128; i++){
        if(characters[i] > 0){
            a++;
            preHeap[a] = newNode(i, characters[i], NULL, NULL);
        }  
    }

    return preHeap;
}

//Removes the minimum value from the heap, and fixes it
treeNode* removeMin(treeNode*** A,int * N){
    treeNode* min = (*A)[1];
    (*A)[1] = (*A)[(*N)];
    (*N)=(*N)-1;
    (*A) = sinkDown((*A),1,*N);
    return min;
}

//Builds the huffman tree
treeNode* buildHuffmanTree(treeNode** A, int size){
    while(size > 1){
        treeNode* t1 = removeMin(&A, &size);
        treeNode* t2 = removeMin(&A, &size);

        treeNode* temp = newNode('$', t1->count + t2->count, t1, t2);
        A = insert(A, temp, &size);
        printf("buildHuffmanTree: (%c,%d)+(%c,%d) -> (%c,%d); N: %d\n", t1->symbol, t1->count, t2->symbol, t2->count, temp->symbol, temp->count, size);
    }
    return A[1];
}

//Used to get the coding for each letter to start encoding
char** getCodes(treeNode* root, char arr[], int top, char** codes) 
{ 
    if (root->left) 
    { 
        arr[top] = '0'; 
        getCodes(root->left, arr, top + 1, codes); 
    } 
    if (root->right) 
    { 
        arr[top] = '1'; 
        getCodes(root->right, arr, top + 1, codes); 
    } 
    if (root->left == NULL && root->right == NULL) 
    {
        char* path = malloc(sizeof(char) * 127);
        for(int i = 0; i < 127; i++){
            path[i] = 0;
        }
        for(int i = 0; i < top; i++){
            path[i] = arr[i];
        }
        
        printf("%c: %s\n", root->symbol, path);
        free(codes[root->symbol]);
        codes[root->symbol] = path;
    } 

    return codes;
}

void printTreeEncoding(treeNode* root, FILE* fp){
    if(root != NULL){
        if(root->left != NULL && root->right != NULL){
            fprintf(fp, "0");
            printTreeEncoding(root->left, fp);
            printTreeEncoding(root->right, fp);
        }
        else if(root->left == NULL && root->left == NULL){
            fprintf(fp, "1");
            fprintf(fp, "%c",root->symbol);
        }
    }
}

char* readForEncode(char* inName){
    char* line = malloc(sizeof(char) * 10000);
    for(int i = 0; i < 10000; i++){
        line[i] = 0;
    }

    FILE* infp = fopen(inName,"r");

    fgets(line, 10000, infp);
    fclose(infp);
    return line;
}


void encode(treeNode* root, char* inName, char* outName, char** letterCodes){

    FILE* outfp = fopen(outName, "w");
    printTreeEncoding(root, outfp);
    char* input = readForEncode(inName);

    int i = 0;
    while(input[i] != 0 && input[i] != 10){
        fprintf(outfp,"%s", letterCodes[input[i]]);
        i++;
    }

    free(input);
    fclose(outfp);
}

//Deletes the tree at exit.
void deleteTree(treeNode* root){
    if(root->left != NULL){
        deleteTree(root->left);
    }
    if(root->right != NULL){
        deleteTree(root->right);
    }

    free(root);
}

treeNode* insertDecodeTree(FILE* fp){
    treeNode* root;
    char inChar = fgetc(fp);
    if(inChar == 48){
        root = malloc(sizeof(treeNode));
        root->symbol = '$';
        root->count = 0;
        root->left = insertDecodeTree(fp);
        root->right = insertDecodeTree(fp);
    }
    else if(inChar == 49){
        root = newNode(fgetc(fp), 0, NULL, NULL);
    }

    return root;
}

void printChar(treeNode* root, FILE* fp){
    if(root->left == NULL && root->right == NULL){
        printf("%c", root->symbol);
    }
    else if(root->left != NULL && root->right != NULL){
        char move = fgetc(fp);
        if(move == 48){
            printChar(root->left, fp);
        }
        else if(move == 49){
            printChar(root->right, fp);
        }
    }

}

void decode(char* outName){

    FILE* fp = fopen(outName, "r");
    if(fp == NULL){
        printf("File cannot be opened.\n");
        exit(1);
    }
    else{
        treeNode* root = insertDecodeTree(fp);

        char inChar;
        inChar = fgetc(fp);
        printf("decoded string: ");

        while((inChar > 0) && (inChar != 10) && (inChar < 128)){
           if(inChar == 48){
               printChar(root->left, fp);
           }
           else if(inChar == 49){
               printChar(root->right, fp);
           }
            
            
            inChar = fgetc(fp);
        }

        printf("\n");

        deleteTree(root);
    }

    fclose(fp);

}

int main(int argc, char **argv){
    char * inFile = malloc(sizeof(char) * 50);
    char * outFile= malloc(sizeof(char) * 50);
    int asciiSize = 128;

    printf("Enter your option (1-encode/ 2-decode): ");
    char *input = malloc(sizeof(char) * 50);
    fgets(input, 50, stdin);
    int choice = atoi(input);
    switch(choice){
        case 1:
            printf("Enter the name of the DESTINATION file (encoded file): ");
            fgets(outFile, 50, stdin);
            outFile = strtok(outFile,"\n");
            printf("Enter the name of the SOURCE file (to be encoded): ");
            fgets(inFile, 50, stdin);
            inFile = strtok(inFile, "\n");
            printf("Files: %s and %s\n", inFile, outFile);

            int * charac = readForFreq(inFile);
            int size = 0;
            for(int i = 0; i < asciiSize; i++){
                if(charac[i] > 0){
                    size++;
                    printf("(%c , %d)\n", i, charac[i]);
                }
            }
            size+= 1;
            treeNode** minHeap = buildPreHeap(charac, size);
            minHeap = buildMinHeap(minHeap, (size-1)); 
            treeNode* root;
            root = buildHuffmanTree(minHeap, (size-1));


            char** codes = malloc(sizeof(char*) * 128);
            for(int i = 0; i < asciiSize; i++){
                codes[i] = (char*)malloc(sizeof(char) * 127);
            }
            char codeArr[10];
            codes = getCodes(root, codeArr, 0, codes);

            
            encode(root, inFile, outFile, codes);

            deleteTree(root);
            for(int i = 0; i < asciiSize; i++){
                free(codes[i]);
            }
            free(minHeap[0]);
            free(minHeap);
            free(codes);
            free(charac);
            break;
        case 2:
            printf("Enter the name of the DESTINATION file (encoded file): ");
            fgets(outFile, 50, stdin);
            outFile = strtok(outFile,"\n");
            printf("\n");

            decode(outFile);
            break;
    }
    free(input);
    free(inFile);
    free(outFile);
}