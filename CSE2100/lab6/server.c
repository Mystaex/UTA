//modified from https://www.educative.io/edpresso/how-to-implement-tcp-sockets-in-c

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //needed for socket related functions
#include <arpa/inet.h> //needed for internet related functions


//Function to validate the packet from the client
int isValidMsg(char* input){
	char temp[2];
	int packets[255];
	memset(temp, '\0', sizeof(temp));
	int i = 0;
	int x = 0;
	
	//Convert all characters into integer form from hex char form
	while(input[i] > 0 && input[i] < 256 && input[i] != 10){
		temp[0] = input[i+2];
		temp[1] = input[i+3];
		
		packets[x] = (int)strtol(temp, NULL, 16);
		x++;
		i = i+5;
	}
	int in_checksum = packets[(packets[1]) - 1];
	
	//Calculate checksum from given ints
	int checksum = 0;
	for(i = 0; i < ((packets[1]) - 1); i++){
		checksum = checksum^packets[i];
	}
	
	//If given checksum and calculated checksum are equal, return true
	if(checksum == in_checksum)
		return 1;
	else
		return 0;
}

int main(int argc, char** argv)
{
	printf("Ethan Chase | Lab6 Server\n");
	int socket_desc; //status of socket creation
	int client_sock; //status of client connection
	int client_size;//
	struct sockaddr_in server_addr; //struct containing information about our server address
	struct sockaddr_in client_addr; //struct containing information about our client address
	char server_message[2000]; //array containing the server message
	char client_message[2000]; //array containing the clinet message
	
	//Set message arrays to null
	memset(server_message, '\0', sizeof(server_message));
	memset(client_message, '\0', sizeof(client_message));
	
	// Create socket. will return a negative if unsucessful
	socket_desc = socket(AF_INET, SOCK_STREAM, 0); 
	
	//Check to see if socket sucessfully created
	if(socket_desc < 0){
		//Display error and exit if not
	    printf("Error while creating socket\n");
	    return -1;
	}
	printf("Socket created successfully\n");
	
	// Set port and IP:
	server_addr.sin_family = AF_INET; //set socket domain
	server_addr.sin_port = htons(atoi(argv[1])); //set socket port
	server_addr.sin_addr.s_addr = inet_addr(argv[2]); //set socket IP address
	
	// Bind to the set port and IP
	if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
		//Display error and exit if unsucessful
	    printf("Couldn't bind to the port\n");
	    return -1;
	}
	printf("Done with binding\n");
	// Listen for clients
	if(listen(socket_desc, 1) < 0){
	    printf("Error while listening\n");
	    return -1;
	}
	printf("\nListening for incoming connections.....\n");
	
	// Accept an incoming connection and get information about our client
	client_size = sizeof(client_addr);
	client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
	
	if (client_sock < 0){
		//Display error and don't connect if unable to connect
	    printf("Can't accept\n");
	    return -1;
	}
	printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
	while(1){
		memset(server_message, '\0', sizeof(server_message));
		memset(client_message, '\0', sizeof(client_message));
		// Receive client's message:
		if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
		    printf("Couldn't receive\n");
		    return -1;
		}

		if(isValidMsg(client_message) && strcmp(client_message, "") != 0){
			printf("Msg from client: %s\n", client_message);
			strcpy(server_message, "Message Received.");
		}
		else{
			strcpy(server_message, "Message Rejected.");
		}
	
		if (send(client_sock, server_message, strlen(server_message), 0) < 0){
		    printf("Can't send\n");
		    return -1;
		}
	}
	printf("Closing Server...\n");
	// Closing the socket:
	close(client_sock);
	close(socket_desc);

    return 0;
}
