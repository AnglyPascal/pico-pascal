%skeleton "lalr1.cc" /* -*- C++ -*- */
%language "c++" 
%require "3.8.2"
%debug 
%defines

%define api.parser.class { Parser }
%define api.namespace { Pascal }

%define api.token.constructor
%define api.value.type variant
%define parse.assert

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
        typedef vector<string> *identList;
        typedef vector<Expr *> *exprList;
        typedef vector<Stmt *> *stmtList;
        typedef vector<Proc *> *procList;
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
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%start program

%token <uint64_t> NUMBER "number"
%token <string>   IDENT "ident"

%token <op>   MONOP "monop"
%token <op>   MULOP "mulop"
%token <op>   ADDOP "addop"
%token <op>   RELOP "relop"
%token        MINUS "-"

%token  LPAR     "("
%token  RPAR     ")"
%token  COMMA    ","
%token  SEMI     ";"
%token  DOT      "."
%token  ASSIGN   ":="
%token  BADTOK   "_X_"

%token  PROC_BEGIN  "begin"
%token  PROC_END    "end"
%token  VAR         "var"
%token  PRINT       "print"
%token  IF          "if"
%token  THEN        "then"
%token  ELSE        "else"
%token  WHILE       "while"
%token  DO          "do"
%token  PROC        "proc"
%token  RETURN      "return"
%token  NEWLINE     "newline"

%token  EOF 0  "end of file"
%token  EOL    "end of line"

%type <Program *>   program
%type <Block *>     block
%type <identList>   ident_list
%type <identList>   var_decl 
%type <identList>   formals
%type <procList>    proc_decls
%type <Proc *>      proc_decl
%type <Stmt *>      stmts
%type <Stmt *>      stmt
%type <stmtList>    stmt_list
%type <Name *>      name

%type <Expr *>     expr
%type <Expr *>     simple
%type <Expr *>     term
%type <Expr *>     factor
%type <exprList>   expr_list 
%type <exprList>   actuals

%locations

%%

program :
    block DOT                           { Program *pgm = new Program($1);
                                          driver.setProgram(pgm); }
	;

block :
    var_decl proc_decls PROC_BEGIN stmts PROC_END { $$ = new Block($1, $2, $4); }
	;

var_decl :
    /* empty */                         { $$ = new vector<ident>(); }
  | VAR ident_list SEMI                 { $$ = $2; }
	;

ident_list :
    IDENT                               { vector<ident> *ids = new vector<ident>(); 
                                          ids->push_back($1); $$ = ids; }
  | ident_list COMMA IDENT              { $1->push_back($3); $$ = $1; }
	;

proc_decls :
    /* empty */                         { $$ = new vector<Proc *>(); }
  | proc_decls proc_decl                { $1->push_back($2); $$ = $1; }
	;

proc_decl :
    PROC name formals SEMI block SEMI   { new Proc($2, $3, $5); }
	;

formals :
    LPAR RPAR                           { $$ = new vector<ident>(); }
  | LPAR ident_list RPAR                { $$ = $2; }
	;

stmts :
    stmt_list                           { $$ = Pascal::sequence($1); }
	;

stmt_list :
    stmt                                { vector<Stmt *> *sts = new vector<Stmt *>(); 
                                          sts->push_back($1); $$ = sts; }
  | stmt_list SEMI stmt                 { $1->push_back($3); $$ = $1; }
	;

stmt :
    /* /1* empty *1/                         { $$ = new Skip(); } */
   name ASSIGN expr                    { $$ = new Assign($1, $3); }
  | RETURN expr                         { $$ = new Return($2); }
  | IF expr THEN stmts PROC_END              { $$ = new IfStmt($2, $4, new Skip()); }
  | IF expr THEN stmts ELSE stmts PROC_END   { $$ = new IfStmt($2, $4, $6); }
  | WHILE expr DO stmts PROC_END             { $$ = new WhileStmt($2, $4); }
  | PRINT expr                          { $$ = new Print($2); }
  | NEWLINE                             { $$ = new Newline(); }
	;

actuals :
    LPAR RPAR                           { $$ = new vector<Expr *> (); }
  | LPAR expr_list RPAR                 { $$ = $2; }
	;

expr_list :
    expr                                { vector<Expr *> *exs = new vector<Expr *>(); 
                                          exs->push_back($1); $$ = exs; }
  | expr_list COMMA expr                { $1->push_back($3); $$ = $1; }
	;

expr :
    simple                              { $$ = $1; }
  | expr RELOP simple                   { $$ = new Binop($2, $1, $3); }
	;

simple :
    term                                { $$ = $1; }
  | simple ADDOP term                   { $$ = new Binop($2, $1, $3); }
  | simple MINUS term                   { $$ = new Binop(Minus, $1, $3); }
	;

term :
    factor                              { $$ = $1; }
  | term MULOP factor                   { $$ = new Binop($2, $1, $3); }
	;

factor :
    NUMBER                              { $$ = new Constant($1); }
  | name                                { $$ = new Variable($1); }
  | name actuals                        { $$ = new Call($1, $2); }
  | MONOP factor                        { $$ = new Monop($1, $2); }
  | MINUS factor                        { $$ = new Monop(Uminus, $2); }
  | LPAR expr RPAR                      { $$ = $2; }
	;

name :
    IDENT                               { $$ = Pascal::makeName($1, 0); } 
	;

%%

// Bison expects us to provide implementation - otherwise linker complains
void Parser::error(const location &loc, const std::string &message) {

  // Location should be initialized inside scanner action, but is not in this
  // example. Let's grab location directly from driver class. 

  // cout << "Error: " << message << endl << "Location: " << loc << endl;
  cout << "Error: " << message << endl
       << "Error location: " << driver.location() << endl;
}
