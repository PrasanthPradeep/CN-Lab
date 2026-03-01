#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
 
#define MAX_FRAMES 10   // Total number of frames to send 
#define WINDOW_SIZE 4   // Size of the sliding window 
 
// Function to simulate random frame loss 
int isFrameLost() { 
    return rand() % 5 == 0; // 20% chance of loss 
} 
 
int main() { 
    int totalFrames = MAX_FRAMES; 
    int windowSize = WINDOW_SIZE; 
    int base = 0;      // Oldest unacknowledged frame 
    int nextSeqNum = 0; 
    int ack; 
     
    srand(time(0)); // Initialize random seed 
 
    printf("Go-Back-N ARQ Simulation\n"); 
    printf("Total frames: %d, Window size: %d\n\n", totalFrames, windowSize); 
 
    while (base < totalFrames) 
    { 
        // Send frames in window 
        while (nextSeqNum < base + windowSize && nextSeqNum < totalFrames)  
         { 
                printf("Frame %d sent successfully.\n", nextSeqNum); 
                 nextSeqNum++; 
        } 
 
        // Wait for ACKs 
        ack = base; 
        while (ack < nextSeqNum) 
        { 
            if (isFrameLost()) 
            { 
                printf("ACK for Frame %d lost! Retransmitting from Frame %d\n", ack, ack); 
                nextSeqNum = ack; // Go back N 
                break; 
            }  
             else 
             { 
                    printf("ACK received for Frame %d\n", ack); 
                     ack++; 
            } 
        } 
        base = ack; // Slide the window 
        printf("\n"); 
    } 
 
    printf("All frames transmitted successfully!\n"); 
    return 0; 
} 