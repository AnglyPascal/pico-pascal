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

#ifndef TREE_H
#define TREE_H

#include <stdint.h>

#include "dict.h"
#include "location.hh"
#include <iostream>
#include <map>
#include <vector>

using std::vector;

namespace Pascal {

struct Name {
  ident x_name;
  location x_loc;
  Defn *x_def = nullptr;

  Name(ident Name, location _loc);
  ~Name();
  Name *clone();

  void setDef(Defn *d);
  Defn *getDef();
  string str() const;
};

enum op {
  Plus,
  Minus,
  Times,
  Div,
  Mod,
  Eq,
  Uminus,
  Lt,
  Gt,
  Leq,
  Geq,
  Neq,
  And,
  Or,
  Not,
  Lsl,
  Lsr,
  Asr,
  BitAnd,
  BitOr,
  BitNot
};

/*****************
 *    EXPR
 *****************/

enum expr {
  constant, 
  variable, 
  monop,
  binop,
  call, 
  ifexpr,
  sub
};

struct Expr {
  Type *type = nullptr;
  location loc;
  expr exprType;

  virtual string str() const;
  virtual ~Expr() = 0;
  virtual Expr *clone() = 0;
  virtual Expr &operator=(Expr &other);

  // some methods on types
  /* virtual Type *checkType() = 0; */
};

struct Constant : public Expr {
  int n;
  Constant(int _n, location _loc);

  ~Constant();
  Expr *clone();
  string str() const;
};

struct Variable : public Expr {
  Name *x;
  Variable(Name *_x, location _loc);

  ~Variable();
  Expr *clone();
  string str() const;
};

struct Monop : public Expr {
  op o;
  Expr *e;
  Monop(op _o, Expr *_e, location _loc);

  ~Monop();
  Expr *clone();
  string str() const;
};

struct Binop : public Expr {
  op o;
  Expr *el, *er;
  Binop(op _o, Expr *_el, Expr *_er, location _loc);

  ~Binop();
  Expr *clone();
  string str() const;
};

struct Call : public Expr {
  Name *f;
  vector<Expr *> *args;

  Call(Name *_f, vector<Expr *> *_args, location _loc);
  // should it share Expressions with other nodes?
  ~Call();
  Expr *clone();
  string str() const;
};

struct IfExpr : public Expr {
  Expr *cond, *ifc, *elsec;

  IfExpr(Expr *_cond, Expr *_ifc, Expr *_elsec, location _loc);
  ~IfExpr();
  virtual Expr *clone();
  string str() const;
};

struct Sub : public Expr {
  Expr *arr, *ind;

  Sub(Expr *_arr, Expr *_ind, location _loc);
  ~Sub();
  virtual Expr *clone();
  string str() const;
};

std::ostream &operator<<(std::ostream &s, const Expr &Expr);

/******************
 **   Stmt       **
 ******************/

struct Stmt {
  location loc;
  virtual ~Stmt();
  virtual Stmt *clone() = 0;
  virtual string str(string pad) const;
};

struct Skip : public Stmt {
  Skip();
  ~Skip();
  Stmt *clone();
  string str(string pad) const;
};

struct Newline : public Stmt {
  Newline(location _loc);
  ~Newline();
  Stmt *clone();
  string str(string pad) const;
};

struct Seq : public Stmt {
  vector<Stmt *> *stmts;

  ~Seq();
  Stmt *clone();
  Seq(vector<Stmt *> *_stmts);
  string str(string pad) const;
};

struct Assign : public Stmt {
  Expr *x, *e;

  ~Assign();
  Stmt *clone();
  Assign(Expr *_x, Expr *_e, location _loc);
  string str(string pad) const;
};

struct Return : public Stmt {
  Expr *e;

  ~Return();
  Stmt *clone();
  Return(Expr *_e, location _loc);
  string str(string pad) const;
};

struct IfStmt : public Stmt {
  Expr *cond;
  Stmt *ifStmt, *elseStmt;

  virtual ~IfStmt();
  Stmt *clone();
  IfStmt(Expr *c, Stmt *i, Stmt *e, location _loc);
  string str(string pad) const;
};

struct WhileStmt : public Stmt {
  Expr *cond;
  Stmt *st;

  virtual ~WhileStmt();
  Stmt *clone();
  WhileStmt(Expr *c, Stmt *i, location _loc);
  string str(string pad) const;
};

struct Print : public Stmt {
  Expr *e;

  virtual ~Print();
  Stmt *clone();
  Print(Expr *_e, location _loc);
  string str(string pad) const;
};

struct Decl {
  Type *type;

  Decl() = default;
  virtual ~Decl() = default;

  virtual Decl *clone(){ return this; };
  virtual string str() const = 0;
  virtual int length() const { return 0; };
  virtual int size() const { return 0; };
};

struct VarDecl : public Decl {
  vector<Name *> *names;
  Type *type;
  location loc;

  VarDecl(vector<Name *> *_names, Type *_type, location _loc);
  ~VarDecl();
  Decl *clone();
  string str() const;
  int length() const;
  int size() const;
};

struct ProcDecl : public Decl {
  Name *f;
  vector<Decl *> *args;
  Func *type;
  location loc;

  ProcDecl(Name *_f, vector<Decl *> *_args, Type *_returnType, location _loc);
  ~ProcDecl();
  Decl *clone();
  string str() const;
  int length() const;
  int size() const;
};

struct Proc;

struct Block {
  vector<Decl *> *decls;
  vector<Proc *> *procs;
  Stmt *st;
  int level;

  ~Block();
  Block *clone();
  Block(vector<Decl *> *_decls, vector<Proc *> *_procs, Stmt *_st);
  string str(string pad) const;
};

struct Proc {
  ProcDecl *fun;
  Block *blk;
  location loc;
  int argSize; 
  int locSize; 

  Proc(ProcDecl *_fun, Block *_blk, location _loc);
  ~Proc();
  Proc *clone();
  string str(string pad) const;
};

struct Program {
  Block *prog;
  Program(Block *_prog);
  string str() const;
};

Stmt *sequence(vector<Stmt *> *st);
Name *makeName(ident x, location _l);

int bound(Expr *e);

} // Namespace Pascal

#endif
