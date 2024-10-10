#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t chopsticks[NUM_PHILOSOPHERS];  // Semaphores for chopsticks

// Function to simulate philosopher's behavior
void *philosopher(void *arg) {
    int philosopher_id = *(int *)arg;

    while (1) {
        // Philosopher is thinking
        printf("Philosopher %d is thinking.\n", philosopher_id);
        sleep(1);

        // Pick up chopsticks
        printf("Philosopher %d is hungry and trying to pick up chopsticks.\n", philosopher_id);

        // Pick up the left chopstick
        sem_wait(&chopsticks[philosopher_id]);
        printf("Philosopher %d picked up chopstick %d (left).\n", philosopher_id, philosopher_id);

        // Pick up the right chopstick
        sem_wait(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up chopstick %d (right).\n", philosopher_id, (philosopher_id + 1) % NUM_PHILOSOPHERS);

        // Philosopher is eating
        printf("Philosopher %d is eating.\n", philosopher_id);
        sleep(1);

        // Put down the chopsticks
        sem_post(&chopsticks[philosopher_id]);  // Put down the left chopstick
        printf("Philosopher %d put down chopstick %d (left).\n", philosopher_id, philosopher_id);

        sem_post(&chopsticks[(philosopher_id + 1) % NUM_PHILOSOPHERS]);  // Put down the right chopstick
        printf("Philosopher %d put down chopstick %d (right).\n", philosopher_id, (philosopher_id + 1) % NUM_PHILOSOPHERS);

        // Philosopher goes back to thinking
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize semaphores for chopsticks (each chopstick is a semaphore initialized to 1)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philosopher_ids[i]);
    }

    // Join philosopher threads (in this case they run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores (this part won't be reached since philosophers run indefinitely)
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]);
    }

    return 0;
}
