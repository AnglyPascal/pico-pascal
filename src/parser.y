%skeleton "lalr1.cc" /* -*- C++ -*- */

/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 M Ahsan Al Mahir <ahsanalmahir@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

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
        typedef vector<Expr *> *exprList;
        typedef vector<Stmt *> *stmtList;
        typedef vector<Proc *> *procList;
        typedef vector<Decl *> *declList;
        typedef vector<Name *> *nameList;
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

%lex-param   { Pascal::Scanner &scanner }
%lex-param   { Pascal::Driver &driver }
%parse-param { Pascal::Scanner &scanner }
%parse-param { Pascal::Driver &driver }

%locations
%define parse.error verbose

%define api.token.prefix {TOKEN_}

%start program

%token <uint64_t> NUMBER BOOLCONST
%token <string>   IDENT "ident"

%token <op>   MONOP MULOP ADDOP RELOP
%token        MINUS "-"

%token  LPAR    "("
%token  RPAR    ")"
%token  SUB     "["
%token  BUS     "]"
%token  COMMA   ","
%token  COLON   ":"
%token  SEMI    ";"
%token  DOT     "."
%token  ASSIGN  ":="
%token  BADTOK  "_X_"
/* %token  IMPOSSIBLE  "_XX_" */

%token  BEGINT      "begin"
%token  END         "end"

%token  VAR ARRAY PROC INTEGER BOOLEAN
%token  IF THEN ELSE WHILE DO RETURN NEWLINE PRINT OF

/* %token  NOT         "not" */

%token  EOF 0  "end of file"
%token  EOL    "end of line"

%type <Program *>   program
%type <Decl *>      decl
%type <VarDecl *>   var_decl
%type <ProcDecl *>  proc_heading
%type <declList>    decls
%type <declList>    var_decls

%type <Block *>     block
%type <declList>    formals
%type <procList>    proc_decls
%type <Proc *>      proc_decl
%type <Stmt *>      stmts
%type <Stmt *>      stmt
%type <stmtList>    stmt_list
%type <Name *>      name
%type <nameList>    names

%type <Expr *>     expr
%type <Expr *>     simple
%type <Expr *>     ifexpr
%type <Expr *>     term
%type <Expr *>     factor
%type <Expr *>     variable
%type <Expr *>     constant

%type <exprList>   expr_list 
%type <exprList>   actuals

%type <Type *>     typexp

%locations

// TODO need to implement proc_heading to facilitate passing functions as arguments

%%

program : 
    block "."         { Program *pgm = new Program($1); driver.setProgram(pgm); } 
  ;

names :
    name                { vector<Name *> *ns = new vector<Name *>(); 
                          ns->push_back($1); $$ = ns; }
  | names COMMA name    { $1->push_back($3); $$ = $1; }
  ;

typexp :
    INTEGER                     { $$ = new Int(); }
  | BOOLEAN                     { $$ = new Bool(); }
  | ARRAY NUMBER OF typexp      { $$ = new Array($2, $4); }

var_decl: 
    VAR names COLON typexp SEMI { $$ = new VarDecl($2, $4, @1); } 
  ;

var_decls :
    /* empty */         { $$ = new vector<Decl *>(); }
  | var_decls var_decl  { $1->push_back($2); $$ = $1; }
  ;

block : 
    var_decls proc_decls "begin" stmts "end"  { $$ = new Block($1, $2, $4); } 
  ;

proc_heading : 
    PROC name formals SEMI            { $$ = new ProcDecl($2, $3, new Void(), @1); }
  | PROC name formals ":" typexp SEMI { $$ = new ProcDecl($2, $3, $5, @1); }
  ;

proc_decls :
    /* empty */                     { $$ = new vector<Proc *>(); }
  | proc_decls proc_decl            { $1->push_back($2); $$ = $1; }
	;

proc_decl :
    proc_heading block SEMI         { $$ = new Proc($1, $2, @1); }
  ;

decl :
    var_decl                    { $$ = $1; }
  | proc_heading                { $$ = $1; }
  ;

decls :
    /* empty */       { $$ = new vector<Decl *>(); }
  | decls decl        { $1->push_back($2); $$ = $1; }
  ;

formals :
    "(" decls ")"                   { $$ = $2; } 
  ;

stmts : 
    stmt_list                   { $$ = Pascal::sequence($1); } 
  ;

stmt_list :
    stmt                            { vector<Stmt *> *sts = new vector<Stmt *>(); 
                                      sts->push_back($1); $$ = sts; }
  | stmt_list SEMI stmt             { $1->push_back($3); $$ = $1; }
	;

stmt :
    /* empty */                            { $$ = new Skip(); }
  | variable ASSIGN expr                   { $$ = new Assign($1, $3, @1); }
  | RETURN expr                            { $$ = new Return($2, @1); }
  | IF expr THEN stmts END                 { $$ = new IfStmt($2, $4, new Skip(), @1); }
  | IF expr THEN stmts ELSE stmts END      { $$ = new IfStmt($2, $4, $6, @1); }
  | WHILE expr DO stmts END                { $$ = new WhileStmt($2, $4, @1); }
  | PRINT expr                             { $$ = new Print($2, @1); }
  | NEWLINE                                { $$ = new Newline(@1); }
	;

actuals :
    "(" ")"             { $$ = new vector<Expr *> (); }
  | "(" expr_list ")"   { $$ = $2; }
	;

expr_list :
    expr                { vector<Expr *> *exs = new vector<Expr *>();
                          exs->push_back($1); $$ = exs; }
  | expr_list "," expr  { $1->push_back($3); $$ = $1; }
	;

expr :
    simple              { $$ = $1; }
  | simple RELOP simple { $$ = new Binop($2, $1, $3, @1); }
  | ifexpr              { $$ = $1; }
	;

ifexpr :
    IF expr THEN expr ELSE expr     { $$ = new IfExpr($2, $4, $6, @1); };

simple :
    term              { $$ = $1; }
  | simple ADDOP term { $$ = new Binop($2, $1, $3, @1); }
  | simple MINUS term { $$ = new Binop(Minus, $1, $3, @1); }
	;

term :
    factor            { $$ = $1; }
  | term MULOP factor { $$ = new Binop($2, $1, $3, @1); }
	;

factor :
    constant          { $$ = $1; }
  | variable          { $$ = $1; }
  | name actuals      { $$ = new Call($1, $2, @1); }
  | MONOP factor      { $$ = new Monop($1, $2, @2); }
  | MINUS factor      { $$ = new Monop(Uminus, $2, @2); }
  | "(" expr ")"      { $$ = $2; }
	;

variable :
    name                    { $$ = new Variable($1, @1); }
  | variable "[" expr "]"   { $$ = new Sub($1, $3, @1); }
  ;

/* might change my decision to not have a type inside constant later */
constant :
    NUMBER            { Expr *ex = new Constant($1, @1); ex->type = new Int(); $$ = ex; }
  | BOOLCONST         { Expr *ex = new Constant($1, @1); ex->type = new Bool(); $$ = ex; }
  ;

name :
    IDENT             { $$ = Pascal::makeName($1, @1); }
	;

%%

// Bison expects us to provide implementation - otherwise linker complains
void Parser::error(const location &loc, const std::string &message) {

  // Location should be initialized inside scanner action, but is not in this
  // example. Let's grab location directly from driver class. 

  // cout << "Error: " << message << endl << "Location: " << loc << endl;
  cout << "Error: " << message << endl
       << "Error location: " << driver.yylloc() << endl;
}
