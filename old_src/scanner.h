#ifndef PASCAL_SCANNER_H
#define PASCAL_SCANNER_H

#ifndef __FLEX_LEXER_H
#define yyFlexLexer PascalFlexLexer
#include "FlexLexer.h"
#undef yyFlexLexer
#endif

#ifndef YY_DECL
#define YY_DECL                                                                \
  Pascal::Parser::token_type Scanner::yylex(                                     \
      Pascal::Parser::semantic_type *const yylval,                             \
      Pascal::Parser::location_type *yylloc)
#endif


/* #include "location.hh" */
#include "parser.h"

namespace Pascal {

typedef Parser::token_type token_type;
typedef Parser::token token;

class Scanner : public PascalFlexLexer {
public:
  Scanner(std::istream *arg_yyin = 0, std::ostream *arg_yyout = 0);

  virtual ~Scanner();

  using PascalFlexLexer::yylex;

  virtual token_type yylex(Parser::semantic_type *const yylval,
                           Parser::location_type *yylloc);

  void set_debug(bool b);
};

} // namespace Pascal

#endif
