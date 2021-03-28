#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*	Ethan Chase | 1001457646
	CSE 2100 	| Lab 5
	Packet creator
*/

int main(int argc, char** argv){
	char input[253];
	int packets[255];
	int start = 0xAA;
	packets[0] = start;
	int checksum = 0x00;

	printf("Lab 5 | CSE-2100 | Ethan Chase | 1001457656\n");
	printf("Enter: ");
	fgets(input, 253, stdin);
	strtok(input, "\n");
	
	//Insert length into the packet array
	int length = 0;
	length = strlen(input) + 3;
	packets[1] = length;

	//Insert the word into the packet array
	int i = 0;
	for(i = 0; i < strlen(input); i++){
		packets[i+2] = input[i];
	}
	
	//Checksum calculation
	for(i = 0; i < length-1; i++){
		checksum = checksum^packets[i];
	}
	packets[length-1] = checksum;
	
	//Print out packets
	for(i = 0; i < length; i++){
		printf("0x%02X ", packets[i]);
	}
	printf("\n");
}