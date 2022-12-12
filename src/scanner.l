%{
/* C++ string header, for string ops below */
#include "tree.h"
#include <string>
#include <stdio.h>
#include "parser.h"

/* Implementation of yyFlexScanner */
#include "scanner.h"
#undef YY_DECL
#define YY_DECL                                                                \
  int Pascal::Scanner::yylex(Pascal::Parser::semantic_type *const lval,        \
                             Pascal::Parser::location_type *location)

/* using "token" to make the returns for the tokens shorter to type */
using token = Pascal::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return (token::PROC_END)

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION                                                         \
  loc->step();                                                                 \
  loc->columns(yyleng);

%}

%option debug
%option yyclass="Pascal::Scanner"
%option noyywrap
%option c++

%%

%{          
  yylval = lval;
%}

"true"     { yylval->intval = 1; return token::NUMBER; }
"false"    { yylval->intval = 0; return token::NUMBER; }
"and"      { yylval->opval = And; return token::MULOP; }
"div"      { yylval->opval = Div; return token::MULOP; }
"mod"      { yylval->opval = Mod; return token::MULOP; }
"or"       { yylval->opval = Or;  return token::ADDOP; }
"not"      { yylval->opval = Not; return token::MONOP; }
"begin"    { return token::PROC_BEGIN; }
"end"      { return token::PROC_END; }
"var"      { return token::VAR; }
"print"    { return token::PRINT; }
"if"       { return token::IF; }
"then"     { return token::THEN; }
"else"     { return token::ELSE; }
"while"    { return token::WHILE; }
"do"       { return token::DO; }
"proc"     { return token::PROC; }
"return"   { return token::RETURN; }
"newline"  { return token::NEWLINE; }
['A'-'Z''a'-'z']['A'-'Z''a'-'z''0'-'9''_']* { 
             yylval->strval = new string(yytext); 
             return token::IDENT; 
           }
['0'-'9']+ { yylval->intval = atoi(yytext); return token::NUMBER; }
"="        { yylval->opval = Eq; return token::RELOP; }
"+"        { yylval->opval = Plus; return token::ADDOP; }
"-"        { return token::MINUS; }
"*"        { yylval->opval= Times; return token::MULOP; }
"<"        { yylval->opval= Lt; return token::RELOP; }
">"        { yylval->opval= Gt; return token::RELOP; }
"<>"       { yylval->opval= Neq; return token::RELOP; }
"<="       { yylval->opval= Leq; return token::RELOP; }
">="       { yylval->opval= Geq; return token::RELOP; }
"("        { return token::LPAR; }
")"        { return token::RPAR; }
","        { return token::COMMA; }
";"        { return token::SEMI; }
"."        { return token::DOT; }
":="       { return token::ASSIGN; }
[' ''\t']+ { }
"\r"       { }
"\n"       { }
_          { return token::BADTOK; }
eof        { return token::EOFP; }
%%

