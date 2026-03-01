#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#define SIZE 3 
int main() { 
    int sockfd; 
    struct sockaddr_in serverAddr; 
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE]; 
    socklen_t addr_size; 
 
    // Sample input matrices 
    printf("Enter Matrix A (3x3):\n"); 
    for(int i = 0; i < SIZE; i++) 
        for(int j = 0; j < SIZE; j++) 
            scanf("%d", &A[i][j]); 
 
    printf("Enter Matrix B (3x3):\n"); 
    for(int i = 0; i < SIZE; i++) 
        for(int j = 0; j < SIZE; j++) 
            scanf("%d", &B[i][j]); 
 
    // Create UDP socket 
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
 
    serverAddr.sin_family = AF_INET; 
    serverAddr.sin_port = htons(8080); 
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
 
    addr_size = sizeof(serverAddr); 
 
    // Send matrices to server 
    sendto(sockfd, A, sizeof(A), 0, (struct sockaddr*)&serverAddr, 
addr_size); 
    sendto(sockfd, B, sizeof(B), 0, (struct sockaddr*)&serverAddr, 
addr_size); 
 
    // Receive result matrix 
    recvfrom(sockfd, C, sizeof(C), 0, NULL, NULL); 
 
    // Print result 
    printf("\nResult Matrix (A × B):\n"); 
    for(int i = 0; i < SIZE; i++) { 
        for(int j = 0; j < SIZE; j++) { 
            printf("%d ", C[i][j]); 
        } 
        printf("\n"); 
    } 
    close(sockfd); 
    return 0; 
}