#include "tree.h"

#include <iostream>
#include <vector>

namespace Pascal {

// ------- Name ----------
Name::Name(ident name, int line, int column)
    : x_name(name), x_line(line), x_column(column){};
Name::~Name() { delete x_def; }

Name *Name::clone() {
  Name *nn = new Name(x_name, x_line, x_column);
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

/************************
 **        Expr        **
 *************************/
Expr::~Expr() {}

// ------- Constant ----------
Constant::Constant(int _n) : n(_n) {}
Constant::~Constant() {}
Expr *Constant::clone() { return new Constant(n); }
Expr &Expr::operator=(Expr &other) { return other; }

// ------- Variable ----------
Variable::Variable(Name *_x) : x(_x) {}
Variable::~Variable() { delete x; }
Expr *Variable::clone() { return new Variable(x->clone()); }

// ------- Monop ----------
Monop::Monop(op _o, Expr *_e) : o(_o), e(_e){};
Monop::~Monop() { delete e; }
Expr *Monop::clone() { return new Monop(o, e->clone()); }

// ------- Binop ----------
Binop::Binop(op _o, Expr *_el, Expr *_er) : o(_o), el(_el), er(_er){};
Binop::~Binop() {
  delete el;
  delete er;
}
Expr *Binop::clone() { return new Binop(o, el->clone(), er->clone()); }

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

// ------- IfExpr ----------
IfExpr::IfExpr(Expr *_cond, Expr *_ifc, Expr *_elsec)
    : cond(_cond), ifc(_ifc), elsec(_elsec) {}
IfExpr::~IfExpr() {
  delete cond;
  delete ifc;
  delete elsec;
}
Expr *IfExpr::clone() {
  return new IfExpr(cond->clone(), ifc->clone(), elsec->clone());
}

// ------- Sub ----------
Sub::Sub(Expr *_arr, Expr *_ind) : arr(_arr), ind(_ind) {}
Sub::~Sub() {
  delete arr;
  delete ind;
}
Expr *Sub::clone() { return new Sub(arr->clone(), ind->clone()); }

// ------- << operator ----------
std::ostream &operator<<(std::ostream &s, const Expr &Expr) {
  return s << "(" << Expr.str() << ")";
}

/************************
 **        Stmt        **
 *************************/
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
Assign::Assign(Expr *_x, Expr *_e) : x(_x), e(_e) {}
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

/************************
 **        Proc        **
 *************************/

Proc::Proc(Name *_f, vector<Decl *> *_decls, Type *_returnType, Block *_blk)
    : f(_f), decls(_decls), blk(_blk), type(nullptr) {
  vector<Type *> args = vector<Type *>();
  for (Decl *d : *decls)
    args.push_back(d->type);
  type = new Func(args, _returnType);
}

Proc::~Proc() {
  for (Decl *d : *decls)
    delete d;
  delete decls;
  delete type;
  delete blk;
}

Proc *Proc::clone() {
  vector<Decl *> *_decls = new vector<Decl *>();
  for (Decl *d : *decls)
    _decls->push_back(d);
  return new Proc(f->clone(), _decls, type->returnType->clone(), blk->clone());
}

/************************
 **       Block        **
 *************************/

Block::~Block() {
  for (Proc *p : *procs)
    delete p;
  for (Decl *d : *decls)
    delete d;
  delete decls;
  delete procs;
  delete st;
}

Block *Block::clone() {
  vector<Decl *> *_decls = new vector<Decl *>();
  for (Decl *d : *decls)
    _decls->push_back(d);
  vector<Proc *> *_procs = new vector<Proc *>();
  for (Proc *p : *procs)
    _procs->push_back(p->clone());
  return new Block(_decls, _procs, st->clone());
}

Block::Block(vector<Decl *> *_decls, vector<Proc *> *_procs, Stmt *_st)
    : decls(_decls), procs(_procs), st(_st) {}

// ------- Program ---------
Program::Program(Block *_prog) : prog(_prog) {}

Name *makeName(ident x, int ln, int cm) { return new Name(x, ln, cm); };

Stmt *sequence(vector<Stmt *> *st) {
  if (!st)
    return new Skip();

  switch (st->size()) {
    case 0:
      delete st;
      return new Skip();
    case 1: {
      Stmt *s = (*st)[0];
      delete st;
      return s;
    }
    default:
      return new Seq(st);
  }
  return new Skip();
}

/************************
 **  Decl              **
 *************************/

Decl::~Decl() {
  for (Name *n : *names)
    delete n;
  delete names;
  delete type;
}

Decl::Decl(vector<Name *> *_names, Type *_type) : names(_names), type(_type) {}

/************************
 **  Printing the AST  **
 *************************/

string Expr::str() const { return "Expr"; }
string Constant::str() const { return "Constant " + std::to_string(n); }
string Variable::str() const { return "Variable " + x->x_name; }

string Monop::str() const {
  return string("Monop (") + opNames[o] + e->str() + string(")");
}

string Binop::str() const {
  return string("Binop (") + el->str() + string(" ") + opNames[o] +
         string(" ") + er->str() + string(")");
}

string Call::str() const { return string("Call ") + f->x_name; }

string IfExpr::str() const {
  return "if (" + cond->str() + ") " + ifc->str() + " else " + elsec->str();
}

string Sub::str() const { return arr->str() + "[" + ind->str() + "]"; }

string Decl::str() const {
  string s = "var ";
  for (Name *n : *names)
    s += n->str() + ", ";
  s += ": " + type->str();
  return s;
}

string Program::str() const {
  string str = "Program\nBEGIN\n" + prog->str() + "\nEOF.";
  return str;
}

string Block::str() const {
  string str = "Variables:\n";
  for (Decl *d : *decls)
    str += d->str() + "\n";
  str += "\nProcedures:\n";
  for (Proc *p : *procs)
    str += p->str();
  str += "\nStatements:\n" + st->str();
  return str;
}

string Proc::str() const {
  string str = "Name: " + f->str() + "\n";
  str += "Variables:\n";
  for (Decl *d : *decls)
    str += d->str() + "\n";
  str += "\n" + blk->str() + "\n";
  return str;
}

string Name::str() const { return x_name; }

string Stmt::str() const { return ""; }
string Skip::str() const { return "SKIP\n"; }
string Newline::str() const { return "NEWLINE\n"; }

string Seq::str() const {
  string str = "";
  for (Stmt *st : *stmts)
    str += st->str() + "\n";
  return str;
}

string Assign::str() const { return x->str() + " = " + e->str() + "\n"; }
string Return::str() const { return "return " + e->str() + "\n"; }

string IfStmt::str() const {
  string str = "if (" + cond->str() + ") {\n" + ifStmt->str() + "}";
  str += "else {\n" + elseStmt->str() + "\n}\n";
  return str;
}

string WhileStmt::str() const {
  string str = "while (" + cond->str() + ") {\n" + st->str() + "}";
  return str;
}

string Print::str() const { return "print (" + e->str() + ")\n"; }

} // namespace Pascal
