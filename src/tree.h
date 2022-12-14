#ifndef TREE_H
#define TREE_H

#include <stdint.h>

#include "dict.h"
#include <iostream>
#include <map>
#include <vector>

using std::vector;

namespace Pascal {

struct Name {
  ident x_name;
  int x_line;
  Defn *x_def = nullptr;

  Name(ident Name, int line);
  virtual ~Name();
  virtual Name *clone();

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
  Not
};

struct Expr {
  virtual string str() const;
  virtual ~Expr();
  virtual Expr *clone() { return this; };
  virtual Expr &operator=(Expr &other);
};

struct Constant : public Expr {
  int n;
  Constant(int _n);

  virtual ~Constant();
  virtual Expr *clone();
  string str() const;
};

struct Variable : public Expr {
  Name *x;
  Variable(Name *_x);

  virtual ~Variable();
  virtual Expr *clone();
  string str() const;
};

struct Monop : public Expr {
  op o;
  Expr *e;
  Monop(op _o, Expr *_e);

  virtual ~Monop();
  virtual Expr *clone();
  string str() const;
};

struct Binop : public Expr {
  op o;
  Expr *el, *er;
  Binop(op _o, Expr *_el, Expr *_er);

  virtual ~Binop();
  virtual Expr *clone();
  string str() const;
};

struct Call : public Expr {
  Name *f;
  vector<Expr *> *args;

  Call(Name *_f, vector<Expr *> *_args);
  // should it share Expressions with other nodes?
  virtual ~Call();
  virtual Expr *clone();
  string str() const;
};

std::ostream &operator<<(std::ostream &s, const Expr &Expr);

struct Stmt {
  virtual ~Stmt();
  virtual Stmt *clone() = 0;
  virtual string str() const;
};

struct Skip : public Stmt {
  virtual ~Skip();
  Stmt *clone();
  string str() const;
};

struct Newline : public Stmt {
  virtual ~Newline();
  Stmt *clone();
  virtual string str() const;
};

struct Seq : public Stmt {
  const vector<Stmt *> *stmts;

  virtual ~Seq();
  Stmt *clone();
  Seq(vector<Stmt *> *_stmts);
  virtual string str() const;
};

struct Assign : public Stmt {
  Name *x;
  Expr *e;

  virtual ~Assign();
  Stmt *clone();
  Assign(Name *_x, Expr *_e);
  virtual string str() const;
};

struct Return : public Stmt {
  Expr *e;

  virtual ~Return();
  Stmt *clone();
  Return(Expr *_e);
  virtual string str() const;
};

struct IfStmt : public Stmt {
  Expr *cond;
  Stmt *ifStmt, *elseStmt;

  virtual ~IfStmt();
  Stmt *clone();
  IfStmt(Expr *c, Stmt *i, Stmt *e);
  virtual string str() const;
};

struct WhileStmt : public Stmt {
  Expr *cond;
  Stmt *st;

  virtual ~WhileStmt();
  Stmt *clone();
  WhileStmt(Expr *c, Stmt *i);
  virtual string str() const;
};

struct Print : public Stmt {
  Expr *e;

  virtual ~Print();
  Stmt *clone();
  Print(Expr *_e);
  virtual string str() const;
};

struct Proc;

struct Block {
  vector<ident> *idents;
  vector<Proc *> *procs;
  Stmt *st;
  virtual ~Block();
  virtual Block *clone();
  Block(vector<ident> *_idents, vector<Proc *> *_procs, Stmt *_st);
  string str() const;
};

struct Proc {
  Name *f;
  vector<ident> *idents;
  Block *blk;

  virtual ~Proc();
  virtual Proc *clone();
  Proc(Name *_f, vector<ident> *_idents, Block *_blk);
  string str() const;
};

struct Program {
  const Block *prog;
  Program(Block *_prog);
  string str() const;
};

Stmt *sequence(vector<Stmt *> *st);
Name *makeName(ident x, int ln);

} // Namespace Pascal

#endif

