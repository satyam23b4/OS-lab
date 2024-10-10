#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void sortStrings(char *arr[], int n) {
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[i], arr[j]) > 0) {
                // Swap strings if they are in the wrong order
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // Check if sufficient arguments are passed
    if (argc < 2) {
        printf("Please provide a set of strings as command line arguments.\n");
        return 1;
    }

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        // Error handling if fork fails
        printf("Failed to create a child process.\n");
        return 1;
    }

    if (pid == 0) {
        // Child process block
        printf("Child Process:\n");
        printf("Sorted strings:\n");

        // Sort the strings (excluding the program name, argv[0])
        sortStrings(&argv[1], argc - 1);

        // Display sorted strings
        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        exit(0);  // Terminate child process
    } else {
        // Parent process block

        // Wait for the child process to complete
        wait(NULL);

        // Display unsorted strings
        printf("Parent Process:\n");
        printf("Unsorted strings:\n");

        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
    }

    return 0;
}
