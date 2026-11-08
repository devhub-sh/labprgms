#include <stdio.h>
#include <string.h>

#define MAX 10

int n, m;                 // Number of states and input symbols
int trans[MAX][MAX][MAX]; // NFA transitions
int eps[MAX][MAX];        // Epsilon transitions
int closure[MAX][MAX];    // Epsilon

// Compute epsilon closure of a state
void epsilonClosure(int state, int visited[]) {
    visited[state] = 1;

    for (int i = 0; i < n; i++) {
        if (eps[state][i] && !visited[i]) {
            epsilonClosure(i, visited);
        }
    }
}

int main() {
    int i, j, k;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    memset(trans, 0, sizeof(trans));
    memset(eps, 0, sizeof(eps));

    // Input epsilon transitions
    printf("Enter epsilon transition matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &eps[i][j]);

    // Input transitions for each symbol
    for (k = 0; k < m; k++) {
        printf("Transition matrix for symbol %d:\n", k);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                scanf("%d", &trans[k][i][j]);
    }

    // Compute epsilon closures
    printf("\nEpsilon Closures:\n");
    for (i = 0; i < n; i++) {
        int visited[MAX] = {0};
        epsilonClosure(i, visited);

        printf("E(%d) = { ", i);
        for (j = 0; j < n; j++) {
            closure[i][j] = visited[j];
            if (visited[j])
                printf("%d ", j);
        }
        printf("}\n");
    }

    // Construct new NFA transitions
    printf("\nNFA without epsilon transitions:\n");

    for (k = 0; k < m; k++) {
        printf("\nFor input symbol %d:\n", k);

        for (i = 0; i < n; i++) {
            int result[MAX] = {0};

            for (j = 0; j < n; j++) {
                if (closure[i][j]) {
                    for (int p = 0; p < n; p++) {
                        if (trans[k][j][p]) {
                            for (int q = 0; q < n; q++) {
                                if (closure[p][q])
                                    result[q] = 1;
                            }
                        }
                    }
                }
            }

            printf("State %d -> { ", i);
            for (j = 0; j < n; j++)
                if (result[j])
                    printf("%d ", j);
            printf("}\n");
        }
    }

    return 0;
}
