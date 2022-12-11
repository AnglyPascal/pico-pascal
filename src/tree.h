#ifndef tree
#define tree

#include "./dict.h"
#include <iostream>
#include <vector>

using namespace std;

class name {
  const ident _name;
  const int x_line;
  def *x_def = nullptr;

public:
  name(ident name, int line) : _name(name), x_line(line){};

  void setDef(def *d) {
    delete x_def;
    x_def = d;
  }

  def *getDef() {
    if (!x_def) {
      /*  throw error */
    }
    return x_def;
  }

  int line() { return x_line; }
  string x_name() { return _name; }
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

map<op, string> opNames = {
    {Plus, "+"}, {Minus, "-"},  {Times, "*"}, {Div, "/"}, {Mod, "%"},
    {Eq, "=="},  {Uminus, "-"}, {Lt, "<"},    {Gt, ">"},  {Leq, "<="},
    {Geq, ">="}, {Neq, "!="},   {And, "&&"},  {Or, "||"}, {Not, "!"},
};

struct expr {
  virtual string str() const { return "expr"; }
};

struct Constant : public expr {
  const int n;
  Constant(int _n) : n(_n){};

  string str() const { return "Constant " + to_string(n); }
};

struct Variable : public expr {
private:
  name *x;

public:
  Variable(name *_x) : x(_x){};
  string str() const { return "Variable " + x->x_name(); }
};

struct Monop : public expr {
  const op o;
  const expr *e;
  Monop(op _o, expr *_e) : o(_o), e(_e){};
  string str() const {
    return string("Monop (") + opNames[o] + e->str() + string(")");
  }
};

struct Binop : public expr {
  const op o;
  const expr *el, *er;
  Binop(op _o, expr *_el, expr *_er) : o(_o), el(_el), er(_er){};
  string str() const {
    return string("Binop (") + el->str() + string(" ") + opNames[o] +
           string(" ") + er->str() + string(")");
  }
};

struct Call : public expr {
private:
  name *f;

public:
  const vector<expr> args;
  Call(name *_f, vector<expr> _args) : f(_f), args(_args){};

  string str() const { return string("Call ") + f->x_name(); }
};

ostream &operator<<(ostream &s, const expr &expr) {
  return s << "(" << expr.str() << ")";
}

struct stmt {};

struct Skip : public stmt {};

struct Newline : public stmt {};

struct Seq : public stmt {
  const vector<stmt *> stmts;
  Seq(vector<stmt *> *_stmts) : stmts(*_stmts) { delete _stmts; };
};

struct Assign : public stmt {
  const name x;
  const expr *e;
  Assign(name _x, expr *_e) : x(_x), e(_e){};
};

struct Return : public stmt {
  const expr *e;
  Return(expr *_e) : e(_e){};
};

struct IfStmt : public stmt {
  const expr *cond;
  const stmt *ifstmt, *elsestmt;
  IfStmt(expr *c, stmt *i, stmt *e) : cond(c), ifstmt(i), elsestmt(e){};
};

struct WhileStmt : public stmt {
  const expr *cond;
  const stmt *st;
  WhileStmt(expr *c, stmt *i) : cond(c), st(i){};
};

struct Print : public stmt {
  const expr *e;
  Print(expr *_e) : e(_e){};
};

struct block;

struct proc {
  const block *blk;
};

struct block {
  const vector<ident> idents;
  const vector<proc *> procs;
  const stmt *st;
};

struct program {
  const block *prog;
};

stmt *sequence(vector<stmt *> *st) {
  if (!st)
    return new Skip();

  switch (st->size()) {
  case 0:
    delete st;
    return new Skip();
  case 1: {
    stmt *s = (*st)[0];
    delete st;
    return s;
  }
  default:
    return new Seq(st);
  }
  return new Skip();
}

name *makeName(ident x, int ln) { return new name(x, ln); };

#endif
