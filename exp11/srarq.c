#include <stdio.h> 
#include <stdlib.h> 
 
int main() { 
    int n, windowSize; 
    int i, j; 
    int ack[50]; 
 
    printf("Enter number of frames: "); 
    scanf("%d", &n); 
 
    printf("Enter window size: "); 
    scanf("%d", &windowSize); 
 
    // Initialize ACK array 
    for (i = 0; i < n; i++) 
        ack[i] = 0; 
 
    printf("\n--- Selective Repeat ARQ Simulation ---\n"); 
 
    for (i = 0; i < n; i += windowSize) { 
 
        // Send frames in the window 
        for (j = i; j < i + windowSize && j < n; j++) { 
            printf("Frame %d sent\n", j); 
        } 
 
        // Receive ACKs 
        for (j = i; j < i + windowSize && j < n; j++) { 
            if (ack[j] == 0) { 
                printf("Did receiver get frame %d correctly? (1=Yes, 0=No): ", j); 
                scanf("%d", &ack[j]); 
 
                if (ack[j] == 0) { 
                    printf("Frame %d lost! Retransmitting frame %d\n", j, j); 
                    printf("Frame %d resent successfully\n", j); 
                    ack[j] = 1; 
                } 
            } 
        } 
        printf("\n"); 
    } 
 
    printf("All frames received successfully!\n"); 
    return 0; 
}