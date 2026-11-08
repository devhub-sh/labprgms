#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

char keywords[10][10] = {
    "int", "float", "char", "if", "else", "while", "for", "return", "void", "main"};

int isKeyword(char buffer[]) {
    for (int i = 0; i < 10; i++) {
        if (strcmp(keywords[i], buffer) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
            ch == '=' || ch == '<' || ch == '>' || ch == '!');
}

int isDelimiter(char ch) {
    return (ch == ';' || ch == ',' || ch == '(' || ch == ')' ||
            ch == '{' || ch == '}');
}

void analyze(char input[]) {
    int i = 0;
    char buffer[MAX];

    printf("\nTokens Found:\n");
    printf("----------------------------------\n");
    printf("Lexeme\t\tToken Type\n");
    printf("----------------------------------\n");

    while (input[i] != '\0') {
        if (input[i] == ' ' || input[i] == '\t' || input[i] == '\n') {
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_') {
            int k = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                buffer[k++] = input[i++];
            }
            buffer[k] = '\0';

            if (isKeyword(buffer))
                printf("%-15s KEYWORD\n", buffer);
            else
                printf("%-15s IDENTIFIER\n", buffer);
        } else if (isdigit(input[i])) {
            int k = 0;
            while (isdigit(input[i])) {
                buffer[k++] = input[i++];
            }
            buffer[k] = '\0';
            printf("%-15s NUMBER\n", buffer);
        } else if (isOperator(input[i])) {
            if (isOperator(input[i + 1])) {
                printf("%c%c             OPERATOR\n", input[i], input[i + 1]);
                i += 2;
            } else {
                printf("%-15c OPERATOR\n", input[i]);
                i++;
            }
        } else if (isDelimiter(input[i])) {
            printf("%-15c DELIMITER\n", input[i]);
            i++;
        } else {
            printf("%-15c UNKNOWN\n", input[i]);
            i++;
        }
    }
}

int main() {
    char input[MAX];

    printf("Enter source code line:\n");
    fgets(input, sizeof(input), stdin);

    analyze(input);

    return 0;
}
