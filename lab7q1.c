#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5  // Define the size of the buffer

int buffer[BUFFER_SIZE];  // Shared buffer
int in = 0, out = 0;      // Indexes for producer and consumer

sem_t empty;  // Semaphore for empty slots
sem_t full;   // Semaphore for filled slots
pthread_mutex_t mutex;  // Mutex for critical section

// Function executed by the producer
void *producer(void *arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce an item (a random number)
        sem_wait(&empty);  // Wait if buffer is full
        pthread_mutex_lock(&mutex);  // Lock the buffer (critical section)

        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;  // Update the index for the next item

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&full);  // Signal that the buffer now has one more filled slot

        sleep(1);  // Sleep to simulate time taken to produce the item
    }
}

// Function executed by the consumer
void *consumer(void *arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait if buffer is empty
        pthread_mutex_lock(&mutex);  // Lock the buffer (critical section)

        // Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  // Update the index for the next item

        pthread_mutex_unlock(&mutex);  // Unlock the buffer
        sem_post(&empty);  // Signal that the buffer now has one more empty slot

        sleep(1);  // Sleep to simulate time taken to consume the item
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE);  // Initialize empty slots to BUFFER_SIZE
    sem_init(&full, 0, 0);  // Initialize full slots to 0
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join threads (they run indefinitely in this example)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores and mutex (this part will not be reached in this infinite loop example)
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
