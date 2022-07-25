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
	struct sockaddr_in server_addr, client_addr;
	char buffer[1024];
	socklen_t addr_size;
		
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
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	// binding
	n = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (n<0)
	{
		perror("Bind error\n");
		exit(1);
	}
	printf("[+] Binding Successful!\n\n");

	bzero(buffer, 1024);
	addr_size = sizeof(client_addr);
	recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
	printf("[+] Data Recieved: %s", buffer);
	
	return 0;
}
