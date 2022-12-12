%{/* -*- C++ -*- */
#include "tree.h"
#include <string>
#include <stdio.h>
#include "parser.tab.hh"

typedef yy::parser::token::token_kind_type token;

map<string, token> tokens = {
    {"begin", token::PROC_BEGIN},   {"end", token::PROC_END},
    {"var", token::VAR},       {"print", token::PRINT},
    {"if", token::IF},         {"then", token::THEN},
    {"else", token::ELSE},     {"while", token::WHILE},
    {"do", token::DO},         {"proc", token::PROC},
    {"return", token::RETURN}, {"newline", token::NEWLINE}};
};

token lookup(string s) {
  if (tokens.count(s)) 
      return tokens[s];
  yylval->strval = s; 
  return token::IDENT;
}


%}

%% 

"true"            { yylval->intval = 1; return token::NUMBER; }
"false"           { yylval->intval = 0; return token::NUMBER; }
"and"             { yylval->opval = And; return token::MULOP; }
"div"             { yylval->opval = Div; return token::MULOP; }
"mod"             { yylval->opval = Mod; return token::MULOP; }
"or"              { yylval->opval = Or;  return token::ADDOP; }
"not"             { yylval->opval = Not; return token::MONOP; }
['A'-'Z''a'-'z']['A'-'Z''a'-'z''0'-'9''_']*  { return lookup(yytext); }
['0'-'9']+ { yylval->intval = atoi(yytext); return token::NUMBER; }
"="               { yylval->opval = Eq; return token::RELOP; }
"+"               { yylval->opval = Plus; return token::ADDOP; }
"-"               { return token::MINUS; }
"*"               { yylval->opval= Times; return token::MULOP; }
"<"               { yylval->opval= Lt; return token::RELOP; }
">"               { yylval->opval= Gt; return token::RELOP; }
"<>"              { yylval->opval= Neq; return token::RELOP; }
"<="              { yylval->opval= Leq; return token::RELOP; }
">="              { yylval->opval= Geq; return token::RELOP; }
"("               { return token::LPAR; }
")"               { return token::RPAR; }
","               { return token::COMMA; }
";"               { return token::SEMI; }
"."               { return token::DOT; }
":="              { return token::ASSIGN; }
[' ''\t']+        
"\r"              
_                 { return token::BADTOK; }
eof               { return token::EOFP; }

%%
/* "(*"              { comment lexbuf; token lexbuf; } */
/* "\n"              { lineno ++; Source.note_line !lineno lexbuf; } */

