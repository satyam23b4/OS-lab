#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    // Create a child process using fork()
    pid = fork();

    // Error handling if fork fails
    if (pid < 0) {
        printf("Failed to create a child process.\n");
        return 1;
    }
    
    // This block is executed by the child process
    if (pid == 0) {
        // Get the process ID (PID) of the child and the parent's PID (PPID)
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());        // PID of the child process
        printf("PPID: %d\n", getppid());      // PID of the parent process
        printf("Message: This is the child process.\n");
    } 
    // This block is executed by the parent process
    else {
        // Get the process ID (PID) of the parent and the parent's parent PID (PPID)
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());        // PID of the parent process
        printf("PPID: %d\n", getppid());      // PID of the parent's parent process
        printf("Message: This is the parent process.\n");
    }

    return 0;
}
