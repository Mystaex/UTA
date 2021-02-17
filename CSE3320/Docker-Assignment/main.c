/*
Ethan Chase
1001457646
DockerHW | CSE 3320
*/

/*
**ALTERED FROM TREVOR BAKKER'S fork.c and alarm.c**
*/


#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define ONE_SECOND 1

/*
  fork() a child and print a message from the parent and 
  a message from the child
*/

static void handle_alarm (int sig )
{
  printf ("Caught alarm \n");
  alarm(1);
}

int main( void )
{
  struct sigaction act;
  
  /*
    Zero out the sigaction struct
  */ 
  memset (&act, '\0', sizeof(act));
  
  /*
    Set the handler to use the function handle_alarm()
  */ 
  act.sa_handler = &handle_alarm;
  
  /* 
    Install the handler and check the return value.
  */ 
  if (sigaction(SIGALRM, &act, NULL) < 0) {
    perror ("sigaction: ");
    return 1;
  }

  
  
  pid_t pid = fork();

  if( pid == -1 )
  {
    // When fork() returns -1, an error happened.
    perror("fork failed: ");
    exit( EXIT_FAILURE );
  }
  else if ( pid == 0 )
  {
    // When fork() returns 0, we are in the child process.
    
    if (sigaction(SIGALRM, &act, NULL) < 0) {
      perror ("sigaction: ");
      return 1;
    }
    //Wasn't sure how alarm was to be implemented, so I made it 
    //Catch when the countdown finished.
    alarm(10);    
    
    //Count down from 10 to 1 and print the current number every second
    int i = 10;
    while(i > 0){
      printf("%d\n", i);
      i--;
      sleep(1);
    }
    
    
    fflush(NULL);
    exit( EXIT_SUCCESS );
  }
  else 
  {
    // When fork() returns a positive number, we are in the parent
    // process and the return value is the PID of the newly created
    // child process.
    int status;

    // Force the parent process to wait until the child process 
    // exits
    waitpid(pid, &status, 0 );
    printf("Countdown Complete\n");
    fflush( NULL );
  }
  return EXIT_SUCCESS;
}
