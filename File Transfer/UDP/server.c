#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define PORT 5566
#define SIZE 1024

void write_file(int sockfd, struct sockaddr_in addr)
{
	FILE *fp;
	char *filename = "file2.txt";
	int n;
	char buffer[SIZE];
	socklen_t addr_size;
	
	fp = fopen(filename, "w");
	if(fp == NULL)
	{
		perror("[-] Error in opening file.\n");
		exit(1);
	}
	while(1)
	{
		addr_size = sizeof(addr);
		n = recvfrom(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, &addr_size);
		if(n<0)
		{
			break;
			return;
		}
		printf("Data recieved from file: %s", buffer);
		fprintf(fp, "%s", buffer);
		bzero(buffer, SIZE);
	}
	fclose(fp);
	return;
}


int main()
{
	int n, sockfd;
	struct sockaddr_in server_addr;
	char buffer[SIZE];
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
	{
		perror("[-] Socket error.\n");
		exit(1);
	}
	printf("[+] Socket created.\n");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	n = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(n<0)
	{
		perror("[-] Bind error.\n");
		exit(1);
	}
	printf("[+] Binding successful.\n");
	
	printf("UDP File Server started.\n");
	
	write_file(sockfd, server_addr);
	
	printf("[+] Data transferred.\n");
	close(sockfd);
	return 0;
}
