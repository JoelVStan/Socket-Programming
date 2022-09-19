//UDP

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
	int sock;
	struct sockaddr_in server_addr, client_addr;
	
	// create socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock<0)
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
	n = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (n<0)
	{
		perror("[-]Bind Error.\n");
		exit(0);	
	}
	printf("[+]Bind successful. PORT:5566\n");
	
	//recieve msg from client
	addr_size = sizeof(client_addr);
	recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
	printf("Message from Client: %s\n\n", buffer);
	
	
	
	
	return 0;
	
}
