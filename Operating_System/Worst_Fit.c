//Worst Fit Memory Allocation in OS

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
        int worstIdx = -1;
        for(j = 0; j < nb; j++) {
            if(blockAllocated[j] == 0 && blockSize[j] >= processSize[i]) {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if(worstIdx != -1) {
            // Allocate block to process
            allocation[i] = worstIdx;
            blockAllocated[worstIdx] = 1; // Mark block as used
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
