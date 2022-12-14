%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of PascalFlexScanner */
#include "scanner.h"

using namespace Pascal; 

/* define yyterminate as this instead of NULL */
#define yyterminate() return token::EOFP

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

#define YY_USER_ACTION  yylloc->columns(yyleng);

%}

%option debug
%option prefix="Pascal"
%option yyclass="Scanner"
%option noyywrap
%option c++

%%

%{          
  yylloc->step();
%}

"true"                { yylval->intval = 1; return token::NUMBER; }
"false"               { yylval->intval = 0; return token::NUMBER; }
"and"                 { yylval->opval = And; return token::MULOP; }
"div"                 { yylval->opval = Div; return token::MULOP; }
"mod"                 { yylval->opval = Mod; return token::MULOP; }
"or"                  { yylval->opval = Or;  return token::ADDOP; }
"not"                 { yylval->opval = Not; return token::MONOP; }
"begin"               { return token::PROC_BEGIN; }
"end"                 { return token::PROC_END; }
"var"                 { return token::VAR; }
"print"               { return token::PRINT; }
"if"                  { return token::IF; }
"then"                { return token::THEN; }
"else"                { return token::ELSE; }
"while"               { return token::WHILE; }
"do"                  { return token::DO; }
"proc"                { return token::PROC; }
"return"              { return token::RETURN; }
"newline"             { return token::NEWLINE; }
[A-Za-z][A-Za-z0-9_]* { yylval->strval = new string(yytext, yyleng); return token::IDENT; }
[0-9]+                { yylval->intval = atoi(yytext); return token::NUMBER; }
"="                   { yylval->opval = Eq; return token::RELOP; }
"+"                   { yylval->opval = Plus; return token::ADDOP; }
"-"                   { return token::MINUS; }
"*"                   { yylval->opval= Times; return token::MULOP; }
"<"                   { yylval->opval= Lt; return token::RELOP; }
">"                   { yylval->opval= Gt; return token::RELOP; }
"<>"                  { yylval->opval= Neq; return token::RELOP; }
"<="                  { yylval->opval= Leq; return token::RELOP; }
">="                  { yylval->opval= Geq; return token::RELOP; }
\(                    { return token::LPAR; }
\)                    { return token::RPAR; }
,                     { return token::COMMA; }
;                     { return token::SEMI; }
\.                    { return token::DOT; }
:=                    { return token::ASSIGN; }
[ \t]+                { yylloc->step(); }
"\r"                  { yylloc->step(); }
"\n"                  { yylloc->lines(yyleng); yylloc->step(); }
_                     { return token::BADTOK; }
<<EOF>>               { yyterminate(); }

%%

namespace Pascal {

Scanner::Scanner(std::istream *in, std::ostream *out)
    : PascalFlexLexer(in, out) {}

Scanner::~Scanner() {}

void Scanner::set_debug(bool b) { yy_flex_debug = b; }

} // namespace Pascal

#ifdef yylex
#undef yylex
#endif

int PascalFlexLexer::yylex() {
  std::cerr << "in PascalFlexLexer::yylex() !" << std::endl;
  return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int PascalFlexLexer::yywrap() { return 1; }
