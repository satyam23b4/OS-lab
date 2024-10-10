#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;             // Process ID
    int arrivalTime;     // Arrival time
    int burstTime;       // Burst time
    int waitingTime;     // Waiting time
    int turnaroundTime;  // Turnaround time
} Process;

// Function to sort processes by arrival time
void sortByArrival(Process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrivalTime > proc[j].arrivalTime) {
                Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void calculateTimes(Process proc[], int n) {
    int completeTime[MAX_PROCESSES]; // Completion time for each process
    int i, j, time = 0, completed = 0;
    
    while (completed < n) {
        int minIndex = -1;
        int minBurstTime = 99999;

        // Find the process with the shortest burst time that has arrived
        for (i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= time && proc[i].burstTime > 0) {
                if (proc[i].burstTime < minBurstTime) {
                    minBurstTime = proc[i].burstTime;
                    minIndex = i;
                }
            }
        }

        // If no process is ready, increase the time
        if (minIndex == -1) {
            time++;
        } else {
            // Process the selected process
            time += proc[minIndex].burstTime;
            proc[minIndex].waitingTime = time - proc[minIndex].arrivalTime - proc[minIndex].burstTime;
            proc[minIndex].turnaroundTime = time - proc[minIndex].arrivalTime;
            completeTime[minIndex] = time;
            proc[minIndex].burstTime = 0; // Mark as completed
            completed++;
        }
    }
}

// Function to display the results
void display(Process proc[], int n) {
    printf("\nProcess ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
               proc[i].pid, 
               proc[i].arrivalTime, 
               proc[i].burstTime + proc[i].waitingTime, // Original burst time
               proc[i].waitingTime, 
               proc[i].turnaroundTime);
    }
}

// Main function
int main() {
    int n;
    Process proc[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Process ID, Arrival Time, and Burst Time: ");
        scanf("%d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].waitingTime = 0;       // Initialize waiting time
        proc[i].turnaroundTime = 0;    // Initialize turnaround time
    }

    // Sort processes by arrival time
    sortByArrival(proc, n);
    
    // Calculate waiting and turnaround times
    calculateTimes(proc, n);
    
    // Display the results
    display(proc, n);

    return 0;
}
