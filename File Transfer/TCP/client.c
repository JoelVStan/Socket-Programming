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

void send_file(FILE *fp, int sockfd)
{
	char data[SIZE] = {0};
	
	while(fgets(data, SIZE, fp) != NULL)
	{
		if(send(sockfd, data, sizeof(data),0) == -1)
		{
			perror("[-] Error in sendng data\n");
			exit(1);
		}
		bzero(data, SIZE);
	}
}

int main()
{
	int e;
	int sockfd;
	struct sockaddr_in server_addr;
	FILE *fp;
	char *filename = "file1.txt";
	
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
	
	e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if(e<0)
	{
		perror("[-] Error in connecting to server.\n");
		exit(1);
	}
	printf("[+] Server Connected.\n");
	
	fp = fopen(filename, "r");
	if(fp==NULL)
	{
		perror("[-] Error in reading file.\n");
		exit(1);		
	}
	
	send_file(fp, sockfd);
	
	printf("[+] File send.\n");
	
	close(sockfd);
	printf("[+] Disconnected\n");

	
	return 0;
}
