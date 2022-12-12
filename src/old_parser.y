%language "c++" 
%require "3.8.2" 
%header

//http://www.jonathanbeard.io/tutorials/FlexBisonC++

%{
#include "tree.h"
#include <vector>

#include <string>
#include <stack>

using namespace std;

// stack class that takes care of all the nodes that were allocated
int lineno = 1;

%}

%union {
  ident *strval; 
  int intval;
  op opval;
  program *progval; 
  block *blockval;
  proc *procval;
  stmt *stmtptr;
  name *nameval;
  expr *exprval;
  vector<ident> *ident_list;
  vector<proc *> *proc_list;
  vector<stmt *> *stmt_list;
  vector<expr *> *expr_list;
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

%%

program :
    block DOT                           { $$ = new program($1); }
	;

block :
    var_decl proc_decls PROC_BEGIN stmts PROC_END { $$ = new block($1, $2, $4); }
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
    /* empty */                         { $$ = new vector<proc *>(); }
  | proc_decls proc_decl                { $1->push_back($2); $$ = $1; }
	;

proc_decl :
    PROC name formals SEMI block SEMI   { new proc($2, $3, $5); }
	;

formals :
    LPAR RPAR                           { $$ = new vector<ident>(); }
  | LPAR ident_list RPAR                { $$ = $2; }
	;

stmts :
    stmt_list                           { $$ = sequence($1); }
	;

stmt_list :
    stmt                                { vector<stmt *> *sts = new vector<stmt *>(); 
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
    LPAR RPAR                           { $$ = new vector<expr *> (); }
  | LPAR expr_list RPAR                 { $$ = $2; }
	;

expr_list :
    expr                                { vector<expr *> *exs = new vector<expr *>(); 
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
    IDENT                               { $$ = makeName($1, lineno); }
	;

%%

void yyerror(string s){
  fprintf(stderr, "error: %s\n", s);
}

#include "lex.yy.cc"

