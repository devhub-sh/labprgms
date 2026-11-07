#include <stdio.h>
#include <string.h>

char stack[50], input[50];
int top = -1, ip = 0;

void display(char action[])
{
    int i;

    for(i = 0; i <= top; i++)
        printf("%c", stack[i]);

    printf("\t\t%s\t\t%s\n", input + ip, action);
}

int reduce(char action[], char lookahead)
{
    /* i -> E */
    if(stack[top] == 'i')
    {
        stack[top] = 'E';
        strcpy(action, "Reduce i to E");
        return 1;
    }

    /* (E) -> E */
    if(top >= 2 &&
       stack[top-2] == '(' &&
       stack[top-1] == 'E' &&
       stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';

        strcpy(action, "Reduce (E) to E");
        return 1;
    }

    /* E op E -> E */
    if(top >= 2 &&
       stack[top-2] == 'E' &&
       stack[top] == 'E' &&
       (stack[top-1] == '+' ||
        stack[top-1] == '-' ||
        stack[top-1] == '*' ||
        stack[top-1] == '/'))
    {
        /*
           If current operator is + or -
           and next input is * or /,
           don't reduce yet.
        */
        if((stack[top-1] == '+' || stack[top-1] == '-') &&
           (lookahead == '*' || lookahead == '/'))
        {
            return 0;
        }

        top -= 2;
        stack[top] = 'E';

        strcpy(action, "Reduce E op E to E");
        return 1;
    }

    return 0;
}

int main()
{
    char action[30];

    printf("Enter expression (use i for id): ");
    scanf("%s", input);

    strcat(input, "$");

    stack[++top] = '$';

    printf("\nSTACK\t\tINPUT\t\tACTION\n");

    /* Shift input symbols */
    while(input[ip] != '$')
    {
        stack[++top] = input[ip++];

        display("Shift");

        /* Reduce whenever possible */
        while(reduce(action, input[ip]))
        {
            display(action);
        }
    }

    /* Final reductions */
    while(reduce(action, input[ip]))
    {
        display(action);
    }

    /* Check acceptance */
    if(top == 1 &&
       stack[0] == '$' &&
       stack[1] == 'E')
    {
        display("Accepted");
    }
    else
    {
        display("Rejected");
    }

    return 0;
}