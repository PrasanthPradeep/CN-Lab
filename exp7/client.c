#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
    int sockfd, n, key, pos;
    int arr[50];
    struct sockaddr_in server;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements: ");
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    printf("Enter the key to search: ");
    scanf("%d", &key);
    write(sockfd, &n, sizeof(n));
    write(sockfd, arr, n*sizeof(int));
    write(sockfd, &key, sizeof(key));
    read(sockfd, &pos, sizeof(pos));
    if (pos >= 0)
        printf("Element found at position: %d\n", pos);
    else
        printf("Element not found in the array.\n");
    close(sockfd);
    return 0;
}