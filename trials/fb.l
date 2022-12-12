/* recognize tokens for the calculator and print them out */
%{
#include "fb.tab.h"
%}

%%

"+"    { return ADD; }
"-"    { return SUB; }
"*"    { return MUL; }
"/"    { return DIV; }
"|"    { return ABS; }
[0-9]+ { yylval.intval = atoi(yytext); return NUMBER; }
\n     { return EOL; }
[ \t]  { /* ignore whitespace */ }
"("    { return OP; }
")"    { return CP; }
"//".* /* ignore comments */
.      { printf("Mystery character %c\n", *yytext); }

%%
