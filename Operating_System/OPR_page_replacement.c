#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAXF 20
#define WORD 20

int main() {
    int refSize, frameSize;

    char reference[MAX][WORD];
    char frame[MAXF][WORD];

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

    // Initialize frame
    for (int i = 0; i < frameSize; i++) strcpy(frame[i], "-");

    int pageFaults = 0;
    int hits = 0;

    // Print header
    printf("\nRef\tFrame Status\tRemark\n");
    printf("---------------------------------------------\n");

    // Process OPR
    for (int i = 0; i < refSize; i++) {
        int hit = 0;

        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (strcmp(frame[j], reference[i]) == 0) {
                hit = 1;
                hits++;
                break;
            }
        }

        if (!hit) {
            int replaceIndex = -1;

            // If there is empty slot, use it
            for (int j = 0; j < frameSize; j++) {
                if (strcmp(frame[j], "-") == 0) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty slot, find optimal page to replace
            if (replaceIndex == -1) {
                int farthest = -1;
                int index = -1;
                for (int j = 0; j < frameSize; j++) {
                    int k;
                    for (k = i + 1; k < refSize; k++) {
                        if (strcmp(frame[j], reference[k]) == 0) break;
                    }
                    if (k > farthest) {
                        farthest = k;
                        index = j;
                    }
                }
                replaceIndex = index;
            }

            strcpy(frame[replaceIndex], reference[i]);
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
