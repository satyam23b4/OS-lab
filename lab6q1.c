#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

typedef struct {
    int pid;            // Process ID
    int burstTime;     // Burst time
    int arrivalTime;   // Arrival time
    int remainingTime; // Remaining time for preemptive SJF and RR
    int waitingTime;   // Waiting time
    int turnaroundTime; // Turnaround time
    int priority;      // Priority for non-preemptive priority scheduling
} Process;

// Function to find the waiting time for Preemptive SJF
void findWaitingTimePreemptiveSJF(Process proc[], int n) {
    int completed = 0, t = 0, min_index, min_burst_time;
    bool check = false;

    while (completed < n) {
        min_burst_time = 9999999;
        min_index = -1;

        // Find the process with the minimum remaining time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= t && proc[i].remainingTime > 0 && 
                proc[i].remainingTime < min_burst_time) {
                min_burst_time = proc[i].remainingTime;
                min_index = i;
                check = true;
            }
        }

        if (check) {
            proc[min_index].remainingTime--;
            t++;
            if (proc[min_index].remainingTime == 0) {
                completed++;
                proc[min_index].turnaroundTime = t - proc[min_index].arrivalTime;
                proc[min_index].waitingTime = proc[min_index].turnaroundTime - proc[min_index].burstTime;
            }
        } else {
            t++; // No process is ready, so increase time
        }
    }
}

// Function to find waiting time for Round Robin
void findWaitingTimeRR(Process proc[], int n, int quantum) {
    int remainingTime[MAX_PROCESSES];
    for (int i = 0; i < n; i++)
        remainingTime[i] = proc[i].burstTime;

    int t = 0; // Current time
    while (1) {
        bool done = true;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                done = false; // Process is not done
                if (remainingTime[i] > quantum) {
                    t += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    t = t + remainingTime[i];
                    proc[i].waitingTime = t - proc[i].burstTime - proc[i].arrivalTime;
                    remainingTime[i] = 0;
                }
            }
        }
        if (done)
            break;
    }
}

// Function to find waiting time for Non-Preemptive Priority Scheduling
void findWaitingTimePriority(Process proc[], int n) {
    int completed = 0, t = 0;
    bool check = false;

    while (completed < n) {
        int idx = -1;
        int min_priority = 9999999;

        // Find the process with the highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= t && proc[i].burstTime > 0 &&
                proc[i].priority < min_priority) {
                min_priority = proc[i].priority;
                idx = i;
                check = true;
            }
        }

        if (check) {
            t += proc[idx].burstTime;
            proc[idx].burstTime = 0;
            proc[idx].turnaroundTime = t - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
            completed++;
        } else {
            t++; // No process is ready, so increase time
        }
    }
}

// Function to calculate turnaround time
void findTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++)
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
}

// Function to display the result
void display(Process proc[], int n) {
    printf("\nProcess ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].burstTime,
               proc[i].waitingTime, proc[i].turnaroundTime);
    }
}

// Main function
int main() {
    int choice, n;
    Process proc[MAX_PROCESSES];

    while (1) {
        printf("\nMenu:\n");
        printf("1. Preemptive Shortest Job First Scheduling\n");
        printf("2. Round Robin Scheduling\n");
        printf("3. Non-Preemptive Priority Scheduling\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4) {
            break; // Exit the program
        }

        printf("Enter number of processes: ");
        scanf("%d", &n);

        for (int i = 0; i < n; i++) {
            printf("Enter Process ID, Arrival Time, Burst Time, and Priority (for priority scheduling): ");
            scanf("%d %d %d %d", &proc[i].pid, &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
            proc[i].remainingTime = proc[i].burstTime; // For preemptive SJF and RR
            proc[i].waitingTime = 0; // Initialize waiting time
            proc[i].turnaroundTime = 0; // Initialize turnaround time
        }

        switch (choice) {
            case 1: // Preemptive SJF
                findWaitingTimePreemptiveSJF(proc, n);
                findTurnaroundTime(proc, n);
                display(proc, n);
                break;
            case 2: // Round Robin
                {
                    int quantum;
                    printf("Enter time quantum: ");
                    scanf("%d", &quantum);
                    findWaitingTimeRR(proc, n, quantum);
                    findTurnaroundTime(proc, n);
                    display(proc, n);
                }
                break;
            case 3: // Non-Preemptive Priority Scheduling
                findWaitingTimePriority(proc, n);
                findTurnaroundTime(proc, n);
                display(proc, n);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
