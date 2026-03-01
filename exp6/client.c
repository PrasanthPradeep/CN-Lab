#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    int sockfd, num, sum;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Enter a number: ");
    scanf("%d", &num);
    sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&server, len);
    recvfrom(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&server, &len);
    printf("Sum of digits: %d\n", sum);
    close(sockfd);
    return 0;
}