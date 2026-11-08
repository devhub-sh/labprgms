
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char input[50];
int i = 0, error = 0;

void E();
void T();
void F();

void E() {
    T();

    while (input[i] == '+' || input[i] == '-') {
        i++;
        T();
    }
}

void T() {
    F();
    while (input[i] == '*' || input[i] == '/') {
        i++;
        F();
    }
}

void F() {
    if (isalnum((unsigned char)input[i])) {
        i++;
    } else if (input[i] == '(') {
        i++;
        E();

        if (input[i] == ')') {
            i++;
        } else {
            error = 1;
        }
    } else {
        error = 1;
    }
}

int main() {
    if (scanf("%49s", input) != 1)
        return 1;

    E();
    if (input[i] == '\0' && error == 0) {
        printf("Accepted");
    } else {
        printf("Rejected\n");
    }

    return 0;
}

