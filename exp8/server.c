#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    int sockfd, n, key, pos = -1;
    int arr[50];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Server is listening on port 8080...\n");
    recvfrom(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&client, &len);
    recvfrom(sockfd, arr, sizeof(arr), 0, (struct sockaddr *)&client, &len);
    recvfrom(sockfd, &key, sizeof(key), 0, (struct sockaddr *)&client, &len);
    for(int i=0; i<n; i++) {
        if(arr[i] == key) {
            pos = i;
            break;
        }
    }
    sendto(sockfd, &pos, sizeof(pos), 0, (struct sockaddr *)&client, len);
    printf("result calculated\n");
    close(sockfd);
    return 0;
}