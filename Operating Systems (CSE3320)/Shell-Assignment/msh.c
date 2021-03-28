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
  ID: 1001457646
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
//The parameters taken in are the array of pids and the current pid to add
void insertPid(pid_t* pids, pid_t curr){
  //Assume the array is full and set otherwise if empty spot is found
  int full = 1;
  int spot = 0;
  int i = 0;
  //Go through cmds string array looking for first empty spot. Assume array is full.
  while((i < MAX_NUM_ENTRIES)){
    //If an empty spot is found, break loop and save empty index.
    if(pids[i] == -1){
      full = 0;
      spot = i;
      break;
    }
    i++;
  }

  //Case of the array having an empty space. Set first empty space to the current command
  if(!full){
    pids[spot] = curr;
  }
  //Case of the array being full and having to apply FIFO with all entries moving forward one
  //space, replacing the first entry and the current command going in the last space (14)
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
//The parameters taken in are the array of commands and the current command to add
void insertCmd(char ** cmds, char* curr){
  //Assume the array is full and set otherwise if empty spot is found
  int full = 1;
  int spot = 0;
  int i = 0;
  //Go through cmds string array looking for first empty spot.
  while((i < MAX_NUM_ENTRIES)){
    //If an empty spot is found, break loop and save empty index.
    if(cmds[i][0] == 0){
      full = 0;
      spot = i;
      break;
    }
    i++;
  }

  //Case of the array having an empty space. Set first empty space to the current command
  if(!full){
    strcpy(cmds[spot],curr);
  }
  //Case of the array being full and having to apply FIFO with all entries moving forward one
  //space (n-1), replacing the first entry and the current command going in the last space (14)
  else{
    for(i = 0; i < (MAX_NUM_ENTRIES-1); i++){
      strcpy(cmds[i],cmds[i+1]);
    }
    strcpy(cmds[MAX_NUM_ENTRIES-1],curr);
  }
}

//Goes through the cmds array and prints out the entries if the space is occupied.
//Function for history command
//Takes in the array of commands
void history(char ** cmds){
  int i = 0;
  while((i < MAX_NUM_ENTRIES) && (cmds[i][0] != 0)){
    printf("%2d: %s", i, cmds[i]);
    i++;
  }
}

//Goes through the pids array and prints out the entries if the space is occupied.
//Function for listpids command
//Takes in the array of pids
void listPids(pid_t* pids){
  int i = 0;
  while((i < MAX_NUM_ENTRIES) && (pids[i] != -1)){
    printf("%2d: %d\n", i, pids[i]);
    i++;
  }
}

//Takes in a string of input from the command line and splits it into tokens for 
//each individual "word"
//Takes in the current command inputted, an token array to tokenize into, and a 
//string to work through the current command with.
void tokenize(char* cmd_str, char* token[MAX_NUM_ARGUMENTS], char* working_root){

  int   token_count = 0;                                 
                                                           
  // Pointer to point to the token
  // parsed by strsep
  char *argument_ptr;               

  // we are going to move the working_str pointer so
  // keep track of its original value so we can deallocate
  // the correct amount at the end
  char* working_str = working_root;

  // Tokenize the input strings with whitespace used as the delimiter
  while(((argument_ptr = strsep(&working_str, WHITESPACE)) != NULL) && 
            (token_count<MAX_NUM_ARGUMENTS)){
    token[token_count] = strndup(argument_ptr, MAX_COMMAND_SIZE);
    if(strlen( token[token_count]) == 0){
      token[token_count] = NULL;
    }
    token_count++;
  }  
}

int main(){

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  //Storage for listpids command
  pid_t* pids = (pid_t*)malloc(sizeof(pid_t) * MAX_NUM_ENTRIES);

  //Storage for history command
  char ** cmds = (char**)malloc(sizeof(char*) * MAX_NUM_ENTRIES);

  //Create "free" spaces in pids array
  int i;
  for(i = 0; i < MAX_NUM_ENTRIES; i++){
    pids[i] = -1;
  }
  //Allocate space for strings inside the cmds array
  for(i = 0; i < MAX_NUM_ENTRIES; i++){
    cmds[i] = (char*)malloc(MAX_COMMAND_SIZE);
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
    char* working_root;
    working_root  = strdup( cmd_str );  
    tokenize(cmd_str, token, working_root);
                                                                          
    if(token[0] != NULL){

      //If quit or exit are input into shell, then break the loop and quit the program.
      if(!strcmp(token[0], "quit") || !strcmp(token[0], "exit")){
        break;
      }

      //If the first character is '!', then follow case for n command from history
      if(token[0][0] == '!'){
        //Extract n from input
        char temp[3];
        temp[0] = token[0][1];
        temp[1] = token[0][2];
        temp[2] = '\0';
        int n = atoi(temp);

        //If the history has n command in storage, tokenize that command and run it through
        //if statements for commands.
        if(cmds[n][0] != 0){
          strcpy(cmd_str, cmds[n]);
          tokenize(cmd_str, token, working_root);
        }
        //If the history doesn't have n commands, then don't run any command and output error msg
        else{
          printf("Command not in history.\n");
          token[0][0] = 0;
        }
      }

      //Case for listpids command
      if(!strcmp(token[0], "listpids")){
        insertCmd(cmds, cmd_str);
        listPids(pids);
      }

      //Case for history command
      else if(!strcmp(token[0], "history")){
        insertCmd(cmds, cmd_str);
        history(cmds);
      }

      //Case for cd command
      else if(!strcmp(token[0], "cd")){
        insertCmd(cmds, cmd_str);

        //Ensure correct amount of arguments for cd command
        if(token[1] == NULL){
          printf("cd: too few arguments\n");
        }
        //If correct # of args, then change directory
        else if(token[2] == NULL){
          chdir(token[1]);
        }
        else{
          printf("cd: too many arguments\n");
        }
      }

      //If command is none of the above special cases, then execute with execvp in a child process
      else if(token[0][0] != 0){
        insertCmd(cmds, cmd_str);
        pid_t pid = fork();

        if( pid == -1 ){
          // When fork() returns -1, an error happened.
          perror("fork failed: ");
          exit( EXIT_FAILURE );
        }
        else if ( pid == 0 ){
          //Run command with any given arguments (Max of 10). If it can't run, output error.
          int ret = execvp(token[0], &token[0]);
          if(ret == -1){
            printf("%s: Command not found\n\n", token[0]);
            exit(0);
          }
          
          fflush(NULL);
          exit( EXIT_SUCCESS );
        }
        else {
          //Insert pid into array of pids for use of listpids command
          insertPid(pids, pid);

          int status;

          // Force the parent process to wait until the child process exits
          waitpid(pid, &status, 0 );
          fflush( NULL );
        }
      }
    }

    free( working_root );

  }

  //Free pointers used in listpids and history storage
  free(pids);
  for(i = 0; i < MAX_NUM_ENTRIES; i++){
    free(cmds[i]);
  }
  free(cmds);
  
  //Return status 0
  return 0;
}