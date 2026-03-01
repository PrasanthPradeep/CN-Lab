#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
 
#define SIZE 3   // 3x3 matrix 
 
int main() { 
    int sockfd; 
    struct sockaddr_in serverAddr, clientAddr; 
    socklen_t addr_size; 
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE]; 
 
    // Create UDP socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
 
    serverAddr.sin_family = AF_INET; 
    serverAddr.sin_port = htons(8080); 
    serverAddr.sin_addr.s_addr = INADDR_ANY; 
 
    // Bind socket 
    bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)); 
 
    addr_size = sizeof(clientAddr); 
 
    printf("Server waiting for matrices...\n"); 
 
    // Receive Matrix A 
    recvfrom(sockfd, A, sizeof(A), 0, (struct sockaddr*)&clientAddr, 
&addr_size); 
 
    // Receive Matrix B 
    recvfrom(sockfd, B, sizeof(B), 0, (struct sockaddr*)&clientAddr, 
&addr_size); 
 
    // Multiply A×B = C 
    for (int i = 0; i < SIZE; i++) { 
        for (int j = 0; j < SIZE; j++) { 
            C[i][j] = 0; 
            for (int k = 0; k < SIZE; k++) { 
                C[i][j] += A[i][k] * B[k][j]; 
            } 
        } 
    } 
 
    // Send result back 
    sendto(sockfd, C, sizeof(C), 0, (struct sockaddr*)&clientAddr, 
addr_size); 
 
    printf("Matrix multiplication completed and result sent.\n"); 
 
    close(sockfd); 
    return 0; 
}