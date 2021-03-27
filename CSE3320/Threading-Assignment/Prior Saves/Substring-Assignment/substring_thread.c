#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX 5000000
#define CORES 4

struct thread_info{
    int start;
    int stop;
}; 

int n1,n2; 
char *s1,*s2;

FILE *fp;

int readf(char* filename){
    if((fp=fopen(filename, "r"))==NULL){
        printf("ERROR: can’t open %s!\n", filename);
        return 0;
    }
    
    s1=(char *)malloc(sizeof(char)*MAX);
    
    if (s1==NULL){
        printf ("ERROR: Out of memory!\n") ;
        return -1;
    }
    
    s2=(char *)malloc(sizeof(char)*MAX);
    
    if (s1==NULL){
        printf ("ERROR: Out of memory\n") ;
        return -1;
    }
    
    /*read s1 s2 from the file*/
    
    s1=fgets(s1, MAX, fp);
    s2=fgets(s2, MAX, fp);
    n1=strlen(s1); /*length of s1*/
    n2=strlen(s2)-1; /*length of s2*/
    
    if( s1==NULL || s2==NULL || n1 < n2 ) /*when error exit*/{
        return -1;
    }
}

void* num_substring (void * args){
    int total = 0;
    int i,j,k;
    int count;
    for (i = ((struct thread_info*)args)->start; i <= (((struct thread_info*)args)->stop); i++){
        count = 0;
        for(j = i ,k = 0; k < n2; j++,k++){ /*search for the next string of size of n2*/
            if (*(s1+j)!=*(s2+k)){
                break ;
            }
            else{
                count++;
            }
            if (count==n2)
                total++; /*find a substring in this step*/
         }
    }
    return (void*)total ;
}
    
int main(int argc, char *argv[])
{
    int count = 0;

    if( argc < 2 ){
      printf("Error: You must pass in the datafile as a commandline parameter\n");
    }

    readf ( argv[1] ) ;

    int num_threads = 0;

    //Finds the highest number of threads that satisfy the given conditions
    //As well as fits into the number of cores on my VM.
    for(int i = 1; i <= CORES; i++){
        if(n1%i == 0){
            if(n1/i > n2){
                num_threads = i;
            }
        }
    }

    printf("NUM THREADS: %d\n", num_threads);

    pthread_t threads[num_threads];
    int interval = n1/num_threads;
    struct thread_info ** arguments = (struct thread_info**)malloc(sizeof(struct thread_info*) * num_threads);

    struct timeval start, end;
    float mtime; 
    int secs, usecs;    
    gettimeofday(&start, NULL);

    //Creates the correct number of threads and finds their correct start and stop numbers.
    for(int i = 0; i < num_threads; i++){
        arguments[i] = malloc(sizeof(struct thread_info));
        arguments[i]->start = interval*i;
        arguments[i]->stop = interval*(i+1)-1;
        if(pthread_create(&threads[i], NULL, num_substring, arguments[i] ))
        {
            perror("Error creating thread: ");
            exit( EXIT_FAILURE ); 
        }
    }

    //Joins together all threads used to go through S1 and collects the total of substrings
    //from each.
    void* partialCount;
    for(int i = 0; i < num_threads; i++){
        if(pthread_join(threads[i], &partialCount)){
            perror("Problem with pthread_join: ");
        }
        count += (int)partialCount;
        free(arguments[i]);
    }

    gettimeofday(&end, NULL);

    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;

    printf ("The number of substrings is : %d\n" , count) ;
    printf ("Elapsed time is : %f milliseconds\n", mtime );

    if( s1 ){
      free( s1 );
    }
    if( s2 ){
      free( s2 );
    }
    free(arguments);

    return 0 ; 
}
