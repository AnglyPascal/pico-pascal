%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.8.2"
%defines
%define api.parser.class { Parser }

%define api.token.constructor
%define api.value.type variant
%define parse.assert
%define api.namespace { Pascal }
%code requires {
    #include <iostream>
    #include <string>
    #include <vector>
    #include <stdint.h>
    #include "tree.h"

    using namespace std;

    namespace Pascal {
        class Scanner;
        class Driver;
    }
}

// Bison calls yylex() function that must be provided by us to suck tokens
// from the scanner. This block will be placed at the beginning of IMPLEMENTATION file (cpp).
// We define this function here (function! not method).
// This function is called only inside Bison, so we make it static to limit symbol visibility for the linker
// to avoid potential linking conflicts.
%code top
{
    #include <iostream>
    #include "scanner.h"
    #include "parser.h"
    #include "driver.h"
    #include "location.hh"
    
    using namespace Pascal;
    
    // yylex() arguments are defined in parser.y
    static Parser::symbol_type yylex(Scanner &scanner, Driver &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()
}

%lex-param { Pascal::Scanner &scanner }
%lex-param { Pascal::Driver &driver }
%parse-param { Pascal::Scanner &scanner }
%parse-param { Pascal::Driver &driver }

%locations
%define parse.trace
%define parse.error verbose

%define api.token.prefix {TOKEN_}


/* %union{ */
/*     int intval; */ 
/*     Pascal::Expr *exprval; */ 
/* } */

%token END 0 "end of file"
%token<uint64_t>  NUMBER "number"

%start          expr
%type <Pascal::Expr> expr

%locations

%%

expr :               { std::cout << "haha\n"; return 0; }
     |  NUMBER       { std::cout << $1; const Expr &expr = Constant($1); driver.addExpr(expr); };

%%

// Bison expects us to provide implementation - otherwise linker complains
void Pascal::Parser::error(const location &loc , const std::string &message) {
        
        // Location should be initialized inside scanner action, but is not in this example.
        // Let's grab location directly from driver class.
	// cout << "Error: " << message << endl << "Location: " << loc << endl;
	
        cout << "Error: " << message << endl << "Error location: " << driver.location() << endl;
}
