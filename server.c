#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

#define PORT 5566

int main()
{
	int n, sock;
	struct sockaddr_in server_addr, client_addr;
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
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	// binding
	n = bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(n<0)
	{
		perror("[-] Bind Error\n");
		exit(1);
	}
	printf("[+] Binding successful!\n\n");
	
	// data recieved from client
	bzero(buffer, 1024);
	addr_size = sizeof(client_addr);
	recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, &addr_size);
	printf("[+] Data Recieved: %s", buffer);
	
	// data sending to client
	bzero(buffer, 1024);
	char data[1024];
	printf("Enter data to send: ");
	fgets(data, 1024, stdin);
	strcpy(buffer, data);
	sendto(sock, buffer, 1024, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));
	printf("[+] Data send: %s", buffer);
	
	return 0;
}
