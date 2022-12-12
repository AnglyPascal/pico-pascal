%{
/* C++ string header, for string ops below */
#include "tree.h"
#include <string>
#include <stdio.h>

/* Implementation of yyFlexScanner */
#include "scanner.h"

using namespace Pascal; 

#undef YY_DECL
#define YY_DECL                                                                \
  int Scanner::yylex(Parser::semantic_type *const lval,        \
                             Parser::location_type *location)

/* define yyterminate as this instead of NULL */
#define yyterminate() {token::EOFP};

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION                                                         \
  loc->step();                                                                 \
  loc->columns(yyleng);

typedef Parser::token::token_kind_type token;
vector<token> *tokens = new vector<token>();

token yield(token t) {
  tokens->push_back(t);
  return t;
}

void printTokens() {
  for(token t: *tokens) {
    switch (t) {
      case token::NUMBER:
        std::cout << "NUMBER,";
        break;
      case token::MULOP:
        std::cout << "MULOP,";
        break;
      case token::ADDOP:
        std::cout << "ADDOP,";
        break;
      case token::MONOP:
        std::cout << "MONOP,";
        break;
      case token::MINUS:
        std::cout << "MINUS,";
        break;
      case token::RELOP:
        std::cout << "RELOP,";
        break;
      case token::PROC_BEGIN:
        std::cout << "PROC_BEGIN,";
        break;
      case token::PROC_END:
        std::cout << "PROC_END,";
        break;
      case token::VAR:
        std::cout << "VAR,";
        break;
      case token::PRINT:
        std::cout << "PRINT,";
        break;
      case token::IF:
        std::cout << "IF,";
        break;
      case token::THEN:
        std::cout << "THEN,";
        break;
      case token::ELSE:
        std::cout << "ELSE,";
        break;
      case token::WHILE:
        std::cout << "WHILE,";
        break;
      case token::DO:
        std::cout << "DO,";
        break;
      case token::LPAR:
        std::cout << "LPAR,";
        break;
      case token::RPAR:
        std::cout << "RPAR,";
        break;
      case token::PROC:
        std::cout << "PROC,";
        break;
      case token::RETURN:
        std::cout << "RETURN,";
        break;
      case token::NEWLINE:
        std::cout << "NEWLINE,";
        break;
      case token::IDENT:
        std::cout << "IDENT,";
        break;
      case token::ASSIGN:
        std::cout << "ASSIGN,";
        break;
      case token::COMMA:
        std::cout << "COMMA,";
        break;
      case token::SEMI:
        std::cout << "SEMI,";
        break;
      case token::DOT:
        std::cout << "DOT,";
        break;
      case token::BADTOK:
        std::cout << "BADTOK,";
        break;
      case token::EOFP:
        std::cout << "EOF,";
        break;
      default:
        std::cout << "_";
        break;
    }
  }
  std::cout << std::endl;
}

%}

%option debug
%option yyclass="Scanner"
%option noyywrap
%option c++

%%

%{          
  yylval = lval;
  loc->step();
%}

"true"                { yylval->intval = 1; yield(token::NUMBER); }
"false"               { yylval->intval = 0; yield(token::NUMBER); }
"and"                 { yylval->opval = And; yield(token::MULOP); }
"div"                 { yylval->opval = Div; yield(token::MULOP); }
"mod"                 { yylval->opval = Mod; yield(token::MULOP); }
"or"                  { yylval->opval = Or;  yield(token::ADDOP); }
"not"                 { yylval->opval = Not; yield(token::MONOP); }
"begin"               { yield(token::PROC_BEGIN); }
"end"                 { yield(token::PROC_END); }
"var"                 { yield(token::VAR); }
"print"               { yield(token::PRINT); }
"if"                  { yield(token::IF); }
"then"                { yield(token::THEN); }
"else"                { yield(token::ELSE); }
"while"               { yield(token::WHILE); }
"do"                  { yield(token::DO); }
"proc"                { yield(token::PROC); }
"return"              { yield(token::RETURN); }
"newline"             { yield(token::NEWLINE); }
[A-Za-z][A-Za-z0-9_]* { yylval->strval = new string(yytext, yyleng); yield(token::IDENT); }
[0-9]+                { yylval->intval = atoi(yytext); yield(token::NUMBER); }
"="                   { yylval->opval = Eq; yield(token::RELOP); }
"+"                   { yylval->opval = Plus; yield(token::ADDOP); }
"-"                   { yield(token::MINUS); }
"*"                   { yylval->opval= Times; yield(token::MULOP); }
"<"                   { yylval->opval= Lt; yield(token::RELOP); }
">"                   { yylval->opval= Gt; yield(token::RELOP); }
"<>"                  { yylval->opval= Neq; yield(token::RELOP); }
"<="                  { yylval->opval= Leq; yield(token::RELOP); }
">="                  { yylval->opval= Geq; yield(token::RELOP); }
\(                    { yield(token::LPAR); }
\)                    { yield(token::RPAR); }
,                     { yield(token::COMMA); }
;                     { yield(token::SEMI); }
\.                    { yield(token::DOT); }
:=                    { yield(token::ASSIGN); }
[ \t]+                { loc->step(); }
"\r"                  { loc->step(); }
"\n"                  { loc->lines(yyleng); loc->step(); }
_                     { yield(token::BADTOK); }
<<EOF>>               { printTokens(); return yyterminate(); }
%%


