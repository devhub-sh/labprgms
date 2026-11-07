%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char token[20];
    struct Node* left;
    struct Node* right;
};

struct Node* makeNode(char* token, struct Node* left, struct Node* right) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    strcpy(node->token, token);
    node->left = left;
    node->right = right;
    return node;
}

void printTree(struct Node* root, int space) {
    if (root == NULL) return;

    space += 5;
    printTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");
    printf("%s\n", root->token);

    printTree(root->left, space);
}

int yylex();
void yyerror(char *s);
%}

%union {
    struct Node* node;
}

%token <node> ID NUMBER
%type <node> expr

%left '+' '-'
%left '*' '/'

%%

input: expr '\n'
      {
          printf("\nGenerated Abstract Syntax Tree (Horizontal View):\n");
          printf("---------------------------------------------------\n");
          printTree($1, 0);
          printf("---------------------------------------------------\n");
          exit(0);
      }
      ;

expr: expr '+' expr { $$ = makeNode("+", $1, $3); }
      | expr '-' expr { $$ = makeNode("-", $1, $3); }
      | expr '*' expr { $$ = makeNode("*", $1, $3); }
      | expr '/' expr { $$ = makeNode("/", $1, $3); }
      | '(' expr ')'  { $$ = $2; }
      | NUMBER        { $$ = $1; }
      | ID            { $$ = $1; }
      ;

%%

void yyerror(char *s) {
    printf("Syntax Error\n");
    exit(1);
}

int main() {
    printf("Enter expression: ");
    yyparse();
    return 0;
}
