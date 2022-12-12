%skeleton "lalr1.cc"
%language "c++" 
%require "3.8.2" 
%debug 
%defines 
%define api.namespace {Pascal}
%define api.parser.class {Parser}

%code requires{
   #include "tree.h"

   namespace Pascal {
   class Driver;
   class Scanner;
   } // namespace Pascal

   // The following definitions is missing when %locations isn't used
   #ifndef YY_NULLPTR
   #if defined __cplusplus && 201103L <= __cplusplus
   #define YY_NULLPTR nullptr
   #else
   #define YY_NULLPTR 0
   #endif
   #endif
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <vector>
   #include <string>
   
   /* include for all driver functions */
   #include "driver.h"

   #undef yylex
   #define yylex scanner.yylex
}

%define parse.assert

%union {
  ident *strval; 
  int intval;
  op opval;
  Program *progval; 
  Block *blockval;
  Proc *procval;
  Stmt *stmtptr;
  Name *nameval;
  Expr *exprval;
  vector<ident> *ident_list;
  vector<Proc *> *proc_list;
  vector<Stmt *> *stmt_list;
  vector<Expr *> *expr_list;
}

%token<strval>  IDENT
%token<intval>  NUMBER
%token<opval>   MONOP MULOP ADDOP RELOP
%token          MINUS LPAR RPAR COMMA SEMI DOT ASSIGN EOFP BADTOK
%token          PROC_BEGIN PROC_END VAR PRINT IF THEN ELSE WHILE DO PROC RETURN NEWLINE

%start          program

%type <progval>     program
%type <blockval>    block
%type <ident_list>  ident_list
%type <ident_list>  var_decl 
%type <ident_list>  formals
%type <proc_list>   proc_decls
%type <procval>     proc_decl
%type <stmtptr>     stmts
%type <stmtptr>     stmt
%type <stmt_list>   stmt_list
%type <nameval>     name

%type <exprval>     expr
%type <exprval>     simple
%type <exprval>     term
%type <exprval>     factor
%type <expr_list>   expr_list 
%type <expr_list>   actuals

%locations

%%

program :
    block DOT                           { $$ = new Program($1); }
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
                                          ids->push_back(*$1); $$ = ids; }
  | ident_list COMMA IDENT              { $1->push_back(*$3); $$ = $1; }
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
    stmt_list                           { $$ = sequence($1); }
	;

stmt_list :
    stmt                                { vector<Stmt *> *sts = new vector<Stmt *>(); 
                                          sts->push_back($1); $$ = sts; }
  | stmt_list SEMI stmt                 { $1->push_back($3); $$ = $1; }
	;

stmt :
    /* empty */                         { $$ = new Skip(); }
  | name ASSIGN expr                    { $$ = new Assign($1, $3); }
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
    IDENT                               { $$ = makeName(*$1, 0); } 
	;

%%

void Pascal::Parser::error(const location_type &l,
                           const std::string &err_message) {
  std::cerr << "Error: " << err_message << " at " << l << "\n";
}
