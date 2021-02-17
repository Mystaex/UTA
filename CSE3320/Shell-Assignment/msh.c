// The MIT License (MIT)
// 
// Copyright (c) 2016, 2017, 2021 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 7f704d5f-9811-4b91-a918-57c1bb646b70
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

/*
Ethan Chase
Shell Assignment
CSE 3320
*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 12     // Mav shell only supports 10 arguments, the input, and the NULL

#define MAX_NUM_ENTRIES 15      //Listpids and history should support 15 entries


//Puts the pid into the first empty spot in the pids array.
//If the pids array is full, then the FIFO rule will be applied and
//all entries will move up one spot, and put the newest pid at the end
void insertPid(pid_t* pids, pid_t curr){
  int full = 1;
  int spot = 0;
  int i = 0;
  while((i < MAX_NUM_ENTRIES)){
    if(pids[i] == -1){
      full = 0;
      spot = i;
      break;
    }
    i++;
  }

  //Case of the array having an empty space
  if(!full){
    pids[spot] = curr;
  }
  //Case of the array being full and having to apply FIFO
  else{
    for(i = 0; i < (MAX_NUM_ENTRIES-1); i++){
      pids[i] = pids[i+1];
    }
    pids[MAX_NUM_ENTRIES-1] = curr;
  }
}

//Puts the string into the first empty spot in the cmds array.
//If the cmds array is full, then the FIFO rule will be applied and
//all entries will move up one spot, and put the newest pid at the end
void insertCmd(char ** cmds/**char cmds[MAX_NUM_ENTRIES][MAX_COMMAND_SIZE]**/, char* curr){
  int full = 1;
  int spot = 0;
  int i = 0;
  while((i < MAX_NUM_ENTRIES)){
    int x = 0;
    if(cmds[i][0] == 0){
      full = 0;
      spot = i;
      break;
    }
    i++;
  }

  //Case of the array having an empty space
  if(!full){
    strcpy(cmds[spot],curr);
  }
  //Case of the array being full and having to apply FIFO
  else{
    for(i = 0; i < (MAX_NUM_ENTRIES-1); i++){
      strcpy(cmds[i],cmds[i+1]);
    }
    strcpy(cmds[MAX_NUM_ENTRIES-1],curr);
  }
}

//Goes through the pids array and prints out the entries if the space is occupied.
//Function for listpids command
void history(char ** cmds/*[MAX_NUM_ENTRIES][MAX_COMMAND_SIZE]*/){
  int i = 0;
  while((i < MAX_NUM_ENTRIES) && (cmds[i][0] != 0)){
    printf("%2d. %s", i, cmds[i]);
    i++;
  }
}

//Goes through the cmds array and prints out the entries if the space is occupied.
//Function for history command
void listPids(pid_t* pids){
  int i = 0;
  while((i < MAX_NUM_ENTRIES) && (pids[i] != -1)){
    printf("%2d. %d\n", i, pids[i]);
    i++;
  }
}

int main(){

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
  pid_t * pids = (pid_t*)malloc(sizeof(pid_t) * MAX_NUM_ENTRIES);
  //char cmds[MAX_NUM_ENTRIES][MAX_COMMAND_SIZE];
  char ** cmds = (char**)malloc(sizeof(char*) * MAX_NUM_ENTRIES);

  int i;
  for(i = 0; i < MAX_NUM_ENTRIES; i++){
    pids[i] = -1;
  }
  for(i = 0; i < MAX_NUM_ENTRIES; i++){
    cmds[i] = (char*)malloc(MAX_COMMAND_SIZE);
    //cmds[i] =  NULL
  }


  while( 1 ){
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;  

    insertCmd(cmds, cmd_str);                          
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input strings with whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS)){
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 ){
        token[token_count] = NULL;
      }
        token_count++;
    }

    // Now print the tokenized input as a debug check
    // \TODO Remove this code and replace with your shell functionality

    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ){
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }
    
    if(token[0] != NULL){
      /*If quit or exit are input into shell, then break the loop and quit the program.*/
      if(!strcmp(token[0], "quit") || !strcmp(token[0], "exit")){
        break;
      }

      else if(!strcmp(token[0], "listpids")){
        listPids(pids);
      }

      else if(!strcmp(token[0], "history")){
        history(cmds);
      }

      else if(!strcmp(token[0], "cd")){
        if(token[2] == NULL){
          chdir(token[1]);
        }
        else{
          printf("cd: too many arguments\n");
        }
      }

      else if(token[0][0] == '!'){
        printf("Called history use func\n");
      }

      /*If command is none of the above special commands, then execute with execvp in a child process.*/
      else{
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

          execvp(token[0], token);
          
          
          fflush(NULL);
          exit( EXIT_SUCCESS );
        }
        else 
        {

          printf("pid: %d\n", pid);
          insertPid(pids, pid);

          // When fork() returns a positive number, we are in the parent
          // process and the return value is the PID of the newly created
          // child process.
          int status;

          // Force the parent process to wait until the child process 
          // exits
          waitpid(pid, &status, 0 );
          fflush( NULL );
        }
      }
    }
    

    free( working_root );

  }
  free(pids);
  for(i = 0; i < MAX_NUM_ENTRIES; i++){
    free(cmds[i]);
  }
  free(cmds);
  return 0;
}
