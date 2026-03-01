#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <time.h> 
#define PORT 8080 
#define BUFFER_SIZE 1024 
int main() { 
int sockfd; 
char buffer[BUFFER_SIZE]; 
struct sockaddr_in server_addr, client_addr; 
socklen_t addr_len = sizeof(client_addr); 
time_t now; 
// Create UDP socket 
sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
// Server address configuration 
server_addr.sin_family = AF_INET; 
server_addr.sin_addr.s_addr = INADDR_ANY; 
server_addr.sin_port = htons(PORT); 
// Bind socket 
bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)); 
printf("UDP Concurrent Server running on port %d...\n", PORT); 
while (1) { 
// Receive request from any client 
recvfrom(sockfd, buffer, BUFFER_SIZE, 0, 
(struct sockaddr *)&client_addr, &addr_len); 
printf("Request received from client\n"); 
// Get current time 
now = time(NULL); 
snprintf(buffer, BUFFER_SIZE, "%s", ctime(&now)); 
// Send response to the same client 
sendto(sockfd, buffer, strlen(buffer), 0, 
(struct sockaddr *)&client_addr, addr_len); 
} 
close(sockfd); 
return 0; 
}