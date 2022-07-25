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
	int sock, n;
	struct sockaddr_in addr;
	char buffer[1024];
	
	printf("[+] PORT ADDRESS: %d\n", PORT);
	
	// socket creation
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock<0)
	{
		perror("Socket error\n");
		exit(1);
	}
	printf("[+] UDP Socket Created.\n\n");
	
	// server address initialize
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	bzero(buffer, 1024);
	strcpy(buffer, "Hello World");
	sendto(sock, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
	printf("[+] Data Send: %s", buffer);

	
	return 0;
	
}
