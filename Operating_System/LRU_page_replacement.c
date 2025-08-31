#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAXF 20
#define WORD 20

int main() {
    int refSize, frameSize;

    char reference[MAX][WORD];
    char frame[MAXF][WORD];
    int lastUsed[MAXF]; // Tracks last used index for each frame

    // Input
    printf("Enter number of pages in reference string: ");
    scanf("%d", &refSize);

    printf("Enter concatenated reference string: ");
    char concat[MAX * WORD];
    scanf("%s", concat);

    printf("Enter frame size: ");
    scanf("%d", &frameSize);

    // Split concatenated string into pages (1 char per page)
    for (int i = 0; i < refSize; i++) {
        reference[i][0] = concat[i];
        reference[i][1] = '\0';
    }

    // Initialize frame and lastUsed
    for (int i = 0; i < frameSize; i++) {
        strcpy(frame[i], "-");
        lastUsed[i] = -1;
    }

    int pageFaults = 0;
    int hits = 0;

    // Print header
    printf("\nRef\tFrame Status\tRemark\n");
    printf("---------------------------------------------\n");

    // Process LRU
    for (int i = 0; i < refSize; i++) {
        int hit = 0;
        int replaceIndex = -1;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (strcmp(frame[j], reference[i]) == 0) {
                hit = 1;
                hits++;
                lastUsed[j] = i; // Update last used
                break;
            }
        }

        // If page fault occurs
        if (!hit) {
            // Find empty slot first
            for (int j = 0; j < frameSize; j++) {
                if (strcmp(frame[j], "-") == 0) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty slot, find LRU page
            if (replaceIndex == -1) {
                int minLastUsed = lastUsed[0];
                replaceIndex = 0;
                for (int j = 1; j < frameSize; j++) {
                    if (lastUsed[j] < minLastUsed) {
                        minLastUsed = lastUsed[j];
                        replaceIndex = j;
                    }
                }
            }

            strcpy(frame[replaceIndex], reference[i]);
            lastUsed[replaceIndex] = i;
            pageFaults++;
        }

        // Print current reference and frame status in one line
        printf("%s\t", reference[i]);
        for (int j = 0; j < frameSize; j++) printf("%s ", frame[j]);
        printf("\t%s\n", hit ? "[HIT]" : "Page Fault");
    }

    printf("---------------------------------------------\n");

    // Print summary
    printf("TOTAL PAGE FAULTS: %d\tTOTAL HITS: %d\n", pageFaults, hits);
    printf("Page hit symbol: [HIT]\n");

    return 0;
}
