#include <stdio.h> 
int main()  
{ 
    int bucket_size, output_rate, n; 
    int packet_size; 
    int bucket_content = 0; 
    int i; 
    printf("Enter Bucket Size: "); 
    scanf("%d", &bucket_size); 
    printf("Enter Output Rate: "); 
    scanf("%d", &output_rate); 
    printf("Enter Number of Packets: "); 
    scanf("%d", &n); 
    for(i = 1; i <= n; i++)  
{ 
 printf("\nEnter size of packet %d: ", i); 
        scanf("%d", &packet_size); 
        printf("Packet %d size = %d\n", i, packet_size); 
        if(packet_size > bucket_size) 
       { 
            printf("Packet Dropped (Too Large)\n"); 
        } 
        else if(bucket_content + packet_size > bucket_size) 
      { 
         printf("Packet Dropped (Bucket Overflow)\n"); 
        } 
        else 
        {  
           bucket_content += packet_size; 
            printf("Packet Accepted\n"); 
        } 
        printf("Bucket Content before leak: %d\n", bucket_content); 
 
        // Leak process 
        if(bucket_content > output_rate) 
            bucket_content -= output_rate; 
        else 
            bucket_content = 0; 
 
        printf("Bucket Content after leak: %d\n", bucket_content); 
    } 
 
    return 0; 
}