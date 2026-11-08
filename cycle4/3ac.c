#include <stdio.h>
#include <string.h>

int main() {
    int n, i;
    char line[100];
    char result[20], arg1[20], op[5], arg2[20];

    printf("Enter number of three address statements: ");
    scanf("%d", &n);
    getchar();

    printf("\nEnter three address code:\n");
    printf("Example: t1 = a + b\n\n");

    for (i = 0; i < n; i++) {
        printf("Statement %d: ", i + 1);
        fgets(line, sizeof(line), stdin);

        sscanf(line, "%s = %s %s %s", result, arg1, op, arg2);

        printf("\n");

        if (strcmp(op, "+") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("ADD AX, %s\n", arg2);
            printf("MOV %s, AX\n", result);
        } else if (strcmp(op, "-") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("SUB AX, %s\n", arg2);
            printf("MOV %s, AX\n", result);
        } else if (strcmp(op, "*") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("MOV BX, %s\n", arg2);
            printf("MUL BX\n");
            printf("MOV %s, AX\n", result);
        } else if (strcmp(op, "/") == 0) {
            printf("MOV AX, %s\n", arg1);
            printf("MOV BX, %s\n", arg2);
            printf("DIV BX\n");
            printf("MOV %s, AX\n", result);
        } else {
            printf("Invalid operator\n");
        }

        printf("\n");
    }

    return 0;
}
