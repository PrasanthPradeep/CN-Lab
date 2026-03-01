#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#define PORT 8080 
#define BUFFER_SIZE 1024 
int main() { 
int server_fd, client_fd; 
struct sockaddr_in server_addr, client_addr; 
socklen_t addr_len = sizeof(client_addr); 
char filename[BUFFER_SIZE]; 
char buffer[BUFFER_SIZE]; 
pid_t pid; 
// Create TCP socket 
server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    // Server address 
    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT); 
    // Bind socket 
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); 
    // Listen 
    listen(server_fd, 5); 
    printf("Concurrent File Server running on port %d...\n", PORT); 
    while (1) { 
        // Accept client 
        client_fd = accept(server_fd,(struct sockaddr *)&client_addr, &addr_len); 
        // Create child process 
        pid = fork(); 
        if (pid == 0) { // Child process 
            close(server_fd); 
            // Read filename from client 
            int n = read(client_fd, filename, BUFFER_SIZE - 1);
            filename[n] = '\0'; 
            FILE *fp = fopen(filename, "r"); 
            pid_t server_pid = getpid(); 
            if (fp == NULL) { 
                snprintf(buffer, BUFFER_SIZE, 
                         "Server PID: %d\nFile not found\n", server_pid); 
                send(client_fd, buffer, strlen(buffer), 0); 
            } else { 
                snprintf(buffer, BUFFER_SIZE, 
                         "Server PID: %d\nFile content:\n", server_pid); 
                send(client_fd, buffer, strlen(buffer), 0); 
                while (fgets(buffer, BUFFER_SIZE, fp) != NULL) { 
                    send(client_fd, buffer, strlen(buffer), 0); 
                } 
                fclose(fp); 
            } 
           close(client_fd); 
            exit(0); 
        } 
        // Parent process 
        close(client_fd); 
    } 
 
    return 0; 
}