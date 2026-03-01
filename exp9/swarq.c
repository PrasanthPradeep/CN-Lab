#include <stdio.h> 
#include <stdlib.h> 
 
int main() 
{ 
    int frame = 0; 
    int ack; 
    int choice; 
 
    while (frame < 10)   // simulate 10 frames 
    { 
        printf("\nSender: Sending frame %d", frame); 
 
        // Randomly decide ACK received or lost 
        ack = rand() % 2; 
 
        if (ack == 1) 
        { 
            printf("\nReceiver: ACK received for frame %d", frame); 
            frame++;   // move to next frame 
        } 
        else 
        { 
            printf("\nReceiver: ACK lost for frame %d", frame); 
            printf("\nSender: Timeout! Resending frame %d", frame); 
        } 
 
        printf("\n-----------------------------------"); 
    } 
 
    printf("\nAll frames transmitted successfully.\n"); 
    return 0; 
} 