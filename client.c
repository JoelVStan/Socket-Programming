#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

#define MAX_LIMIT 1024
#define PORT 5566

int main()
{
	int n, sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	char buffer[1024];
	
	// create socket
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock<0)
	{
		perror("[-] Socket not created.\n");
		exit(1);
	}
	printf("[+] Socket Created.\n\n");
	printf("[+] PORT Number: %d\n\n", PORT);
	
	// server address
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	// data send to server
	char data[MAX_LIMIT];
	bzero(buffer, 1024);
	printf("enter data to send: ");
	fgets(data, MAX_LIMIT, stdin);
	strcpy(buffer, data);
	sendto(sock, buffer, 1024, 0, (struct sockaddr*)&addr, sizeof(addr));
	printf("[+] Data send: %s", buffer);
	
	// data recieve from server
	bzero(buffer, 1024);
	addr_size = sizeof(addr);
	recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&addr, &addr_size);
	printf("[+] Data Recieved: %s", buffer);
	
	
	return 0;
	
}
