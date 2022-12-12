#include "tree.h"

#include <iostream>
#include <vector>

using namespace Pascal;

// ------- Name ----------
Name::Name(ident name, int line) : x_name(name), x_line(line){};

Name::~Name() { delete x_def; }

Name *Name::clone() {
  Name *nn = new Name(x_name, x_line);
  nn->x_def = x_def->clone();
  return nn;
}

void Name::setDef(Defn *d) {
  delete x_def;
  x_def = d;
}

Defn *Name::getDef() {
  if (!x_def) {
    /*  throw error */
  }
  return x_def;
}

// ------- opName ----------
map<op, string> opNames = {
    {Plus, "+"}, {Minus, "-"},  {Times, "*"}, {Div, "/"}, {Mod, "%"},
    {Eq, "=="},  {Uminus, "-"}, {Lt, "<"},    {Gt, ">"},  {Leq, "<="},
    {Geq, ">="}, {Neq, "!="},   {And, "&&"},  {Or, "||"}, {Not, "!"},
};

// -----------------------
// ------- Expr ----------
// -----------------------
//
string Expr::str() const { return "Expr"; }
Expr::~Expr() {}

// ------- Constant ----------
Constant::Constant(int _n) : n(_n) {}
Constant::~Constant() {}
Expr *Constant::clone() { return new Constant(n); }
string Constant::str() const { return "Constant " + std::to_string(n); }

// ------- Variable ----------
Variable::Variable(Name *_x) : x(_x) {}
Variable::~Variable() { delete x; }
Expr *Variable::clone() { return new Variable(x->clone()); }
string Variable::str() const { return "Variable " + x->x_name; }

// ------- Monop ----------
Monop::Monop(op _o, Expr *_e) : o(_o), e(_e){};
Monop::~Monop() { delete e; }
Expr *Monop::clone() { return new Monop(o, e->clone()); }
string Monop::str() const {
  return string("Monop (") + opNames[o] + e->str() + string(")");
}

// ------- Binop ----------
Binop::Binop(op _o, Expr *_el, Expr *_er) : o(_o), el(_el), er(_er){};
Binop::~Binop() {
  delete el;
  delete er;
}
Expr *Binop::clone() { return new Binop(o, el->clone(), er->clone()); }
string Binop::str() const {
  return string("Binop (") + el->str() + string(" ") + opNames[o] +
         string(" ") + er->str() + string(")");
}

// ------- Call ----------
Call::Call(Name *_f, vector<Expr *> *_args) : f(_f), args(_args) {}
// should it share Expressions with other nodes?
Call::~Call() {
  delete f;
  for (Expr *e : *args)
    delete e;
  delete args;
}
Expr *Call::clone() { return new Call(f->clone(), args); }
string Call::str() const { return string("Call ") + f->x_name; }

// ------- << operator ----------
std::ostream &operator<<(std::ostream &s, const Expr &Expr) {
  return s << "(" << Expr.str() << ")";
}

// -----------------------
// ------- Stmt ----------
// -----------------------
//
Stmt::~Stmt() {}

// ------- Skip ----------
Skip::~Skip() {}
Stmt *Skip::clone() { return new Skip(); }

// ------- Newline ----------
Newline::~Newline() {}
Stmt *Newline::clone() { return new Newline(); }

// ------- Seq ----------
Seq::Seq(vector<Stmt *> *_stmts) : stmts(_stmts) {}
Seq::~Seq() {
  for (Stmt *s : *stmts)
    delete s;
  delete stmts;
}
Stmt *Seq::clone() {
  vector<Stmt *> *sts = new vector<Stmt *>();
  for (Stmt *s : *stmts)
    sts->push_back(s->clone());
  return new Seq(sts);
}

// ------- Assign ----------
Assign::Assign(Name *_x, Expr *_e) : x(_x), e(_e) {}
Assign::~Assign() {
  delete x;
  delete e;
}
Stmt *Assign::clone() { return new Assign(x->clone(), e->clone()); }

// ------- Return ----------
Return::Return(Expr *_e) : e(_e) {}
Return::~Return() { delete e; }
Stmt *Return::clone() { return new Return(e->clone()); }

// ------- IfStmt ----------
IfStmt::IfStmt(Expr *c, Stmt *i, Stmt *e) : cond(c), ifStmt(i), elseStmt(e) {}
IfStmt::~IfStmt() {
  delete cond;
  delete ifStmt;
  delete elseStmt;
}
Stmt *IfStmt::clone() {
  return new IfStmt(cond->clone(), ifStmt->clone(), elseStmt->clone());
}

// ------- WhileStmt ----------
WhileStmt::WhileStmt(Expr *c, Stmt *i) : cond(c), st(i) {}
WhileStmt::~WhileStmt() {
  delete cond;
  delete st;
}
Stmt *WhileStmt::clone() { return new WhileStmt(cond->clone(), st->clone()); }

// ------- Print ----------
Print::Print(Expr *_e) : e(_e){};
Print::~Print() { delete e; }
Stmt *Print::clone() { return new Print(e->clone()); }

// -----------------------
// ------- Proc ----------
// -----------------------
//
Proc::Proc(Name *_f, vector<ident> *_idents, Block *_blk)
    : f(_f), idents(_idents), blk(_blk) {}
Proc::~Proc() {
  delete idents;
  delete blk;
}
Proc *Proc::clone() {
  vector<ident> *ids = new vector<ident>();
  for (ident i : *idents)
    ids->push_back(i);
  return new Proc(f->clone(), ids, blk->clone());
}

// -----------------------
// ------- Block ---------
// -----------------------
//
Block::~Block() {
  for (Proc *p : *procs)
    delete p;
  delete idents;
  delete procs;
  delete st;
}

Block *Block::clone() {
  vector<ident> *ids = new vector<ident>();
  for (ident i : *idents)
    ids->push_back(i);
  vector<Proc *> *prs = new vector<Proc *>();
  for (Proc *p : *procs)
    prs->push_back(p->clone());
  return new Block(ids, prs, st->clone());
}

Block::Block(vector<ident> *_idents, vector<Proc *> *_procs, Stmt *_st)
    : idents(_idents), procs(_procs), st(_st) {}

// ------- Program ---------
Program::Program(Block *_prog) : prog(_prog) {}
