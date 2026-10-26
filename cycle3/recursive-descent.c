#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char s[100];
int p = 0;

void E(void);
void Ep(void);
void T(void);
void Tp(void);
void F(void);

void error(void) {
    printf("\nString is Rejected(error at position: %d)\n", p);
    exit(1);
}

void E(void) {
    printf("E -> T E'\n");
    T();
    Ep();
}

void Ep(void) {
    if (s[p] == '+' || s[p] == '-') {
        printf("E' -> %c T E'\n", s[p]);
        p++;
        T();
        Ep();
    } else
        printf("E' -> epsilon\n");
}

void T(void) {
    printf("T -> F T'\n");
    F();
    Tp();
}
void Tp(void) {
    if (s[p] == '*' || s[p] == '/') {
        printf("T' -> %c F T'\n", s[p]);
        p++;
        F();
        Tp();
    } else
        printf("T' -> epsilon\n");
}

void F(void) {
    if (s[p] == '(') {
        printf("F  -> ( E )\n");
        p++;
        E();
        if (s[p] == ')')
            p++;
        else
            error();
    } else if (isalnum((unsigned char)s[p])) {
        printf("F  -> id\n");
        while (isalnum((unsigned char)s[p]))
            p++;
    } else
        error();
}

int main() {
    printf("Enter Expression: ");
    scanf("%99s", s);
    E();
    if (s[p] == '\0')
        printf("String is Accepted\n");
    else
        error();
    return 0;
}
