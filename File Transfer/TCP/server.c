#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

#define SIZE 1024
#define PORT 5566

void write_file(int sockfd)
{
	int n;
	FILE *fp;
	char *filename = "file2.txt";
	char buffer[SIZE];
	
	fp = fopen(filename, "w");
	if(fp==NULL)
	{
		perror("[-] Error in creating file.\n");
		exit(1);		
	}
	
	while(1)
	{
		n = recv(sockfd, buffer, SIZE, 0);
		if(n<=0)
		{
			break;
			return;
		}
		fprintf(fp, "%s", buffer);
		printf("Content of file: %s", buffer);
		bzero(buffer, SIZE);
	}
	return;
}

int main()
{
	int e;
	int sockfd, new_sock;
	struct sockaddr_in server_addr, new_addr;
	socklen_t addr_size;
	char buffer[SIZE];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	if (sockfd<0)
	{
		perror("[-] Socket not created.\n");
		exit(1);
	}
	printf("[+] Socket created.\n");
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e<0)
	{
		perror("[-] Bind error.\n");
		exit(1);
	}
	printf("[+]Binding Successful.\n");
	
	listen(sockfd, 10);
	printf("Listening..\n");
	
	addr_size = sizeof(new_addr);
	new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);	
	
	write_file(new_sock);
	printf("[+] Data written in the text file.\n");
		
	return 0;
}
