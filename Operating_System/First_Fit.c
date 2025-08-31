// First Fit Memeory allocation In OS

#include <stdio.h>

int main() {
    int i, j, nb, np;

    
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    int blockSize[nb], blockAllocated[nb]; 

    printf("Enter sizes of memory blocks:\n");
    for(i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        blockAllocated[i] = 0; 
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);

    int processSize[np], allocation[np]; 

    printf("Enter sizes of processes:\n");
    for(i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
        allocation[i] = -1;
    }

    
    for(i = 0; i < np; i++) {
        for(j = 0; j < nb; j++) {
            if(blockAllocated[j] == 0 && blockSize[j] >= processSize[i]) {
                allocation[i] = j;        
                blockAllocated[j] = 1;    
                break;                     
            }
        }
    }

    
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\n");
    for(i = 0; i < np; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if(allocation[i] != -1)
            printf("%d\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("Not Allocated\t-\n");
    }

    return 0;
}
