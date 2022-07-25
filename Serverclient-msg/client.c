#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>

#define PORT 5566


int main()
{

	char buffer[1024];
	int n;
	
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0); 
	if (sock < 0)
	{
		perror("Socket not created\n");
		exit(1);
	}
	printf("TCP Socket Client created\n\n");
	
	//define the sock address
	struct sockaddr_in addr;
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;	
	
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("Connected to server.\n");
	
	// sending msg to server
	bzero(buffer,1024);
	strcpy(buffer,"Hello, this is client");
	printf("Client: %s\n", buffer);
	send(sock, buffer, strlen(buffer), 0);
	
	// recieving msg from server
	bzero(buffer, 1024);
	recv(sock, buffer, sizeof(buffer), 0);
	printf("Server: %s\n", buffer);

	close (sock);
	printf("Disconnected from server\n");
	return 0;
}
