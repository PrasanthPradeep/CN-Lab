#include <stdio.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
 
int main() { 
    int sockfd; 
    struct sockaddr_in server; 
    char buffer[1024]; 
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
 
    server.sin_family = AF_INET; 
    server.sin_port = htons(9000); 
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
 
    connect(sockfd, (struct sockaddr*)&server, sizeof(server)); 
 
    printf("Enter string: "); 
    fgets(buffer, sizeof(buffer), stdin); 
    buffer[strcspn(buffer, "\n")] = 0;  // Remove newline 
 
    // Send to server 
    send(sockfd, buffer, strlen(buffer), 0); 
 
    // Receive reversed string 
    int n = recv(sockfd, buffer, sizeof(buffer), 0); 
    buffer[n] = '\0'; 
 
    printf("Reversed string from server: %s\n", buffer); 
 
    close(sockfd); 
    return 0; 
} 