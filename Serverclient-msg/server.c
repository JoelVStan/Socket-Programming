#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>

#define PORT 5566


int main()
{

	char buffer[1024];
	int n;
	
	// create the socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0); 
	if (server_socket < 0)
	{
		perror("Socket not created\n");
		exit(1);
	}
	printf("TCP Socket server created\n\n");
	
	//define the server address
	struct sockaddr_in server_address;
	memset(&server_address, '\0', sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	// binding the socket to specified IP and port
	n = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
	if (n < 0)
	{
		perror("Bind error\n");
		exit(1);
	}
	printf("Binding successful to port number %d\n", PORT);
	
	
	//Listening
	listen(server_socket, 5);
	printf("Listening...\n");
	
	
	// connecting to client
	int client_socket;
	struct sockaddr_in client_address;
	while(1){
	socklen_t addr_size = sizeof(client_address);
	client_socket = accept(server_socket, (struct sockaddr*)&client_address, &addr_size);
	printf("Client connected.\n\n");
	
	// message from client
	bzero(buffer, 1024);
	recv(client_socket, buffer, sizeof(buffer), 0);
	printf("Client: %s\n", buffer);
	
	// message to client from server
	bzero(buffer, 1024);
	strcpy(buffer, "Hi, i am server.");
	printf("Server: %s\n", buffer);
	send(client_socket, buffer, strlen(buffer), 0);
	
	close(client_socket);
	
	printf("Client disconnected\n");
	}
	
	//close socket
	close(server_socket);
	
	return 0;
}
