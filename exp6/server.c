#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    int sockfd, num, sum = 0;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Server is listening on port 8080...\n");
    recvfrom(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&client, &len);
        while(num > 0) {
            sum += num % 10;
            num /= 10;
        }
        sendto(sockfd, &sum, sizeof(sum), 0, (struct sockaddr *)&client, len);
        printf("result calculated\n");
    close(sockfd);
    return 0;
}