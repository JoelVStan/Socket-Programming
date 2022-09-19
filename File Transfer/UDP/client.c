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

void send_file(FILE *fp, int sockfd, struct sockaddr_in addr)
{
	char data[SIZE] = {0};
	int n;
	while(fgets(data,SIZE, fp) != NULL)
	{
		printf("Data send to server is: %s", data);
		n = sendto(sockfd, data, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
		if (n<0)
		{
			perror("[-] File send error.\n");
			exit(1);
		}
		bzero(data, SIZE);
	}
	
	fclose(fp);
	return;
}


int main()
{
	int n, sockfd;
	struct sockaddr_in addr;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd<0)
	{
		perror("[-] Socket error.\n");
		exit(1);
	}
	printf("[+] Socket created.\n");
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	FILE *fp;
	char *filename = "file1.txt";
	
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		perror("[-] Error in reading file.\n");
		exit(1);
	}
	
	send_file(fp, sockfd, addr);
	
	printf("[+] File send succesfully\n");
	
	close(sockfd);
	
	printf("[+] Disconnected.\n");
	return 0;
}	
