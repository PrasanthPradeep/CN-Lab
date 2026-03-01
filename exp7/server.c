#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    int sockfd, newsockfd, n, key, pos;
    int arr[50];
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sockfd, (struct sockaddr *)&server, sizeof(server));
    listen(sockfd, 5);
    printf("Server is listening on port 8080...\n");
    newsockfd = accept(sockfd, (struct sockaddr *)&client, &len);
    read(newsockfd, &n, sizeof(n));
    read(newsockfd, arr, n*sizeof(int));
    read(newsockfd, &key, sizeof(key));
    for(int i=0; i<n; i++) {
        if(arr[i] == key) {
            pos = i;
            break;
        } else {
            pos = -1;
        }
    }
    write(newsockfd, &pos, sizeof(pos));
    printf("result calculated\n");
    close(newsockfd);
    close(sockfd);
    return 0;
}