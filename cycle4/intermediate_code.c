/* Simple Three Address Code generator (parser emits code directly)
   Input e.g.  x=a+b*c-d   or   x=(a+b)*(c-d)/2
   Also writes tac.txt (op arg1 arg2 result) for the 8086 back end (program 6). */
#include <ctype.h>
#include <stdio.h>
#include <string.h>

char s[100];
int p = 0, tc = 0, pc = 0;
char pool[100][12]; /* storage for operand / temp names */
FILE* f;

char* E(void);

char* newtemp(void) {
    char* t = pool[pc++];
    snprintf(t, 12, "t%d", ++tc);
    return t;
}

void emit(char op, char* a, char* b, char* r) {
    printf("%s = %s %c %s\n", r, a, op, b);
    fprintf(f, "%c %s %s %s\n", op, a, b, r);
}

char* F(void) { /* F -> (E) | id */
    if (s[p] == '(') {
        p++;
        char* x = E();
        p++;
        return x;
    }
    char* r = pool[pc++];
    int k = 0;
    while (isalnum((unsigned char)s[p]) && k < 11)
        r[k++] = s[p++];
    r[k] = '\0';
    return r;
}

char* T(void) { /* T -> F { (*|/) F } */
    char* l = F();
    while (s[p] == '*' || s[p] == '/') {
        char op = s[p++];
        char* r = F();
        char* t = newtemp();
        emit(op, l, r, t);
        l = t;
    }
    return l;
}

char* E(void) { /* E -> T { (+|-) T } */
    char* l = T();
    while (s[p] == '+' || s[p] == '-') {
        char op = s[p++];
        char* r = T();
        char* t = newtemp();
        emit(op, l, r, t);
        l = t;
    }
    return l;
}

int main() {
    char lhs[12] = "";
    f = fopen("tac.txt", "w");
    printf("Enter assignment (e.g. x=a+b*c-d): ");
    scanf("%99s", s);
    char* eq = strchr(s, '=');
    if (eq) {
        *eq = '\0';
        strcpy(lhs, s);
        p = (int)(eq - s) + 1;
    }

    printf("\nThree Address Code:\n");
    char* res = E();
    if (lhs[0]) {
        printf("%s = %s\n", lhs, res);
        fprintf(f, "= %s - %s\n", res, lhs);
    }
    fclose(f);
    return 0;
}
