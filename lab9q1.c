#include <stdio.h>
#include <stdlib.h>

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int *allocation = (int *)malloc(processes * sizeof(int));  // Allocation array to store block number allocated to each process
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;  // Initially, no block is allocated to any process
    }

    // First Fit Algorithm
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to process i
                allocation[i] = j;
                blockSize[j] -= processSize[i];  // Reduce available memory in this block
                break;
            }
        }
    }

    // Display allocation results
    printf("\nFirst Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    free(allocation);
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes) {
    int *allocation = (int *)malloc(processes * sizeof(int));  // Allocation array to store block number allocated to each process
    for (int i = 0; i < processes; i++) {
        allocation[i] = -1;  // Initially, no block is allocated to any process
    }

    // Best Fit Algorithm
    for (int i = 0; i < processes; i++) {
        int bestIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        // If a suitable block is found, allocate it
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];  // Reduce available memory in this block
        }
    }

    // Display allocation results
    printf("\nBest Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }

    free(allocation);
}

int main() {
    int blocks, processes;

    // Input number of memory blocks and processes
    printf("Enter the number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    // Dynamically allocate memory for block sizes and process sizes
    int *blockSize = (int *)malloc(blocks * sizeof(int));
    int *processSize = (int *)malloc(processes * sizeof(int));

    // Input sizes of memory blocks
    printf("Enter the sizes of the memory blocks:\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input sizes of processes
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < processes; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Run First Fit and Best Fit algorithms
    firstFit(blockSize, blocks, processSize, processes);

    // Reset block sizes (reallocate memory as First Fit modifies the block sizes)
    printf("\nRe-enter the sizes of the memory blocks (for Best Fit algorithm):\n");
    for (int i = 0; i < blocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    bestFit(blockSize, blocks, processSize, processes);

    // Free dynamically allocated memory
    free(blockSize);
    free(processSize);

    return 0;
}
