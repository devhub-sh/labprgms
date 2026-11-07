%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%union {
    double dval;
}

%token <dval> NUMBER
%type <dval> EXPR

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input: expr '\n' { printf("Result = %g\n", $1); exit(0); }
    ;

expr: expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr
      {
          if ($3 == 0) {
              printf("Error: Division by zero\n");
              exit(1);
          }
          $$ = $1 / $3;
      }
    | '(' expr ')' { $$ = $2; }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | NUMBER { $$ = $1; }
    ;

%%

void yyerror(char *s)
{
    printf("Invalid Expression\n");
    exit(1);
}

int main()
{
    printf("Enter an arithmetic expression: ");
    yyparse();
    return 0;
}
