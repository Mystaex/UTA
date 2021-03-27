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
    int done;               //0 if the producer is still working, 1 if the producer is finished.

    char arr[BUFFER_SIZE];
};

struct queue q;                         //struct to hold the circular queue
char filename[13] = "message.txt";      //Assuming file will always be called message.txt
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

//Function that dequeues a char from a circular queue and returns it to the consumer thread
char dequeue(){
    if(q.size == 0){
        return 0;       //NULL if buffer is empty.
    }
    pthread_mutex_lock(&size_mutex);
    char c = q.arr[q.front];                
    q.front = (q.front+1)%BUFFER_SIZE;
    q.size--;
    pthread_mutex_unlock(&size_mutex);
    return c;
}

//Function used by the producer thread that reads characters one by one and then 
//enqueues it into the circular queue when allowed.
void * readf(){
    FILE* fp;
    if((fp=fopen(filename, "r"))==NULL)
    {
        printf("ERROR: can’t open %s!\n", filename);
        return 0;
    }

    //Hand control back and forth between consumer and producer(this)
    //untill text in file is finished. Ends when input character is NULL or \n
    char curr = fgetc(fp);              //First char read is necessary to start the shile loop
    while(curr > 0 && curr != 10){
        sem_wait(&chars_in_line);       //Take control
        enqueue(curr);                  //Send char 
        curr = fgetc(fp);               //Read new char
        sem_post(&chars_processed);     //Give control
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
        sem_wait(&chars_processed);     //Take control
        char c = dequeue();             //Take char
        //!c is not enough to know that the producer is done. q.done is necessary
        //To tell the consumer that the producer has no more to read. !c simply happens
        //when the buffer is empty.
        if(!c && q.done)                
            break;              
        printf("%c\n", c);              
        sem_post(&chars_in_line);       //Give control
    }
    return NULL;
}

/*Use condition variables to implement the producer-consumer algorithm. Assume two
threads: one producer and one consumer. The producer reads characters one by one
from a string stored in a file named “message.txt”, then writes sequentially these
characters into a circular queue. Meanwhile, the consumer reads sequentially from the
queue and prints them in the same order. Assume a buffer (queue) size of 5 characters.*/
int main(int argc, char** argv){
    //Initial state of buffer. Nothing is in queue, so rear and front are equal at -1.
    q.front = q.rear = -1;
    q.done = q.size = 0;

    pthread_t consumer, producer;

    //Create the 2 semaphors. Start with "chars_in_line" at 1 so that the 
    //producer starts first. 
    sem_init( & chars_processed, 1, 0);
    sem_init( & chars_in_line, 1, 1);
    pthread_mutex_init( &size_mutex, NULL);

    //Start of the producer-consumer loop
    pthread_create(&producer, NULL, readf, NULL);
    pthread_create(&consumer, NULL, popf, NULL);

    //End of the producer-consumer loop
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    //Closing of program, ensuring closing of semaphores and mutexes 
    pthread_mutex_destroy(&size_mutex);
    sem_destroy(&chars_processed);
    sem_destroy(&chars_in_line);
}