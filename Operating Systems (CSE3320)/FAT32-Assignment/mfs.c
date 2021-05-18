// The MIT License (MIT)
// 
// Copyright (c) 2020 Trevor Bakker 
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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


/*
*    Authors           ID
* 	 Ethan Chase       1001457646
*    Robert Fabbro     1001724536
*/


#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#define MAX_NUM_ARGUMENTS 5

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

struct __attribute__((__packed__)) DirectoryEntry{
  char DIR_Name[11];
  uint8_t DIR_Attr;
  uint8_t unused[8];
  uint16_t ClusterHigh;
  uint8_t unused2[4];
  uint16_t ClusterLow;
  uint32_t size;
};

struct DirectoryEntry dir[16];

//Key fat32 image values extracted on open
int16_t BPB_BytesPerSec;
int8_t BPB_SecPerClus;
int16_t BPB_RsvdSecCnt;
int8_t BPB_NumFATs;
int32_t BPB_FATSz32;

FILE *fp;   //fat32 image file pointer used to read from the fat32 image file

/*
 * \brief info
 *
 * prints out key values of a fat32 image when the info command is typed
 *
 * \param none
 *
 * \return void
 */
void info(){
  printf("BPB_BytesPerSec:\t %6d 0x%04x\n", BPB_BytesPerSec, BPB_BytesPerSec);
  printf("BPB_SecPerClus:\t\t %6d 0x%04x\n", BPB_SecPerClus, BPB_SecPerClus);
  printf("BPB_RsvdSecCnt:\t\t %6d 0x%04x\n", BPB_RsvdSecCnt, BPB_RsvdSecCnt);
  printf("BPB_NumFATs:\t\t %6d 0x%04x\n", BPB_NumFATs, BPB_NumFATs);
  printf("BPB_FATSz32:\t\t %6d 0x%04x\n", BPB_FATSz32, BPB_FATSz32);
}

/*
 * \brief openFunc
 *
 * Opens a file (an image file in our case) and sets key values of a fat32 image then
 * sets the the file pointer to the root directory
 *
 * \param inputted filename
 *
 * \return returns the newly allocated _block of NULL if failed
 */
FILE* openFunc(char* filename){
  FILE* fp;
  fp = fopen(filename, "r");
  if (fp == NULL){
    printf("Error: No File System Found\n");
    return fp;
  }

  //Finding info values
  fseek(fp, 11, SEEK_SET);
  fread(&BPB_BytesPerSec, 2, 1, fp);

  fseek(fp, 13, SEEK_SET);
  fread(&BPB_SecPerClus, 1, 1, fp);

  fseek(fp, 14, SEEK_SET);
  fread(&BPB_RsvdSecCnt, 2, 1, fp);

  fseek(fp, 16, SEEK_SET);
  fread(&BPB_NumFATs, 1, 1, fp);

  fseek(fp, 36, SEEK_SET);
  fread(&BPB_FATSz32, 4, 1, fp);

  // After read, set seek head to default directory.
  int32_t dir_start = (BPB_NumFATs * BPB_FATSz32 * BPB_BytesPerSec) + (BPB_RsvdSecCnt * BPB_BytesPerSec);
  fseek(fp, dir_start, SEEK_SET);

  return fp;
}

/*
 * \brief LBAToOffset
 *
 * Finds the offset of a cluster.
 *
 * \param desired sector number
 *
 * \return offset for sector number
 */
int LBAToOffset(int32_t sector) {
	return ((sector - 2) * BPB_BytesPerSec) + (BPB_BytesPerSec * BPB_RsvdSecCnt) + (BPB_NumFATs * BPB_FATSz32 * BPB_BytesPerSec);
}

/*
 * \brief NextLB
 *
 * Looks up into the first FAT at the logical block address.
 *
 * \param Desired sector
 *
 * \return the read in values of that sector
 */
int16_t NextLB(uint32_t sector){
  uint32_t FATAddress = (BPB_BytesPerSec * BPB_RsvdSecCnt) + (sector * 4);
  int16_t val;
  fseek(fp, FATAddress, SEEK_SET);
  fread(&val, 2, 1, fp);
  return val;
}

/*
 * \brief readByByte
 *
 * Reads a given number of bytes from a file from the fat32 image at a given start point and
 * prints out the bytes in hex to the terminal
 *
 * \param start is the start offset to begin reading from the file from.
 * \param numBytes is the number of bytes left to read from the file.
 * \param position is the current position in the cluster. Will be 0-512.
 * \param cluster is the starting cluster of the file in terms of the start position
 *
 * \return void
 */
void readByByte(int start, int numBytes, int position, int cluster){
  fseek(fp, start, SEEK_SET);

  while(numBytes > 0){
    printf("0x%02x ", fgetc(fp));
    position++;
    numBytes--;
    if(position >= 512){  //Reached end of cluster
      if((cluster = NextLB(cluster)) < 0){  //Reached end of file
        printf("\nError: Reached end of file prematurely. Bytes left to read: (%d)\n", numBytes);
        return;
      }
      position -= 512;
      fseek(fp, LBAToOffset(cluster), SEEK_SET);  //Move fp to next cluster
    }
  }
  printf("\n");
}

/*
 * \brief compare
 *
 * compares 11 characters from 2 strings
 *
 * \param expanded_name is the normalized format of the inputted filename
 * \param given filename from the directory to compare to
 *
 * \return true if the 2 strings match. False otherwise.
 */
//Returns 1 if normalized version of input matches filename. Returns 0 if not.
int compare(char* expanded_name, char* filename){
  if( strncmp( filename, expanded_name, 11 ) == 0 )
  {
    return 1;
  }
  else{
    return 0;
  }
}

/*
 * \brief findFile
 *
 * Normalizes the inputted filename to be searched for against directory filenames.
 * Then compares input filename against all directory filenames.
 *
 * \param user inputted filename 
 *
 * \return If the input filename matches a directory filename, returns index value from
 * directory array. Otherwise, returns -1
 */
int findFile(char *input){

  //Normalize user inputted filename
  char expanded_name[12];
  memset( expanded_name, ' ', 12 );

  char *token = NULL;
  if(strcmp(input, "..")){
      token = strtok( input, "." );
  } else{
      token = input;
  }

  strncpy( expanded_name, token, strlen( token ) );

  token = strtok(NULL, ".");

  if( token )
  {
    strncpy( (char*)(expanded_name+8), token, strlen(token ) );
  }

  expanded_name[11] = '\0';

  int i;
  for( i = 0; i < 11; i++ )
  {
    expanded_name[i] = toupper( expanded_name[i] );
  }

  //Compare normalized user inputted filename against all 16 directory filenames
  for(i = 0; i < 16; i++){
    if(compare(expanded_name, dir[i].DIR_Name)){
      return i;
    }
  }
  return -1;
}

/*
 * \brief print_directory
 *
 * prints out the directory contents to console.
 *
 * \param none
 *
 * \return none
 */
void print_directory(){
    int i;
    for (i = 0; i < 16; i++) {
      if (dir[i].DIR_Attr == 0x01 || dir[i].DIR_Attr == 0x10 || dir[i].DIR_Attr == 0x20) {
        char filename[12];
        strncpy(filename, &dir[i].DIR_Name[0], 11);
        filename[11] = '\0';
        if(filename[0] != '\xe5')
          printf("%s\n", filename);
      }
    }
}

/*
 * \brief getFile
 *
 * Reads a file from the fat32 image and writes the file to the users current local directory
 *
 * \param start is the starting offset of the file
 * \param cluster is the starting cluster of the file
 * \param filename is the user inputted filename
 * \param size to know how far to print
 *
 * \return void
 */
void getFile(int start, int cluster, char* filename, uint32_t size){
  FILE* fileOut = fopen(filename, "w");
  if(fileOut == NULL){
    printf("Output file cannot be opened.\n");
  }
  else{
    fseek(fp, start, SEEK_SET);
    int position = 0;
    int totalpos = 0;

    //Read through the entire given file, copying the chars from the file on the fat32 image to
    //your local directory
    while(totalpos < size){
      fprintf(fileOut, "%c", fgetc(fp));
      position++;
      totalpos++;
      if(position >= 512){  //Reached end of cluster
        if((cluster = NextLB(cluster)) < 0){  //Reached end of file
          fclose(fileOut);
          return;
        }
        position -= 512;
        fseek(fp, LBAToOffset(cluster), SEEK_SET);  //Move fp to next cluster
      }
    }
    fclose(fileOut);
  }
}

/*
 * \brief cd
 *
 * changes directory to the desired directory.
 *
 * \param directory name
 *
 * \return none
 */
void cd(char *token[MAX_NUM_ARGUMENTS]){
    int offset = 0;
    int fileIndex = findFile(token[1]);
    if(fileIndex < 0){
        printf("Error: Directory not found\n");
    }
    else if(dir[fileIndex].DIR_Attr != 0x10 && dir[fileIndex].DIR_Name[0] != 0x2e){
        printf("Error: Input was not a directory.\n");
    }
    else{
        int cluster = dir[fileIndex].ClusterLow;
        if(cluster == 0)
            cluster = 2;
        offset = LBAToOffset(cluster);
        fseek(fp, offset, SEEK_SET);
    }


    uint32_t position;
    position = ftell(fp);
    fread(&dir, sizeof(struct DirectoryEntry), 16, fp);
    fseek(fp, position, SEEK_SET);
}

// A simple program to move through and interact with a FAT file system. 
int main()
{
  fp = NULL;

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );

  while( 1 )
  {
    // Print out the mfs prompt
    printf ("mfs> ");

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
    char *arg_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );                

    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (arg_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( arg_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    //QUIT
    if((!strcmp(token[0], "quit")) || !(strcmp(token[0], "exit"))){
      if(fp != NULL){
        fclose(fp);
        fp = NULL;
      }
      break;
    }

    //OPEN
    else if(!strcmp(token[0], "open")){
      if(fp == NULL){
        fp = openFunc(token[1]);

        if(fp != NULL){
            uint32_t position;
            position = ftell(fp);
            fread(&dir, sizeof(struct DirectoryEntry), 16, fp);
            fseek(fp, position, SEEK_SET);
        }
      }
      else
        printf("Error: File system image already open.\n");
    }

    else if(fp == NULL){
      printf("Error: File system image must be opened first.\n");
    }

    //CLOSE
    else if(!strcmp(token[0], "close")){
      fclose(fp);
      fp = NULL;
    }

    //INFO
    else if(!strcmp(token[0], "info")){
      if(fp != NULL)
        info();
      else
        printf("Error: System image must be opened first\n");
    }

    //STAT
    else if(!strcmp(token[0], "stat")){
        if(token[1] != NULL){
            int fileIndex = findFile(token[1]);
            if(fileIndex < 0){
              printf("Error: File not found.\n");
            }
            else{
              printf("File Attribute\t\tSize\t\tStarting Cluster Number\n");
              printf("%u\t\t\t%u\t\t%u\n", dir[fileIndex].DIR_Attr, dir[fileIndex].size, dir[fileIndex].ClusterLow);
            }
        }else {
            printf("Error: Not enough arguments.\n");
        }
    }

    //CD
    else if(!strcmp(token[0], "cd")){
      
      if(token[1] == NULL){
        printf("Error: Not enough parameters.\n");
      }
      else{
        cd(token);
      }
    }

    //LS
    else if(!strcmp(token[0], "ls")){
      uint32_t position = ftell(fp);
      if (token[1] != NULL){
          if(!strcmp(token[1], ".")){
              print_directory();
          }
          else if(!strcmp(token[1], "..")){
			  // check for if in root directory.
              if(position == (BPB_NumFATs * BPB_FATSz32 * BPB_BytesPerSec) + (BPB_RsvdSecCnt * BPB_BytesPerSec)){
                  print_directory();
              }else{
				  // change directory to one above
                  cd(token);
                  print_directory();
				  // seek back to original directory and reread the contents. 
                  fseek(fp, position, SEEK_SET);
                  fread(&dir, sizeof(struct DirectoryEntry), 16, fp);
                  fseek(fp, position, SEEK_SET);
              }
          }
          else{
              printf("Error: Invalid parameter.\n");
          }
      }
      else{
          print_directory();
      }
    }

    //GET
    else if(!strcmp(token[0], "get")){
      if(token[1] == NULL){
        printf("Error: Not enough parameters.\n");
      }
      else{
        int fileIndex = findFile(token[1]);
        if(fileIndex < 0){
          printf("Error: File not found\n");
        }
        else{
          uint16_t cluster = dir[fileIndex].ClusterLow;

          //Save current fp to return after reading file
          uint32_t fp_position;
          fp_position = ftell(fp);

          //Copy file from image to directory
          getFile(LBAToOffset(cluster), cluster, token[1], dir[fileIndex].size);
          fseek(fp, fp_position, SEEK_SET);
        }
      }
    }

    //READ
    else if(!strcmp(token[0], "read")){
      if(token[1] == NULL){
        printf("Error: No filename inputted.\n");
      }
      else{
        int fileIndex = findFile(token[1]);
        if(fileIndex < 0){
          printf("Error: File not found\n");
        }
        else{
          //Read requires 
          if(token[2] == NULL || token[3] == NULL)
            printf("Error: Incorrect read command format.\n");
          else{
            int pos = atoi(token[2]);
            int numBytes = atoi(token[3]);
            uint16_t cluster = dir[fileIndex].ClusterLow;

            //Clusters are 512 bytes, so if the user starts later than 512, find the next cluster
            //Until the position is under 512.
            while(pos >= 512){
              pos -= 512;
              cluster = NextLB(cluster);
              if(cluster < 0){
                printf("Error: Attempt to read past file bounds.\n");
              }
            }
            //Save current fp to return after reading file
            uint32_t fp_position;
            fp_position = ftell(fp);

            //Read a given number of bytes from a given file starting at given start position 
            readByByte(LBAToOffset(cluster), numBytes, pos, cluster);
            fseek(fp, fp_position, SEEK_SET);
          }
        }
      }
    }
    //NON-COMMAND
    else{
      printf("%s is not a supported command.\n", token[0]);
    }

    free( working_root );

  }
  return 0;
}
