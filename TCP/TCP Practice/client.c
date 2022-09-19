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
	
	char buffer[1024];
	int sock;
	struct sockaddr_in addr;
	
	// create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock<0)
	{
		perror("[-]Socket not created.\n");
		exit(0);
	}
	printf("[+]Socket Created\n");
	
	// address
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	//connect to server
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("[+]Connectd to server\n");
	
	//send msg to server
	char data[1024];
	bzero(buffer,1024);
	printf("Enter message for server: ");
	fgets(data, 1024, stdin);
	strcpy(buffer, data);
	printf("\nclient: %s\n", buffer);
	send(sock, buffer, strlen(buffer), 0);
	
	//receive msg from server
	bzero(buffer, 1024);
	recv(sock, buffer, sizeof(buffer), 0);
	printf("Server: %s", buffer);
	
	return 0;	
	
}	
	
