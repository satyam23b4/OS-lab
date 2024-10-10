#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex;  // Semaphore for resource access (write access)
sem_t mutex;     // Semaphore for reader counter update
int read_count = 0;  // Number of readers currently accessing the resource
int shared_data = 0; // Shared resource (e.g., a database or file)

// Reader function
void *reader(void *arg) {
    int reader_id = *(int *)arg;

    while (1) {
        sem_wait(&mutex);  // Lock the reader counter update
        read_count++;  // Increment the number of readers
        if (read_count == 1) {
            sem_wait(&rw_mutex);  // First reader locks the resource for reading
        }
        sem_post(&mutex);  // Unlock the reader counter update

        // Critical section for reading
        printf("Reader %d is reading the shared data: %d\n", reader_id, shared_data);
        sleep(1);  // Simulate time taken for reading

        sem_wait(&mutex);  // Lock the reader counter update
        read_count--;  // Decrement the number of readers
        if (read_count == 0) {
            sem_post(&rw_mutex);  // Last reader unlocks the resource
        }
        sem_post(&mutex);  // Unlock the reader counter update

        sleep(1);  // Simulate time between readings
    }
}

// Writer function
void *writer(void *arg) {
    int writer_id = *(int *)arg;

    while (1) {
        sem_wait(&rw_mutex);  // Lock the resource for writing

        // Critical section for writing
        shared_data++;  // Modify the shared data
        printf("Writer %d is writing new data: %d\n", writer_id, shared_data);
        sleep(1);  // Simulate time taken for writing

        sem_post(&rw_mutex);  // Unlock the resource for other readers or writers

        sleep(1);  // Simulate time between writings
    }
}

int main() {
    pthread_t readers[5], writers[2];  // Threads for readers and writers
    int reader_ids[5], writer_ids[2];

    // Initialize semaphores
    sem_init(&rw_mutex, 0, 1);  // rw_mutex starts at 1 (resource is free)
    sem_init(&mutex, 0, 1);     // mutex starts at 1 (reader count update is free)

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads (they run indefinitely in this example)
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores (this part will not be reached in this infinite loop example)
    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
