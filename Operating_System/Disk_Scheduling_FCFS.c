#include <stdio.h>
#include <stdlib.h>

int main() {
    int numCylinders, numRequests, endRequest, i, j, k;
    int currentPos, direction;

    // Input
    printf("Enter number of cylinders on the disk: ");
    scanf("%d", &numCylinders);

    printf("Enter number of requests: ");
    scanf("%d", &numRequests);

    printf("Enter the ending request (last cylinder number): ");
    scanf("%d", &endRequest);

    printf("Enter current head position: ");
    scanf("%d", &currentPos);

    printf("Enter direction of scanning (0 for inward, 1 for outward): ");
    scanf("%d", &direction);

    // Allocate memory for requests
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

   

    // -------- Graphical representation --------
    int width = 80;  // fixed width for graph display
    double scale = (double)(numCylinders - 1) / (width - 1);

    int totalPoints = numRequests + 1;
    int *positions = (int *)malloc(totalPoints * sizeof(int));
    if (!positions) {
        printf("Memory allocation failed\n");
        free(requests);
        return 1;
    }

    positions[0] = currentPos;
    for (i = 0; i < numRequests; i++)
        positions[i + 1] = requests[i];

    char line[width + 2]; // extra space for null terminator
    line[width + 1] = '\0';

    printf("\n===== Disk Head Movement Graph =====\n");
    printf("(Scaled to %d columns)\n\n", width);

    // Print horizontal axis
    printf("Cylinder: |");
    for (i = 1; i < width - 1; i++) printf("-");
    printf("|\n");

    // Numeric labels
    int mid = width / 2;
    printf("          0%*s%d%*s%d\n\n",
           mid - 2, "", numCylinders / 2, mid - 6, "", numCylinders - 1);

    // Print each step with arrows
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

        // Mark head positions with arrows
        if (posScaled > prevScaled)
            line[posScaled] = '>';
        else if (posScaled < prevScaled)
            line[posScaled] = '<';
        else
            line[posScaled] = '*';

        line[prevScaled] = '*';

        printf("Step %2d |%s|\n", i, line);
    }
      // -------- FCFS processing --------
    int totalSeekTime = 0;
    int prevPos = currentPos;

    printf("\n===== FCFS Disk Scheduling =====\n");
    printf("Disk movement diagram (order of servicing):\n");
    printf("%d", currentPos);
    for (i = 0; i < numRequests; i++) {
        printf(" -> %d", requests[i]);
        totalSeekTime += abs(requests[i] - prevPos);
        prevPos = requests[i];
    }
    printf("\nTotal seek time: %d\n", totalSeekTime);

    free(requests);
    free(positions);

   
    return 0;
}
