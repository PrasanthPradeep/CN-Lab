#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#define PORT 8080 
#define BUFFER_SIZE 1024 
int main() { 
int sockfd; 
struct sockaddr_in server_addr; 
char filename[BUFFER_SIZE]; 
char buffer[BUFFER_SIZE]; 
int n; 
// Create TCP socket 
sockfd = socket(AF_INET, SOCK_STREAM, 0); 
// Server address 
server_addr.sin_family = AF_INET; 
server_addr.sin_port = htons(PORT); 
inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); 
// Connect to server 
connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); 
// Get filename 
printf("Enter filename: "); 
scanf("%s", filename); 
// Send filename to server 
send(sockfd, filename, strlen(filename), 0); 
// Receive response 
printf("\n--- Server Response ---\n"); 
while ((n = read(sockfd, buffer, BUFFER_SIZE)) > 0) { 
buffer[n] = '\0'; 
printf("%s", buffer); 
} 
close(sockfd); 
return 0; 
}