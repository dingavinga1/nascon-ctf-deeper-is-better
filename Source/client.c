#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>

void ConnectToDaddy(char* buffer){
    int sockfd;
    struct sockaddr_in servAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servAddr, 0, sizeof(servAddr)); // Add closing parenthesis

    servAddr.sin_family = AF_INET;

    char ip[] = {0x33,0x34,0x2e,0x31,0x34,0x33,0x2e,0x31,0x37,0x34,0x2e,0x35,0x33};
    int sexy = 10;
    sexy *= 1000;
    int lols = 9;
    lols *= 1000;
    sexy += lols;

    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(sexy);

    connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));

    read(sockfd, buffer, sizeof(buffer));
}

void getFlag(){
    char ip[] = "192.168.1.198";

    int sockfd;
    struct sockaddr_in servAddr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servAddr, 0, sizeof(servAddr)); // Add closing parenthesis

    servAddr.sin_family = AF_INET;

    int lols = 1234;

    servAddr.sin_addr.s_addr = inet_addr(ip);
    servAddr.sin_port = htons(lols);

    connect(sockfd, (struct sockaddr*)&servAddr, sizeof(servAddr));
    
    

    char buffer[1024]={0x5f,0x43,0x55,0x4d,0x5f,0x54,0x30,0x5f,0x54,0x48,0x30,0x53,0x33};
    write(sockfd, buffer, sizeof(buffer));
    
    
    read(sockfd, buffer, sizeof(buffer));

    printf("%s", buffer);
}

int main(){
    srand(time(NULL));
    printf("The underground welcomes you. Maybe you can find the rest of the flag here (If you're lucky)\n"); // Add newline
    long input;
    scanf("%ld", &input); // Add address of operator & to input


    if(input == rand()){
        char buffer[1024];
        ConnectToDaddy(buffer);
        
        printf("%s", buffer);
    }
    else{
        printf("Congratulations! You got the flag:\n"); // Add newline
        getFlag();
    }

    return 0;
}
