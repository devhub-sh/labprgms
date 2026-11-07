%{
#include "y.tab.h"

struct Node* makeNode(char* token, struct Node* left, struct Node* right);
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*  { yylval.node = makeNode(yytext, NULL, NULL); return ID; }
[0-9]+                  { yylval.node = makeNode(yytext, NULL, NULL); return NUMBER; }
[ \t]                   ;
\n                      { return '\n'; }
.                       { return yytext[0]; }

%%

int yywrap()
{
    return 1;
}
