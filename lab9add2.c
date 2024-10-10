#include <stdio.h>

void fifo(int pages[], int n, int frames) {
    int frame[frames], count = 0, pageFaults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initially, all frames are empty
    }

    printf("\nFIFO Page Replacement\n");
    printf("Page\tFrames\n");
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;  // Page is already in a frame (hit)
                break;
            }
        }
        
        if (!found) {
            frame[count] = pages[i];  // Replace the oldest page
            count = (count + 1) % frames;  // FIFO rotation
            pageFaults++;
        }
        
        // Display current frame content
        printf("%d\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", pageFaults);
}

void lru(int pages[], int n, int frames) {
    int frame[frames], time[frames], pageFaults = 0, count = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initially, all frames are empty
        time[i] = 0;
    }

    printf("\nLRU Page Replacement\n");
    printf("Page\tFrames\n");

    for (int i = 0; i < n; i++) {
        int found = 0, leastUsed = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;  // Page is already in a frame (hit)
                time[j] = ++count;
                break;
            }
        }

        if (!found) {
            for (int j = 0; j < frames; j++) {
                if (time[j] < time[leastUsed])
                    leastUsed = j;  // Find least recently used page
            }
            frame[leastUsed] = pages[i];  // Replace the least recently used page
            time[leastUsed] = ++count;
            pageFaults++;
        }

        // Display current frame content
        printf("%d\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", pageFaults);
}

void optimal(int pages[], int n, int frames) {
    int frame[frames], pageFaults = 0;
    for (int i = 0; i < frames; i++) {
        frame[i] = -1;  // Initially, all frames are empty
    }

    printf("\nOptimal Page Replacement\n");
    printf("Page\tFrames\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        
        // Check if the page is already in memory (hit)
        for (int j = 0; j < frames; j++) {
            if (frame[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        // If not found, we need to replace a page (miss)
        if (!found) {
            int j, replaceIdx = -1, farthest = i;

            for (j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    replaceIdx = j;  // Empty frame available
                    break;
                }

                int k;
                for (k = i + 1; k < n; k++) {
                    if (frame[j] == pages[k]) {
                        if (k > farthest) {
                            farthest = k;
                            replaceIdx = j;
                        }
                        break;
                    }
                }

                // If a page is never used again, replace it
                if (k == n) {
                    replaceIdx = j;
                    break;
                }
            }

            if (replaceIdx == -1)
                replaceIdx = 0;

            frame[replaceIdx] = pages[i];  // Replace the selected page
            pageFaults++;
        }

        // Display current frame content
        printf("%d\t", pages[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1)
                printf("%d ", frame[j]);
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (Optimal): %d\n", pageFaults);
}

int main() {
    int n, frames;

    // Input the number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page reference string:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input the number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Call FIFO page replacement algorithm
    fifo(pages, n, frames);

    // Call LRU page replacement algorithm
    lru(pages, n, frames);

    // Call Optimal page replacement algorithm
    optimal(pages, n, frames);

    return 0;
}
