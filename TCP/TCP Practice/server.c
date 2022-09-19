#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define PORT 5566


int main()
{
	int n;
	char buffer[1024];
	socklen_t addr_size;
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	
	// create socket
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock<0)
	{
		perror("[-]Socket not created.\n");
		exit(0);
	}
	printf("[+]Socket Created\n");
	
	// address
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	// bind
	n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (n<0)
	{
		perror("[-]Bind Error.\n");
		exit(0);	
	}
	printf("[+]Bind successful. PORT:5566\n");
	
	// listen
	listen(server_sock, 5);
	printf("Listening..\n");
	
	while(1)
	{
		addr_size = sizeof(client_addr);
		
		//connect to client
		client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
		printf("[+]Client Connected\n");
		
		bzero(buffer,1024);
		
		//recieve msg from client
		recv(client_sock, buffer, sizeof(buffer), 0);
		printf("Message from Client: %s\n\n", buffer);
		
		//msg to client
		bzero(buffer, 1024);
		char data[1024];
		printf("Enter message to client: ");
		fgets(data, 1024, stdin);
		strcpy(buffer, data);
		printf("\nServer: %s", buffer);
		send(client_sock, buffer, sizeof(buffer), 0);
		
		
	
	}
		
	
	
	return 0;
}
