#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Global variables
int available[MAX_RESOURCES];  // Available resources
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Resources allocated to each process
int request[MAX_PROCESSES][MAX_RESOURCES];  // Resources currently requested by each process

// Function to check for deadlock
void detectDeadlock(int num_processes, int num_resources) {
    bool finish[MAX_PROCESSES] = {false};  // Keeps track of finished processes
    int work[MAX_RESOURCES];  // Available resources (work vector)
    int deadlocked_processes[MAX_PROCESSES];  // To store deadlocked processes
    int deadlock_count = 0;  // Number of deadlocked processes

    // Initialize the work array to the available resources
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Try to find a sequence where each process can finish
    while (1) {
        bool found = false;
        
        for (int p = 0; p < num_processes; p++) {
            if (!finish[p]) {
                // Check if the current process's requests can be satisfied
                int j;
                for (j = 0; j < num_resources; j++) {
                    if (request[p][j] > work[j]) {
                        break;
                    }
                }

                // If all requests of the process can be satisfied
                if (j == num_resources) {
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[p][k];  // Release the allocated resources
                    }
                    finish[p] = true;  // Mark process as finished
                    found = true;
                }
            }
        }

        // If no process was found in this iteration, break
        if (!found) {
            break;
        }
    }

    // Check for deadlock by finding unfinished processes
    for (int i = 0; i < num_processes; i++) {
        if (!finish[i]) {
            deadlocked_processes[deadlock_count++] = i;
        }
    }

    // Output deadlock information
    if (deadlock_count > 0) {
        printf("Deadlock detected! The following processes are in deadlock: ");
        for (int i = 0; i < deadlock_count; i++) {
            printf("P%d ", deadlocked_processes[i]);
        }
        printf("\n");
    } else {
        printf("No deadlock detected. All processes can complete.\n");
    }
}

int main() {
    int num_processes = MAX_PROCESSES;
    int num_resources = MAX_RESOURCES;

    // Input available resources
    printf("Enter available resources (R1 R2 R3): ");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    // Input allocation matrix (resources allocated to each process)
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input request matrix (resources requested by each process)
    printf("Enter request matrix (resources needed by each process):\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    // Detect deadlock
    detectDeadlock(num_processes, num_resources);

    return 0;
}
