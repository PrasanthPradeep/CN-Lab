#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/select.h> 
#define PORT 8080 
#define MAX_CLIENTS 10 
#define BUFFER_SIZE 1024 
int main() { 
int server_fd, new_socket, client_socket[MAX_CLIENTS]; 
struct sockaddr_in address; 
int addrlen = sizeof(address); 
char buffer[BUFFER_SIZE]; 
fd_set readfds; 
int max_sd, sd, activity; 
// Initialize all client sockets to 0 
for (int i = 0; i < MAX_CLIENTS; i++) 
client_socket[i] = 0; 
// Create socket 
server_fd = socket(AF_INET, SOCK_STREAM, 0); 
address.sin_family = AF_INET; 
address.sin_addr.s_addr = INADDR_ANY; 
address.sin_port = htons(PORT); 
bind(server_fd, (struct sockaddr *)&address, sizeof(address)); 
listen(server_fd, 3); 
printf("Chat server started on port %d...\n", PORT); 
while (1) { 
FD_ZERO(&readfds); 
FD_SET(server_fd, &readfds); 
max_sd = server_fd; 
for (int i = 0; i < MAX_CLIENTS; i++) { 
sd = client_socket[i]; 
if (sd > 0) 
FD_SET(sd, &readfds); 
if (sd > max_sd) 
max_sd = sd; 
} 
activity = select(max_sd + 1, &readfds, NULL, NULL, NULL); 
// New connection 
if (FD_ISSET(server_fd, &readfds)) { 
new_socket = accept(server_fd,  (struct sockaddr *)&address,(socklen_t *)&addrlen); 
printf("New client connected: %d\n", new_socket); 
  for (int i = 0; i < MAX_CLIENTS; i++) { 
                if (client_socket[i] == 0) { 
                    client_socket[i] = new_socket; 
                    break; 
                } 
            } 
        } 
 
        // Message from client 
        for (int i = 0; i < MAX_CLIENTS; i++) { 
            sd = client_socket[i]; 
 
            if (FD_ISSET(sd, &readfds)) { 
                int valread = read(sd, buffer, BUFFER_SIZE); 
                if (valread == 0) { 
                    close(sd); 
                    client_socket[i] = 0; 
                    printf("Client disconnected\n"); 
                } 
  else { 
                    buffer[valread] = '\0'; 
                    printf("Client %d: %s", sd, buffer); 
 
                    // Broadcast message 
for (int j = 0; j < MAX_CLIENTS; j++) { 
if (client_socket[j] != 0 && client_socket[j] != sd) { 
send(client_socket[j], buffer, strlen(buffer), 0); 
} 
} 
} 
} 
} 
} 
return 0; 
}