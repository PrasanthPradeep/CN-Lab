#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    int sockfd, num, sum;
    struct sockaddr_in server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Enter a number: ");
    scanf("%d", &num);
    write(sockfd, &num, sizeof(num));
    read(sockfd, &sum, sizeof(sum));
    printf("Sum of digits: %d\n", sum);
    close(sockfd);
    return 0;
}