#include <stdio.h>

// Helper function to print the allocation results
void printAllocation(int processSize[], int n, int allocation[]) {
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            // Adding 1 to block index for human-readable output (1-based index)
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
    printf("-------------------------------------------------\n");
}

// 1. First Fit Algorithm
void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    
    // Initialize all allocations to -1 (unallocated)
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate process to block
                allocation[i] = j;
                // Reduce available memory in this block
                blockSize[j] = 0;
                break; // Move to the next process
            }
        }
    }

    printf("\n--- First Fit Allocation ---");
    printAllocation(processSize, n, allocation);
}

// 2. Best Fit Algorithm
void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }

        if (bestIdx != -1) {
            // Allocate process to the best block found
            allocation[i] = bestIdx;
            blockSize[bestIdx]=0;
        }
    }

    printf("\n--- Best Fit Allocation ---");
    printAllocation(processSize, n, allocation);
}

// 3. Worst Fit Algorithm
void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        if (worstIdx != -1) {
            // Allocate process to the worst (largest) block found
            allocation[i] = worstIdx;
            blockSize[worstIdx]=0;
        }
    }

    printf("\n--- Worst Fit Allocation ---");
    printAllocation(processSize, n, allocation);
}

int main() {
    int m, n;

    // 1. Get Memory Blocks Input
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    
    int originalBlocks[m];
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &originalBlocks[i]);
    }

    // 2. Get Processes Input
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    
    int processSize[n];
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // 3. Create independent copies of the block arrays
    // Since the algorithms modify block sizes, we need fresh copies for each run.
    int blocks1[m], blocks2[m], blocks3[m];
    for (int i = 0; i < m; i++) {
        blocks1[i] = originalBlocks[i];
        blocks2[i] = originalBlocks[i];
        blocks3[i] = originalBlocks[i];
    }

    // 4. Run the Algorithms
    firstFit(blocks1, m, processSize, n);
    bestFit(blocks2, m, processSize, n);
    worstFit(blocks3, m, processSize, n);

    return 0;
}