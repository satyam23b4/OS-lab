#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

// Global variables for the algorithm
int available[MAX_RESOURCES];  // Available resources
int maximum[MAX_PROCESSES][MAX_RESOURCES];  // Maximum resource demand of each process
int allocation[MAX_PROCESSES][MAX_RESOURCES];  // Resources allocated to each process
int need[MAX_PROCESSES][MAX_RESOURCES];  // Remaining resources needed by each process

// Function to check if the system is in a safe state
bool isSafe(int processes[], int num_processes, int resources) {
    int work[MAX_RESOURCES];  // Work is the available resources
    bool finish[MAX_PROCESSES] = {false};  // Finish indicates if a process has finished
    int safe_sequence[MAX_PROCESSES];  // To store the safe sequence
    int count = 0;

    // Initialize work with available resources
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    // Find a safe sequence of processes
    while (count < num_processes) {
        bool found = false;
        for (int p = 0; p < num_processes; p++) {
            if (!finish[p]) {  // If the process is not finished
                int j;
                for (j = 0; j < resources; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }

                // If all resources are available for this process
                if (j == resources) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[p][k];  // Release resources
                    }

                    safe_sequence[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            // If no process can be allocated resources
            printf("The system is not in a safe state.\n");
            return false;
        }
    }

    // If the system is in a safe state, print the safe sequence
    printf("The system is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");

    return true;
}

// Resource-request algorithm to check if a request can be granted safely
bool requestResources(int process_id, int request[], int num_processes, int resources) {
    // Check if the request is greater than need
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process_id][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
    }

    // Check if the request is greater than available
    for (int i = 0; i < resources; i++) {
        if (request[i] > available[i]) {
            printf("Resources are not available for Process %d.\n", process_id);
            return false;
        }
    }

    // Pretend to allocate the requested resources
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    // Check if the system is still in a safe state
    if (isSafe((int[]){0, 1, 2, 3, 4}, num_processes, resources)) {
        return true;  // Request is granted
    } else {
        // If not in a safe state, roll back the allocation
        printf("Request cannot be granted. Rolling back.\n");
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        return false;
    }
}

int main() {
    int processes[MAX_PROCESSES] = {0, 1, 2, 3, 4};  // Processes IDs
    int num_processes = MAX_PROCESSES;
    int resources = MAX_RESOURCES;

    // Input available resources
    printf("Enter available resources (R1 R2 R3): ");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    // Input maximum demand matrix
    printf("Enter maximum resource demand matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] = maximum[i][j] - allocation[i][j];  // Calculate the need matrix
        }
    }

    // Check if the system is in a safe state
    isSafe(processes, num_processes, resources);

    // Requesting resources for a specific process
    int process_id;
    printf("Enter the process ID making a request (0-%d): ", num_processes - 1);
    scanf("%d", &process_id);

    int request[MAX_RESOURCES];
    printf("Enter resource request for Process %d (R1 R2 R3): ", process_id);
    for (int i = 0; i < resources; i++) {
        scanf("%d", &request[i]);
    }

    // Execute resource request algorithm
    requestResources(process_id, request, num_processes, resources);

    return 0;
}
