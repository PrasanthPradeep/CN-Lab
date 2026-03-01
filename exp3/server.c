#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
 
void reverse_string(char *str) { 
    int len = strlen(str); 
    for (int i = 0; i < len/2; i++) { 
        char tmp = str[i]; 
        str[i] = str[len - i - 1]; 
        str[len - i - 1] = tmp; 
    } 
} 
 
int main() { 
    int sockfd, connfd; 
    struct sockaddr_in server, client; 
    char buffer[1024]; 
    socklen_t len; 
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
 
    server.sin_family = AF_INET; 
    server.sin_port = htons(9000); 
    server.sin_addr.s_addr = htonl(INADDR_ANY); 
 
    bind(sockfd, (struct sockaddr*)&server, sizeof(server)); 
    listen(sockfd, 5); 
 
    printf("Server listening on port 9000...\n"); 
 
    len = sizeof(client); 
    connfd = accept(sockfd, (struct sockaddr*)&client,&len); 
 
    // Receive data from client 
    int n = recv(connfd, buffer, sizeof(buffer), 0); 
    buffer[n] = '\0';  // Null-terminate 
 
    printf("Received from client: %s\n", buffer); 
 
    // Reverse the string 
    reverse_string(buffer); 
 
    // Send back the reversed string 
    send(connfd, buffer, strlen(buffer), 0); 
 
    close(connfd); 
    close(sockfd); 
    return 0; 
}