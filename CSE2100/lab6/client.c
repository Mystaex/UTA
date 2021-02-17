//modified from https://www.educative.io/edpresso/how-to-implement-tcp-sockets-in-c

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //needed for socket related functions
#include <arpa/inet.h> //needed for internet related functions

/* 	Ethan Chase	| 1001457656
	CSE 2100	| Lab 6 Client
	Packet Client
*/

int main(int argc, char** argv)
{
	printf("Ethan Chase | Lab6 Client\n");
	int socket_desc;
	struct sockaddr_in server_addr;
	char server_message[2000];
	char client_message[2000];
	char input[253];
	int packets[255];
	
	// Clean buffers:
	memset(server_message,'\0',sizeof(server_message));
	memset(client_message,'\0',sizeof(client_message));
	
	// Create socket:
	socket_desc = socket(AF_INET, SOCK_STREAM, 0);
	
	if(socket_desc < 0){
	    printf("Unable to create socket\n");
	    return -1;
	}
	
	printf("Socket created successfully\n");
	
	// Set port and IP the same as server-side:
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[1]));
	server_addr.sin_addr.s_addr = inet_addr(argv[2]);
	
	// Send connection request to server:
	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
	    printf("Unable to connect\n");
	    return -1;
	}
	printf("Connected with server successfully\n");

	while(1){
		memset(input,'\0',sizeof(input));
		memset(client_message,'\0',sizeof(client_message));
		// Get input from the user:
		printf("Enter message: ");
		gets(input);
		strtok(input, "\n");

		if (strcmp(input,"q") == 0){
			close(socket_desc);
			break;
		}

		int x = 0;
		for(x = 0; x < 253; x ++){
			packets[x] = 0;
		}
		//Packet creation
		
		int start = 0xAA;
		packets[0] = start;
		char temp[6];
		int checksum = 0x00;
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
			sprintf(temp, "0x%02X ", packets[i]);
			strcat(client_message, temp);
		}
		printf("Sending: %s\n", client_message);
		
		// Send the message to server:
		if(send(socket_desc, client_message, strlen(client_message), 0) < 0){
		    printf("Unable to send message\n");
		    return -1;
		}
		
		// Receive the server's response:
		if(recv(socket_desc, server_message, sizeof(server_message), 0) < 0){
		    printf("Error while receiving server's msg\n");
		    return -1;
		}
		
		printf("Server's response: %s\n",server_message);
	}
	printf("Closing Client...\n");
	// Close the socket:
	close(socket_desc);
    return 0;
}
