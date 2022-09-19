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
	char buffer[1024];
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t addr_size;
	
	//create socket
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0)
	{
		perror("[-] Socket error\n");
		exit(1);
	}
	printf("[+] Server Socket created.\n");
	
	//define server address
	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	// bind to port
	
	n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (n<0)
	{
		perror("[-] Bind error]n");
		exit(1);
	}
	printf("[+] Binding sucessful. PORT Number: %d\n", PORT);
	
	//listening
	listen(server_sock, 5);
	printf("Listening...\n");

	while(1)
	{	
		addr_size = sizeof(client_addr);	
		client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
		printf("[+] Client Connected.\n");
		
		// zero buffer
		bzero(buffer, 1024);
		
		//recieve msg from client
		recv(client_sock, buffer, sizeof(buffer), 0);
		printf("Client: %s\n", buffer);
		
		// send msg to client
		bzero(buffer, 1024);
		strcpy(buffer, "this is server, hi");
		printf("Server: %s\n", buffer);
		send(client_sock, buffer, sizeof(buffer), 0);
		
		close(client_sock);
	}
	
	return 0;
}
