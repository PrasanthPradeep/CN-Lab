#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#define PORT 8080 
#define BUFFER_SIZE 1024 
int main() { 
int sockfd; 
char buffer[BUFFER_SIZE]; 
struct sockaddr_in server_addr; 
socklen_t addr_len = sizeof(server_addr); 
// Create UDP socket 
sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
// Server address 
server_addr.sin_family = AF_INET; 
server_addr.sin_port = htons(PORT); 
inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); 
// Send request to server 
sendto(sockfd, "Time Request", strlen("Time Request"), 0, 
(struct sockaddr *)&server_addr, addr_len); 
// Receive response from server 
recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, 
&addr_len); 
printf("Time from server: %s\n", buffer); 
close(sockfd); 
return 0; 
}