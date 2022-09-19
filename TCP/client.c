#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

#define PORT 5566
#define MAX_LIMIT 1024

int main()
{
	int n;
	int sock;
	char buffer[1024];
	struct sockaddr_in addr;
	socklen_t addr_size;
	
	//create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("[-] Socket error\n");
		exit(1);
	}
	printf("[+] Server Socket created.\n");
	
	//define address
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("[+] Connected to server.\n");
	
	//send msg to server
	char data[MAX_LIMIT];
	bzero(buffer, 1024);
	printf("Enter data to send: ");
	fgets(data, MAX_LIMIT, stdin);
	strcpy(buffer, data);
	printf("Client: %s\n", buffer);
	send(sock, buffer, strlen(buffer), 0);
	
	//recv msg from server
	bzero(buffer, 1024);
	
	recv(sock, buffer, sizeof(buffer), 0);
	printf("Server: %s\n", buffer);
	
	close (sock);	
	
	return 0;
	
}
