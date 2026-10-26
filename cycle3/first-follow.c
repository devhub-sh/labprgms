/* FIRST and FOLLOW of a grammar.
   Upper-case letter = non-terminal, '#' = epsilon, first production's LHS = start symbol.
   Enter one production per line, e.g.  E=TR   R=+TR   R=#   (write alternatives as separate lines) */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int n;
char lhs[30], rhs[30][30];
int first[128][128], follow[128][128], nullable[128];

int main() {
    char t[60];
    printf("Number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (A=alpha, # for epsilon):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", t);
        lhs[i] = t[0];
        strcpy(rhs[i], t + 2);
    }

    int ch = 1;
    /* nullable */
    while (ch) {
        ch = 0;
        for (int i = 0; i < n; i++) {
            if (nullable[(int)lhs[i]])
                continue;
            int all = 1;
            for (int j = 0; rhs[i][j]; j++) {
                char c = rhs[i][j];
                if (c == '#')
                    continue;
                if (!nullable[(int)c]) {
                    all = 0;
                    break;
                }
            }
            if (all) {
                nullable[(int)lhs[i]] = 1;
                ch = 1;
            }
        }
    }

    /* FIRST */
    ch = 1;
    while (ch) {
        ch = 0;
        for (int i = 0; i < n; i++) {
            int A = lhs[i];
            for (int j = 0; rhs[i][j]; j++) {
                int c = rhs[i][j];
                if (c == '#')
                    continue;
                if (!isupper(c)) {
                    if (!first[A][c]) {
                        first[A][c] = 1;
                        ch = 1;
                    }
                    break;
                }
                for (int x = 0; x < 128; x++)
                    if (first[c][x] && !first[A][x]) {
                        first[A][x] = 1;
                        ch = 1;
                    }
                if (!nullable[c])
                    break;
            }
        }
    }

    /* FOLLOW */
    follow[(int)lhs[0]]['$'] = 1;
    ch = 1;
    while (ch) {
        ch = 0;
        for (int i = 0; i < n; i++) {
            int A = lhs[i];
            for (int k = 0; rhs[i][k]; k++) {
                int B = rhs[i][k];
                if (!isupper(B))
                    continue;
                int allnull = 1;
                for (int j = k + 1; rhs[i][j]; j++) {
                    int c = rhs[i][j];
                    if (!isupper(c)) {
                        if (!follow[B][c]) {
                            follow[B][c] = 1;
                            ch = 1;
                        }
                        allnull = 0;
                        break;
                    }
                    for (int x = 0; x < 128; x++)
                        if (first[c][x] && !follow[B][x]) {
                            follow[B][x] = 1;
                            ch = 1;
                        }
                    if (!nullable[c]) {
                        allnull = 0;
                        break;
                    }
                }
                if (allnull)
                    for (int x = 0; x < 128; x++)
                        if (follow[A][x] && !follow[B][x]) {
                            follow[B][x] = 1;
                            ch = 1;
                        }
            }
        }
    }

    int done[128] = {0};
    printf("\n%-6s %-20s %s\n", "NT", "FIRST", "FOLLOW");
    for (int i = 0; i < n; i++) {
        int A = lhs[i];
        if (done[A])
            continue;
        done[A] = 1;
        char f[200] = "{ ", g[200] = "{ ";
        for (int x = 0; x < 128; x++) {
            if (first[A][x]) {
                char s[4] = {(char)x, ' ', 0};
                strcat(f, s);
            }
            if (follow[A][x]) {
                char s[4] = {(char)x, ' ', 0};
                strcat(g, s);
            }
        }
        if (nullable[A])
            strcat(f, "# ");
        strcat(f, "}");
        strcat(g, "}");
        printf("%-6c %-20s %s\n", A, f, g);
    }
    return 0;
}
