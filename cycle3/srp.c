#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

void display(char action[]) {
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t%s\t\t%s\n", input + ip, action);
}

int reduce(char action[]) {
    if (stack[top] == 'i') {
        stack[top] = 'E';
        strcpy(action, "Reduce i to E");
        return 1;
    } else if (top >= 2 && stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(') {
        top = top - 2;
        stack[top] = 'E';
        strcpy(action, "Reduce (E) to E");
        return 1;
    } else if (top >= 2 && stack[top - 2] == 'E' && stack[top] == 'E' && (stack[top - 1] == '+' || stack[top - 1] == '-' || stack[top - 1] == '*' || stack[top - 1] == '/')) {
        char op = stack[top - 1];
        top = top - 2;
        stack[top] = 'E';
        sprintf(action, "Reduce E %c E to E", op);
        return 1;
    }
    return 0;
}

int main(void) {
    char action[30];
    scanf("%49s", input);
    strcat(input, "$");
    while (input[ip] != '$') {
        stack[++top] = input[ip++];
        display("Shift");
        while (reduce(action)) {
            display(action);
        }
    }

    while (reduce(action))
        display(action);

    if (top == 1 && stack[top] == 'E' && input[ip] == '$') {
        printf("Accepted\n");
    } else {
        printf("Rejected\n");
    }
    return 0;
}
