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
	struct sockaddr_in addr;
	
	// create socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
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
	
	//send msg to server
	char data[1024];
	bzero(buffer,1024);
	printf("Enter message for server: ");
	fgets(data, 1024, stdin);
	strcpy(buffer, data);
	printf("\nclient: %s\n", buffer);
	sendto(sock, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
	
	return 0;
	
}
