%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of PascalFlexScanner */
#include "scanner.h"

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

[0-9]+                { yylval->intval = atoi(yytext); return token::NUMBER; }
[ \t]+                { yylloc->step(); }
"\r"                  { yylloc->step(); }
"\n"                  { yylloc->lines(yyleng); yylloc->step(); }
.                     { return static_cast<token_type>(*yytext); }

%%

namespace Pascal {

Scanner::Scanner(std::istream *in, std::ostream *out)
    : PascalFlexLexer(in, out) {}

Scanner::~Scanner() {}

void Scanner::set_debug(bool b) { yy_flex_debug = b; }

} // namespace Pascal

/* #ifdef yylex */
/* #undef yylex */
/* #endif */

/* int PascalFlexLexer::yylex() { */
/*   std::cerr << "in PascalFlexLexer::yylex() !" << std::endl; */
/*   return 0; */
/* } */

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int PascalFlexLexer::yywrap() { return 1; }
