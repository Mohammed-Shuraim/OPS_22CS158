/*Write a C program to simulate the following contiguous memory allocation
techniques
a) Worst-fit
b) Best-fit
c) First-fit 
cs 158 */

#include <stdio.h>

#define MAX 25

void firstFit(int numberOfBlocks, int numberOfFiles, int blockSize[], int fileSize[]) {
    int fragment[MAX], blockFlag[MAX] = {0}, fileFlag[MAX] = {0};
    int i, j, temp;

    for (i = 1; i <= numberOfFiles; i++) {
        for (j = 1; j <= numberOfBlocks; j++) {
            if (blockFlag[j] != 1) {
                temp = blockSize[j] - fileSize[i];
                if (temp >= 0) {
                    fileFlag[i] = j;
                    fragment[i] = temp;
                    blockFlag[j] = 1;
                    break;
                }
            }
        }
    }

    printf("\nMemory Management Scheme - First Fit\n");
    printf("File No:\tFile Size:\tBlock No:\tBlock Size:\tFragment\n");
    for (i = 1; i <= numberOfFiles; i++) {
        printf("%d\t\t%d\t\t", i, fileSize[i]);
        if (fileFlag[i] != 0) {
            printf("%d\t\t%d\t\t%d\n", fileFlag[i], blockSize[fileFlag[i]], fragment[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

void bestFit(int numberOfBlocks, int numberOfFiles, int blockSize[], int fileSize[]) {
    int fragment[MAX], blockFlag[MAX] = {0}, fileFlag[MAX] = {0};
    int i, j, temp, lowest = 10000;

    for (i = 1; i <= numberOfFiles; i++) {
        for (j = 1; j <= numberOfBlocks; j++) {
            if (blockFlag[j] != 1) {
                temp = blockSize[j] - fileSize[i];
                if (temp >= 0 && lowest > temp) {
                    fileFlag[i] = j;
                    lowest = temp;
                }
            }
        }
        fragment[i] = lowest;
        blockFlag[fileFlag[i]] = 1;
        lowest = 10000;
    }

    printf("\nMemory Management Scheme - Best Fit\n");
    printf("File No:\tFile Size:\tBlock No:\tBlock Size:\tFragment\n");
    for (i = 1; i <= numberOfFiles; i++) {
        printf("%d\t\t%d\t\t", i, fileSize[i]);
        if (fileFlag[i] != 0) {
            printf("%d\t\t%d\t\t%d\n", fileFlag[i], blockSize[fileFlag[i]], fragment[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

void worstFit(int numberOfBlocks, int numberOfFiles, int blockSize[], int fileSize[]) {
    int fragment[MAX], blockFlag[MAX] = {0}, fileFlag[MAX] = {0};
    int i, j, temp, highest = 0;

    for (i = 1; i <= numberOfFiles; i++) {
        for (j = 1; j <= numberOfBlocks; j++) {
            if (blockFlag[j] != 1) {
                temp = blockSize[j] - fileSize[i];
                if (temp >= 0 && highest < temp) {
                    fileFlag[i] = j;
                    highest = temp;
                }
            }
        }
        fragment[i] = highest;
        blockFlag[fileFlag[i]] = 1;
        highest = 0;
    }

    printf("\nMemory Management Scheme - Worst Fit\n");
    printf("File No:\tFile Size:\tBlock No:\tBlock Size:\tFragment\n");
    for (i = 1; i <= numberOfFiles; i++) {
        printf("%d\t\t%d\t\t", i, fileSize[i]);
        if (fileFlag[i] != 0) {
            printf("%d\t\t%d\t\t%d\n", fileFlag[i], blockSize[fileFlag[i]], fragment[i]);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[MAX], fileSize[MAX], numberOfBlocks, numberOfFiles;

    printf("\nEnter the number of blocks: ");
    scanf("%d", &numberOfBlocks);
    printf("Enter the number of files: ");
    scanf("%d", &numberOfFiles);
    printf("\nEnter the size of the blocks:\n");
    for (int i = 1; i <= numberOfBlocks; i++) {
        printf("Block %d: ", i);
        scanf("%d", &blockSize[i]);
    }
    printf("Enter the size of the files:\n");
    for (int i = 1; i <= numberOfFiles; i++) {
        printf("File %d: ", i);
        scanf("%d", &fileSize[i]);
    }

    int blockSizeFirstFit[MAX], blockSizeBestFit[MAX], blockSizeWorstFit[MAX];
    for (int i = 1; i <= numberOfBlocks; i++) {
        blockSizeFirstFit[i] = blockSize[i];
        blockSizeBestFit[i] = blockSize[i];
        blockSizeWorstFit[i] = blockSize[i];
    }

    firstFit(numberOfBlocks, numberOfFiles, blockSizeFirstFit, fileSize);
    bestFit(numberOfBlocks, numberOfFiles, blockSizeBestFit, fileSize);
    worstFit(numberOfBlocks, numberOfFiles, blockSizeWorstFit, fileSize);

    return 0;
}
