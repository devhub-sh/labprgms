#include <stdio.h>

#define MAX 20
#define MAX_SYMBOLS 10

int n, s;
int trans[MAX][MAX_SYMBOLS][MAX];
int visited[MAX];
int epsilon;

void eClosure(int state) {
    int i;

    if (visited[state])
        return;

    visited[state] = 1;
    printf("q%d ", state);

    // Follow epsilon transitions only
    for (i = 0; i < n; i++) {
        if (trans[state][epsilon][i] == 1)
            eClosure(i);
    }
}

int main() {
    int i, j, k;
    int from, symbol, to;
    int m;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols including epsilon: ");
    scanf("%d", &s);

    printf("\nSymbol positions:\n");

    for (i = 0; i < s; i++) {
        if (i == s - 1)
            printf("%d = epsilon\n", i);
        else
            printf("%d = input symbol\n", i);
    }

    epsilon = s - 1;

    // Initialize transition matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < s; j++)
            for (k = 0; k < n; k++)
                trans[i][j][k] = 0;

    printf("\nEnter number of transitions: ");
    scanf("%d", &m);

    printf("\nEnter transitions:\n");
    printf("Format: from symbol-position to\n");
    printf("Example: 0 0 1 means q0 --symbol0--> q1\n");
    printf("Example: 0 %d 2 means q0 --epsilon--> q2\n\n", epsilon);

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &from, &symbol, &to);
        trans[from][symbol][to] = 1;
    }

    printf("\nEpsilon Closures:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            visited[j] = 0;

        printf("e-closure(q%d) = { ", i);

        eClosure(i);

        printf("}\n");
    }

    return 0;
}
