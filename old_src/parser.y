%skeleton "lalr1.cc"
%language "c++" 
%require "3.8.2" 
%debug 
%defines 
%define api.namespace    {Pascal}
%define api.parser.class {Parser}

%code requires{
#include <iostream>
#include <string>

#include "tree.h"

// The following definitions is missing when %locations isn't used
#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif
}

%parse-param { class Driver &driver }
%parse-param { class Expr *expr }

%{
/* include for all driver functions */
#include "driver.h"
#include "scanner.h"

#undef yylex
#define yylex driver.lexer->yylex
%}

%define parse.assert

%union {
  int intval;
  Expr *exprval;
}

%token<intval>  NUMBER

%start          endexpr
%type <exprval> endexpr

%locations

%%

endexpr :               { std::cout << "haha\n"; return 0; }
        |  NUMBER       { std::cout << $1; $$ = new Constant($1); expr = $$; };

%%

void Pascal::Parser::error(const Parser::location_type& l,
			    const std::string& m) {
    driver.error(l, m);
}
