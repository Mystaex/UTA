#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#define MAX 5000000
#define NUM_THREADS 4

//Struct used to store arguments passed into threads.
//start used to specify start index. stop used to specify stop index
//Both indexes are used together to define a search zone for each thread
struct thread_info{
    int start;
    int stop;
}; 

int n1,n2; 
char *s1,*s2;
int total;
pthread_mutex_t mutex; 

FILE *fp;

//Reads a given input file and stores strings and stringlengths into global variables
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

//Function used to count the amount of substrings, S2, in a string, S1
//Takes in a struct thread_info* as parameter to dictate start and stop indexes of S2 loop
//Returns number of substrings found in given start-stop area
void* num_substring (void * ptr){
    int subtotal = 0;
    struct thread_info* args = (struct thread_info*)ptr;
    int i,j,k;
    int count;
    //Searches every char in S1 between start and stop indexes
    for (i = args->start; i <= args->stop; i++){
        count = 0; 
        //On every searched, search N2 chars following to check for substring, S2
        //If substring is found, add to count
        for(j = i ,k = 0; k < n2; j++,k++){ /*search for the next string of size of n2*/
            if (*(s1+j)!=*(s2+k)){
                break ;
            }
            else{
                count++;
            }
            if (count==n2)
                subtotal++; /*find a substring in this step*/
        }
    }

    //Adding the total of substrings in a given section to the total number of substrings in S1
    //Lock is necessary as to not have 2 threads try to add to the total at the same time
    pthread_mutex_lock(&mutex);
    total+= subtotal;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

//Given two character strings s1 and s2. This is a threaded program to find out the number
//of substrings, in string s1, that is exactly the same as s2.
int main(int argc, char *argv[])
{
    total = 0;

    if( argc < 2 ){
      printf("Error: You must pass in the datafile as a commandline parameter\n");
    }

    readf ( argv[1] ) ;

    printf("NUM THREADS: %d\n", NUM_THREADS);

    pthread_t threads[NUM_THREADS];     //Dynamic array to hold as many threads as NUM_THREADS
    int interval = n1/NUM_THREADS;      //Finding the interval of search zone for each thread
    //Array of input variables to go into each thread. Need to be of struct to input 2 ints.
    struct thread_info ** arguments = 
    (struct thread_info**)malloc(sizeof(struct thread_info*) * NUM_THREADS);

    //Begins the completion time stopwatch
    struct timeval start, end;
    float mtime; 
    int secs, usecs;    
    gettimeofday(&start, NULL);

    pthread_mutex_init( &mutex, NULL); //Mutex used to unlock/lock the global total integer

    //Creates the correct number of threads and finds their correct start and stop numbers before 
    //Starting each thread.
    for(int i = 0; i < NUM_THREADS; i++){
        arguments[i] = malloc(sizeof(struct thread_info));
        arguments[i]->start = interval*i;           
        arguments[i]->stop = interval*(i+1)-1;      
        if(pthread_create(&threads[i], NULL, num_substring, arguments[i] ))
        {
            perror("Error creating thread: ");
            exit( EXIT_FAILURE ); 
        }
    }

    //Joins together all threads used. Needs to happen before end of stopwatch to ensure 
    //All threads fully complete before time ends.
    for(int i = 0; i < NUM_THREADS; i++){
        if(pthread_join(threads[i], NULL)){
            perror("Problem with pthread_join: ");
        }
        free(arguments[i]);
    }

    //Ends the completion time stopwatch
    gettimeofday(&end, NULL);
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;

    printf ("The number of substrings is : %d\n" , total );
    printf ("Elapsed time is : %f milliseconds\n", mtime );

    //Free pointers
    if( s1 ){
      free( s1 );
    }
    if( s2 ){
      free( s2 );
    }
    free(arguments);

    pthread_mutex_destroy(&mutex);

    return 0 ; 
}
