#include <stdio.h>
#include <stdlib.h>

int cmpfunc(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int numCylinders, numRequests, i, j, k;
    int currentPos, direction;

    // Input
    printf("Enter number of cylinders on the disk: ");
    scanf("%d", &numCylinders);

    printf("Enter number of requests: ");
    scanf("%d", &numRequests);

    printf("Enter current head position: ");
    scanf("%d", &currentPos);

    printf("Enter direction of scanning (0 for inward, 1 for outward): ");
    scanf("%d", &direction);

    int *requests = (int *)malloc(numRequests * sizeof(int));
    if (!requests) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter the requests (space separated):\n");
    for (i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
        if (requests[i] < 0 || requests[i] >= numCylinders) {
            printf("Request %d is out of range. It should be between 0 and %d\n",
                   requests[i], numCylinders - 1);
            free(requests);
            return 1;
        }
    }

    // -------- LOOK Algorithm --------
    qsort(requests, numRequests, sizeof(int), cmpfunc);

    int *positions = (int *)malloc((numRequests + 1) * sizeof(int)); // store movement
    if (!positions) {
        printf("Memory allocation failed\n");
        free(requests);
        return 1;
    }

    int totalSeekTime = 0;
    int totalPoints = 0;

    // Split requests into left (<current) and right (>=current)
    int *left = (int *)malloc(numRequests * sizeof(int));
    int *right = (int *)malloc(numRequests * sizeof(int));
    int leftCount = 0, rightCount = 0;

    for (i = 0; i < numRequests; i++) {
        if (requests[i] < currentPos) left[leftCount++] = requests[i];
        else right[rightCount++] = requests[i];
    }

    int prevPos = currentPos;
    positions[totalPoints++] = currentPos;

    if (direction == 1) { // outward (toward higher cylinders)
        // Service right side in ascending order
        for (i = 0; i < rightCount; i++) {
            positions[totalPoints++] = right[i];
            totalSeekTime += abs(right[i] - prevPos);
            prevPos = right[i];
        }
        // Then service left side in descending order
        for (i = leftCount - 1; i >= 0; i--) {
            positions[totalPoints++] = left[i];
            totalSeekTime += abs(left[i] - prevPos);
            prevPos = left[i];
        }
    } else { // inward (toward lower cylinders)
        // Service left side in descending order
        for (i = leftCount - 1; i >= 0; i--) {
            positions[totalPoints++] = left[i];
            totalSeekTime += abs(left[i] - prevPos);
            prevPos = left[i];
        }
        // Then service right side in ascending order
        for (i = 0; i < rightCount; i++) {
            positions[totalPoints++] = right[i];
            totalSeekTime += abs(right[i] - prevPos);
            prevPos = right[i];
        }
    }


    // -------- Graphical representation --------
    int width = 80;
    double scale = (double)(numCylinders - 1) / (width - 1);
    char line[width + 2];
    line[width + 1] = '\0';

    printf("\nDisk Head Movement Graph (scaled to %d columns):\n\n", width);

    // Horizontal axis
    printf("Cylinder: |");
    for (i = 1; i < width - 1; i++) printf("-");
    printf("|\n");
    int mid = width / 2;
    printf("          0%*s%d%*s%d\n\n",
           mid - 2, "", numCylinders / 2, mid - 6, "", numCylinders - 1);

    for (i = 0; i < totalPoints; i++) {
        for (j = 0; j < width; j++) line[j] = ' ';
        line[width] = ' ';

        int posScaled = (int)(positions[i] / scale + 0.5);

        if (i == 0) {
            line[posScaled] = '*';
            printf("Step %2d |%s|\n", i, line);
            continue;
        }

        int prevScaled = (int)(positions[i - 1] / scale + 0.5);
        int start = prevScaled < posScaled ? prevScaled : posScaled;
        int end = prevScaled > posScaled ? prevScaled : posScaled;

        for (k = start; k <= end; k++) line[k] = '-';

        if (posScaled > prevScaled)
            line[posScaled] = '>';
        else if (posScaled < prevScaled)
            line[posScaled] = '<';
        else
            line[posScaled] = '*';

        line[prevScaled] = '*';

        printf("Step %2d |%s|\n", i, line);
    }
    
    
    printf("\nDisk movement diagram (order of servicing):\n");
    for (i = 0; i < totalPoints; i++) {
        if (i == 0) printf("%d", positions[i]);
        else printf(" -> %d", positions[i]);
    }
    printf("\nTotal seek time: %d\n", totalSeekTime);
    free(requests);
    free(positions);
    free(left);
    free(right);


    return 0;
}
