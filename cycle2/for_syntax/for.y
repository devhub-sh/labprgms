%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(char *s);
%}

%token FOR ID NUM REL_OP INC_OP

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

stmt: FOR '(' init ';' cond ';' incr ')' body
      { printf("Valid For Loop Syntax\n"); exit(0); }
    ;

init: /* empty */
    | ID '=' expr
    ;

cond: /* empty */
    | expr
    | expr REL_OP expr
    ;

incr: /* empty */
    | ID '=' expr
    | ID INC_OP
    | INC_OP ID
    ;

expr: expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | '-' expr %prec UMINUS
    | '(' expr ')'
    | ID
    | NUM
    ;

body: ';'
    | statement
    | '{' statements '}'
    ;

statement: ID '=' expr ';'
         | ID INC_OP ';'
         ;

statements: /* empty */
          | statements statement
          ;

%%

void yyerror(char *s)
{
    printf("Invalid For Loop Syntax\n");
    exit(1);
}

int main()
{
    printf("Enter a FOR loop statement: ");
    yyparse();
    return 0;
}
