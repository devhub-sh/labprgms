#include <stdio.h>
#include <string.h>

#define MAX 10

int n, m;
int trans[MAX][MAX][MAX]; // NFA transitions
int dfaStates[100][MAX];  // Stores DFA states as subsets
int dfaTrans[100][MAX];   // DFA transition table
int dfaCount = 0;

// Check if two subsets are equal
int equal(int a[], int b[]) {
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

// Find subset in DFA state list
int findState(int subset[]) {
    for (int i = 0; i < dfaCount; i++)
        if (equal(dfaStates[i], subset))
            return i;
    return -1;
}

int main() {
    int i, j, k;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    memset(trans, 0, sizeof(trans));

    // Input transition matrices
    for (k = 0; k < m; k++) {
        printf("Enter transition matrix for symbol %d:\n", k);

        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf("%d", &trans[k][i][j]);
    }

    // Initial DFA state = {q0}
    memset(dfaStates, 0, sizeof(dfaStates));
    dfaStates[0][0] = 1;
    dfaCount = 1;

    int front = 0;

    while (front < dfaCount) {
        for (k = 0; k < m; k++) {
            int newSubset[MAX] = {0};

            // For every state in current DFA state
            for (i = 0; i < n; i++) {
                if (dfaStates[front][i]) {
                    for (j = 0; j < n; j++) {
                        if (trans[k][i][j])
                            newSubset[j] = 1;
                    }
                }
            }

            int index = findState(newSubset);

            if (index == -1) {
                memcpy(dfaStates[dfaCount], newSubset, sizeof(newSubset));
                index = dfaCount;
                dfaCount++;
            }

            dfaTrans[front][k] = index;
        }

        front++;
    }

    // Display DFA states
    printf("\nDFA States:\n");

    for (i = 0; i < dfaCount; i++) {
        printf("D%d = { ", i);

        for (j = 0; j < n; j++) {
            if (dfaStates[i][j])
                printf("q%d ", j);
        }

        printf("}\n");
    }

    // Display DFA transition table
    printf("\nDFA Transition Table:\n");

    for (i = 0; i < dfaCount; i++) {
        printf("D%d : ", i);

        for (j = 0; j < m; j++) {
            printf("%d ", dfaTrans[i][j]);
        }

        printf("\n");
    }

    return 0;
}
