#include <stdio.h>
#include <string.h>

int main()
{
    char exp[100], tokens[100][10];
    int count = 0, temp = 1;

    printf("Enter expression: ");
    scanf("%s", exp);

    printf("\nThree Address Code:\n");

    // Store each character as a token
    for(int i = 0; exp[i] != '\0'; i++)
    {
        tokens[count][0] = exp[i];
        tokens[count][1] = '\0';
        count++;
    }

    // Process parentheses
    for(int i = 0; i < count; i++)
    {
        if(tokens[i][0] == '(')
        {
            int j = i + 1;

            // Find ')'
            while(tokens[j][0] != ')')
                j++;

            // Process inside parentheses
            while(j - i > 2)
            {
                for(int k = i + 1; k < j; k++)
                {
                    if(tokens[k][0] == '*' || tokens[k][0] == '/' ||
                       tokens[k][0] == '+' || tokens[k][0] == '-')
                    {
                        printf("t%d = %s %c %s\n",
                               temp, tokens[k-1],
                               tokens[k][0], tokens[k+1]);

                        sprintf(tokens[k-1], "t%d", temp);
                        temp++;

                        // Remove operator and operand
                        for(int x = k; x < count - 2; x++)
                            strcpy(tokens[x], tokens[x+2]);

                        count -= 2;
                        j -= 2;
                        break;
                    }
                }
            }

            // Replace (result) with result
            strcpy(tokens[i], tokens[i+1]);

            // Remove '(' and ')'
            for(int x = i + 1; x < count - 2; x++)
                strcpy(tokens[x], tokens[x+2]);

            count -= 2;

            i--;
        }
    }

    // Process * and /
    for(int pass = 0; pass < 2; pass++)
    {
        for(int i = 1; i < count - 1; i++)
        {
            if((pass == 0 && (tokens[i][0] == '*' || tokens[i][0] == '/')) ||
               (pass == 1 && (tokens[i][0] == '+' || tokens[i][0] == '-')))
            {
                printf("t%d = %s %c %s\n",
                       temp, tokens[i-1],
                       tokens[i][0], tokens[i+1]);

                sprintf(tokens[i-1], "t%d", temp);
                temp++;

                for(int j = i; j < count - 2; j++)
                    strcpy(tokens[j], tokens[j+2]);

                count -= 2;
                i--;
            }
        }
    }

    return 0;
}