#ifndef SCANNER_H
#define SCANNER_H

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

/* #include "location.hh" */
#include "parser.tab.hh"

namespace Pascal {

class Scanner : public yyFlexLexer {
public:
  Scanner(std::istream *in) : yyFlexLexer(in) {
    loc = new Pascal::Parser::location_type();
  };

  // get rid of override virtual function warning
  using FlexLexer::yylex;

  virtual int yylex(Pascal::Parser::semantic_type *const lval,
                    Pascal::Parser::location_type *location);
  // YY_DECL defined in mc_lexer.l
  // Method body created by flex in mc_lexer.yy.cc

private:
  /* yylval ptr */
  Pascal::Parser::semantic_type *yylval = nullptr;
  /* location ptr */
  Pascal::Parser::location_type *loc = nullptr;
};

} // namespace Pascal

#endif

