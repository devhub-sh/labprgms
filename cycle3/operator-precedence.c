/* Simple Operator Precedence Parser
   Grammar: E -> E+E | E*E | (E) | id        (type any letter/digit as id) */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char terms[] = "+*()i$";
/* rows = stack-top terminal, cols = input.  < shift, > reduce, = shift, x error, A accept */
char table[6][6] = {
    /*        +    *    (    )    i    $  */
    /* + */ {'>', '<', '<', '>', '<', '>'},
    /* * */ {'>', '>', '<', '>', '<', '>'},
    /* ( */ {'<', '<', '<', '=', '<', 'x'},
    /* ) */ {'>', '>', 'x', '>', 'x', '>'},
    /* i */ {'>', '>', 'x', '>', 'x', '>'},
    /* $ */ {'<', '<', '<', 'x', '<', 'A'}};

int idx(char c) {
    char* p = strchr(terms, c);
    return p ? (int)(p - terms) : -1;
}

int main() {
    char raw[100], in[100], st[100] = "$";
    int n = 0, i = 0, top = 0;

    printf("Enter expression: ");
    scanf("%99s", raw);
    for (int k = 0; raw[k]; k++)
        in[n++] = isalnum((unsigned char)raw[k]) ? 'i' : raw[k];
    in[n++] = '$';
    in[n] = '\0';

    printf("\n%-12s %-12s %s\n", "STACK", "INPUT", "ACTION");
    while (1) {
        int t = top;
        if (st[t] == 'E')
            t--; /* top terminal is at most one below */
        char a = st[t], b = in[i];
        if (idx(a) < 0 || idx(b) < 0) {
            printf("Invalid symbol\nREJECTED\n");
            return 1;
        }
        char r = table[idx(a)][idx(b)];
        printf("%-12s %-12s ", st, in + i);

        if (r == 'A') {
            printf("Accept\n%s\n", strcmp(st, "$E") == 0 ? "ACCEPTED" : "REJECTED");
            break;
        } else if (r == '<' || r == '=') {
            st[++top] = b;
            st[top + 1] = '\0';
            i++;
            printf("Shift %c\n", b);
        } else if (r == '>') {
            if (st[top] == 'i') {
                st[top] = 'E';
                printf("Reduce E -> id\n");
            } else if (top >= 3 && st[top] == 'E' && (st[top - 1] == '+' || st[top - 1] == '*') && st[top - 2] == 'E') {
                top -= 2;
                st[top] = 'E';
                st[top + 1] = '\0';
                printf("Reduce E -> E op E\n");
            } else if (top >= 3 && st[top] == ')' && st[top - 1] == 'E' && st[top - 2] == '(') {
                top -= 2;
                st[top] = 'E';
                st[top + 1] = '\0';
                printf("Reduce E -> (E)\n");
            } else {
                printf("Error\nREJECTED\n");
                break;
            }
        } else {
            printf("Error\nREJECTED\n");
            break;
        }
    }
    return 0;
}
