#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m; // n = number of processes, m = number of resources
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    int Allocation[n][m];
    int Max[n][m];
    int Available[m];
    int Need[n][m];

    // Input Allocation matrix
    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    // Input Max matrix
    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    // Input Available vector
    printf("Enter Available Resources: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &Available[i]);
    }

    // Calculate Need matrix = Max - Allocation
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;

    int Work[m];
    for (int i = 0; i < m; i++) Work[i] = Available[i];

    int count = 0;
    int safe_sequence[n];
    int safe_seq_index = 0;

    printf("\nStep-by-step process execution (Matrix Format):\n");

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < m; j++) {
                    if (Need[i][j] > Work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    // Print header
                    printf("\nStep %d: Process P%d executed\n", count + 1, i);
                    printf("Work vector before execution: [");
                    for (int k = 0; k < m; k++) printf("%d ", Work[k]);
                    printf("]\n");

                    printf("Allocation of process P%d: [", i);
                    for (int k = 0; k < m; k++) printf("%d ", Allocation[i][k]);
                    printf("]\n");

                    // Execute process: add Allocation to Work
                    for (int k = 0; k < m; k++)
                        Work[k] += Allocation[i][k];

                    printf("Work vector after execution:  [");
                    for (int k = 0; k < m; k++) printf("%d ", Work[k]);
                    printf("]\n");

                    safe_sequence[safe_seq_index++] = i;
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found) {
            break; // No further process can be allocated safely
        }
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\nSafe sequence is: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", safe_sequence[i]);
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state (Deadlock possible).\n");
    }

    return 0;
}
