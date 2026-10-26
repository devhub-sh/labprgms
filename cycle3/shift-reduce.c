/* Shift Reduce Parser
   Grammar:  E -> E+T | T
             T -> T*F | F
             F -> (E) | id            (id = any letter/digit, shown as 'i')  */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char st[100], in[100];
int top = 0;

int endsWith(const char* pat) {
    int l = strlen(pat);
    return top >= l && strncmp(st + top - l, pat, l) == 0;
}

/* replace last len symbols by non-terminal X */
void reduce(int len, char X, const char* rule) {
    top -= len;
    st[top++] = X;
    st[top] = '\0';
    printf("Reduce %s\n", rule);
}

int main() {
    char raw[100];
    int n = 0, i = 0;
    printf("Enter expression: ");
    scanf("%99s", raw);
    for (int k = 0; raw[k]; k++)
        in[n++] = isalnum((unsigned char)raw[k]) ? 'i' : raw[k];
    in[n] = '\0';
    st[0] = '\0';

    printf("\n%-15s %-15s %s\n", "STACK", "INPUT", "ACTION");
    while (1) {
        char next = in[i];
        printf("%-15s %-15s ", st, in + i);
        if (endsWith("i"))
            reduce(1, 'F', "F -> id");
        else if (endsWith("(E)"))
            reduce(3, 'F', "F -> (E)");
        else if (endsWith("T*F"))
            reduce(3, 'T', "T -> T*F");
        else if (endsWith("E+T") && next != '*')
            reduce(3, 'E', "E -> E+T");
        else if (endsWith("F"))
            reduce(1, 'T', "T -> F");
        else if (endsWith("T") && next != '*' && !endsWith("E+T"))
            reduce(1, 'E', "E -> T");
        else if (next != '\0') {
            st[top++] = next;
            st[top] = '\0';
            i++;
            printf("Shift %c\n", next);
        } else
            break;
    }
    if (strcmp(st, "E") == 0)
        printf("Accept\n\nString is ACCEPTED\n");
    else
        printf("Error\n\nString is REJECTED\n");
    return 0;
}
