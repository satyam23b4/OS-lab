#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STRINGS 100
#define MAX_LENGTH 100

void bubbleSort(char arr[][MAX_LENGTH], int n) {
    char temp[MAX_LENGTH];
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                // Swap
                strcpy(temp, arr[j]);
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}

void quickSort(char arr[][MAX_LENGTH], int low, int high) {
    if (low < high) {
        // Partitioning index
        char pivot[MAX_LENGTH];
        strcpy(pivot, arr[high]);
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (strcmp(arr[j], pivot) < 0) {
                i++;
                char temp[MAX_LENGTH];
                strcpy(temp, arr[i]);
                strcpy(arr[i], arr[j]);
                strcpy(arr[j], temp);
            }
        }
        char temp[MAX_LENGTH];
        strcpy(temp, arr[i + 1]);
        strcpy(arr[i + 1], arr[high]);
        strcpy(arr[high], temp);
        
        int partitionIndex = i + 1;
        quickSort(arr, low, partitionIndex - 1);
        quickSort(arr, partitionIndex + 1, high);
    }
}

int main() {
    int n;
    char strings[MAX_STRINGS][MAX_LENGTH];

    // Read number of strings
    printf("Enter the number of strings: ");
    scanf("%d", &n);
    
    // Read the strings
    printf("Enter the strings:\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }

    // Create two child processes
    pid_t pid1 = fork();
    
    if (pid1 < 0) {
        printf("Failed to create first child process.\n");
        return 1;
    }

    if (pid1 == 0) {
        // First child process for bubble sort
        printf("Child 1 (Bubble Sort):\n");
        bubbleSort(strings, n);
        for (int i = 0; i < n; i++) {
            printf("%s ", strings[i]);
        }
        printf("\n");
        exit(0);  // Terminate first child process
    } else {
        // Create second child process
        pid_t pid2 = fork();
        
        if (pid2 < 0) {
            printf("Failed to create second child process.\n");
            return 1;
        }

        if (pid2 == 0) {
            // Second child process for quicksort
            printf("Child 2 (Quick Sort):\n");
            quickSort(strings, 0, n - 1);
            for (int i = 0; i < n; i++) {
                printf("%s ", strings[i]);
            }
            printf("\n");
            exit(0);  // Terminate second child process
        }
    }

    // Parent process waits for any child to terminate
    int status;
    pid_t terminatedChild = wait(&status);
    
    if (terminatedChild == pid1) {
        printf("First child (Bubble Sort) has terminated.\n");
    } else {
        printf("Second child (Quick Sort) has terminated.\n");
    }

    return 0;
}
