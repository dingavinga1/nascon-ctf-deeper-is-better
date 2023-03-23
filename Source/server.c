#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

int main(){
	char flag[]="_WH0_W41T555555";
	
	int sockfd, connfd;
	struct sockaddr_in servAddr, cliAddr;
	
	sockfd=socket(AF_INET, SOCK_STREAM, 0);
	
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family=AF_INET;
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servAddr.sin_port=htons(19000);
	
	bind(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));
	
	listen(sockfd, 1000);
	
	for(int i=0; i<1000; i++){
		connfd = accept(sockfd, (struct sockaddr*)&cliAddr, &(socklen_t){sizeof(cliAddr)});
		
		int pid=fork();
		if(!pid){
			write(connfd, flag, sizeof(flag));
			close(connfd);
		}
		else if(pid>0)
			continue;
		else
			perror("FORK");
	}
	
	return 0;
}