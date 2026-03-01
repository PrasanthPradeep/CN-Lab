#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main() {
    int sockfd, n, key, pos;
    int arr[50];
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    printf("Enter the elements of the array: ");
    for(int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Enter the key to search: ");
    scanf("%d", &key);
    sendto(sockfd, &n, sizeof(n), 0, (struct sockaddr *)&server, len);
    sendto(sockfd, arr, sizeof(arr), 0, (struct sockaddr *)&server, len);
    sendto(sockfd, &key, sizeof(key), 0, (struct sockaddr *)&server, len);
    recvfrom(sockfd, &pos, sizeof(pos), 0, (struct sockaddr *)&server, &len);
    if(pos >= 0) {
        printf("Element found at position: %d\n", pos);
    } else {
        printf("Element not found in the array.\n");
    }
    close(sockfd);
    return 0;
}