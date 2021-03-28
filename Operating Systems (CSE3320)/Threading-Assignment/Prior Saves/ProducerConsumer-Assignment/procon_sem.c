#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define BUFFER_SIZE 5   //Size of the circular queue "buffer"


//Struct used to hold all relevant information for the circular queue
struct queue{
    int front;
    int rear;

    int size;
    int done;

    char arr[BUFFER_SIZE];
};

struct queue q;
char filename[13] = "message2.txt";      //File will always be called message.txt
sem_t chars_processed, chars_in_line;   
pthread_mutex_t size_mutex;

//Function that enqueues a char into a circular queue
//Parameter: char to be inputted into the queue
void enqueue(char c){
    if(q.size > BUFFER_SIZE){
        return;
    }
    pthread_mutex_lock(&size_mutex);
    if(q.front == -1)
        q.front++;
    q.rear = (q.rear+1)%BUFFER_SIZE;
    q.arr[q.rear] = c;
    q.size++;
    pthread_mutex_unlock(&size_mutex);
}

//Function that dequeues a char from a circular queue
char dequeue(){
    if(q.size == 0){
        return 0;
    }
    pthread_mutex_lock(&size_mutex);
    char c = q.arr[q.front];
    q.front = (q.front+1)%BUFFER_SIZE;
    q.size--;
    pthread_mutex_unlock(&size_mutex);
    return c;
}

//Function used by the producer thread that enqueues a character into the circular queue
//When allowed.
void * readf(){
    FILE* fp;
    if((fp=fopen(filename, "r"))==NULL)
    {
        printf("ERROR: can’t open %s!\n", filename);
        return 0;
    }

    //Hand control back and forth between consumer and producer(this)
    //untill text in file is finished. Ends when input character is NULL or \n
    char curr = fgetc(fp);
    while(curr > 0 && curr != 10){
        while(q.size >= BUFFER_SIZE){
            sem_wait(&chars_in_line);
        }
        enqueue(curr);
        curr = fgetc(fp);
        sem_post(&chars_processed);
    }
    //Final post is necessary to allowed the consumer to run it's check 1 more time and close
    q.done = 1;
    sem_post(&chars_processed);

    fclose(fp);
    return NULL;
}

//Function used by the consumer thread that dequeues a character from the circular queue
//When allowed.
void * popf(){
    //Hand control back and forth between consumer(this) and producer
    //until text in file is finished. 
    while(1){
        while(!q.size){
            if(q.done)
                break;
            sem_wait(&chars_processed);
        }
        char c = dequeue();
        if(!c && q.done)
            break;
        printf("%c\n", c);
        sem_post(&chars_in_line);
    }
    return NULL;
}

/*Use condition variables to implement the producer-consumer algorithm. Assume two
threads: one producer and one consumer. The producer reads characters one by one
from a string stored in a file named “message.txt”, then writes sequentially these
characters into a circular queue. Meanwhile, the consumer reads sequentially from the
queue and prints them in the same order. Assume a buffer (queue) size of 5 characters.*/
int main(int argc, char** argv){
    q.front = q.rear = -1;
    q.done = q.size = 0;

    pthread_t consumer, producer;

    //Begin the timer
    struct timeval start, end;
    float mtime; 
    int secs, usecs;    
    gettimeofday(&start, NULL);

    //Create the 2 semaphors. Start with "chars_in_line" at 1 so that the 
    //producer starts first. 
    sem_init( & chars_processed, 1, 0);
    sem_init( & chars_in_line, 1, 0);
    pthread_mutex_init( &size_mutex, NULL);

    pthread_create(&producer, NULL, readf, NULL);
    pthread_create(&consumer, NULL, popf, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    //Finish the timer
    gettimeofday(&end, NULL);
    secs  = end.tv_sec  - start.tv_sec;
    usecs = end.tv_usec - start.tv_usec;
    mtime = ((secs) * 1000 + usecs/1000.0) + 0.5;

    printf ("\nElapsed time is : %f milliseconds\n", mtime );

    pthread_mutex_destroy(&size_mutex);
    sem_destroy(&chars_processed);
    sem_destroy(&chars_in_line);
}