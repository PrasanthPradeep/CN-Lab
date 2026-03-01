#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

int main() {
    int sockfd, newsockfd, num, sum=0;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET; 
    server.sin_port = htons(8080); 
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Server is listening on port 8080...\n");
    newsockfd = accept(sockfd, (struct sockaddr *)&client, &len);
    read(newsockfd, &num, sizeof(num));
    while(num > 0) {
        sum += num % 10;
        num /= 10;
    }
    write(newsockfd, &sum, sizeof(sum));
    read(newsockfd, &sum, sizeof(sum));
    printf("result calculated\n");
    close(newsockfd);
    close(sockfd);
    return 0;
}