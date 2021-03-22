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
pthread_mutex_t size_mutex, q_mutex;
pthread_cond_t read, write;

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
        pthread_mutex_lock(&q_mutex);
        while(q.size == 5){
            pthread_cond_wait(&read, &q_mutex);
        }
        enqueue(curr);
        curr = fgetc(fp);
        pthread_cond_signal(&write);
        pthread_mutex_unlock(&q_mutex);
    }
    //Final post is necessary to allowed the consumer to run it's check 1 more time and close
    q.done = 1;
    pthread_cond_signal(&write);

    fclose(fp);
    return NULL;
}

//Function used by the consumer thread that dequeues a character from the circular queue
//When allowed.
void * popf(){
    //Hand control back and forth between consumer(this) and producer
    //until text in file is finished. 
    while(1){
        pthread_mutex_lock(&q_mutex);
        while(!q.size && !q.done){
            pthread_cond_wait(&write, &q_mutex);
        }

        char c = dequeue();
        if(!c && q.done)
            return NULL;
        printf("%c\n", c);
        pthread_cond_signal(&read);
        pthread_mutex_unlock(&q_mutex);
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
    pthread_cond_init(&read, NULL);
    pthread_cond_init(&write, NULL);
    pthread_mutex_init( &size_mutex, NULL);
    pthread_mutex_init( &q_mutex, NULL);

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
}