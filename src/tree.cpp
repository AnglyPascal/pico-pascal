#include "tree.h"

#include <iostream>
#include <vector>

string pad_const = "  ";

namespace Pascal {

// ------- Name ----------
Name::Name(ident name, location _loc) : x_name(name), x_loc(_loc) {}
Name::~Name() { delete x_def; }

Name *Name::clone() {
  Name *nn = new Name(x_name, x_loc);
  nn->x_def = x_def->clone();
  return nn;
}

void Name::setDef(Defn *d) {
  delete x_def;
  x_def = d;
}

Defn *Name::getDef() {
  if (!x_def) {
    throw std::domain_error("definition not found: " + x_name);
  }
  return x_def;
}

// ------- opName ----------
map<op, string> opNames = {
    {Plus, "+"},  {Minus, "-"},  {Times, "*"}, {Div, "/"},    {Mod, "%"},
    {Eq, "=="},   {Uminus, "-"}, {Lt, "<"},    {Gt, ">"},     {Leq, "<="},
    {Geq, ">="},  {Neq, "!="},   {And, "&&"},  {Or, "||"},    {Not, "!"},
    {Lsl, "<<"},  {Lsr, ">>"},   {Asr, "asr"}, {BitAnd, "&"}, {BitOr, "|"},
    {BitNot, "~"}};

/************************
 **        Expr        **
 *************************/
Expr::~Expr() {}

// ------- Constant ----------
Constant::Constant(int _n, location _loc) : n(_n) { loc = _loc; }
Constant::~Constant() {}
Expr *Constant::clone() { return new Constant(n, loc); }
Expr &Expr::operator=(Expr &other) { return other; }

// ------- Variable ----------
Variable::Variable(Name *_x, location _loc) : x(_x) { loc = _loc; }
Variable::~Variable() { delete x; }
Expr *Variable::clone() { return new Variable(x->clone(), loc); }

// ------- Monop ----------
Monop::Monop(op _o, Expr *_e, location _loc) : o(_o), e(_e) { loc = _loc; };
Monop::~Monop() { delete e; }
Expr *Monop::clone() { return new Monop(o, e->clone(), loc); }

// ------- Binop ----------
Binop::Binop(op _o, Expr *_el, Expr *_er, location _loc)
    : o(_o), el(_el), er(_er) {
  loc = _loc;
};
Binop::~Binop() {
  delete el;
  delete er;
}
Expr *Binop::clone() { return new Binop(o, el->clone(), er->clone(), loc); }

// ------- Call ----------
Call::Call(Name *_f, vector<Expr *> *_args, location _loc)
    : f(_f), args(_args) {
  loc = _loc;
}
// should it share Expressions with other nodes?
Call::~Call() {
  delete f;
  for (Expr *e : *args)
    delete e;
  delete args;
}
Expr *Call::clone() { return new Call(f->clone(), args, loc); }

// ------- IfExpr ----------
IfExpr::IfExpr(Expr *_cond, Expr *_ifc, Expr *_elsec, location _loc)
    : cond(_cond), ifc(_ifc), elsec(_elsec) {
  loc = _loc;
}
IfExpr::~IfExpr() {
  delete cond;
  delete ifc;
  delete elsec;
}
Expr *IfExpr::clone() {
  return new IfExpr(cond->clone(), ifc->clone(), elsec->clone(), loc);
}

// ------- Sub ----------
Sub::Sub(Expr *_arr, Expr *_ind, location _loc) : arr(_arr), ind(_ind) {
  loc = _loc;
}
Sub::~Sub() {
  delete arr;
  delete ind;
}
Expr *Sub::clone() { return new Sub(arr->clone(), ind->clone(), loc); }

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
Skip::Skip() { loc = location(); }
Skip::~Skip() {}
Stmt *Skip::clone() { return new Skip(); }

// ------- Newline ----------
Newline::Newline(location _loc) { loc = _loc; }
Newline::~Newline() {}
Stmt *Newline::clone() { return new Newline(loc); }

// ------- Seq ----------
Seq::Seq(vector<Stmt *> *_stmts) : stmts(_stmts) { loc = location(); }
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
Assign::Assign(Expr *_x, Expr *_e, location _loc) : x(_x), e(_e) { loc = _loc; }
Assign::~Assign() {
  delete x;
  delete e;
}
Stmt *Assign::clone() { return new Assign(x->clone(), e->clone(), loc); }

// ------- Return ----------
Return::Return(Expr *_e, location _loc) : e(_e) { loc = _loc; }
Return::~Return() { delete e; }
Stmt *Return::clone() { return new Return(e->clone(), loc); }

// ------- IfStmt ----------
IfStmt::IfStmt(Expr *c, Stmt *i, Stmt *e, location _loc)
    : cond(c), ifStmt(i), elseStmt(e) {
  loc = _loc;
}
IfStmt::~IfStmt() {
  delete cond;
  delete ifStmt;
  delete elseStmt;
}
Stmt *IfStmt::clone() {
  return new IfStmt(cond->clone(), ifStmt->clone(), elseStmt->clone(), loc);
}

// ------- WhileStmt ----------
WhileStmt::WhileStmt(Expr *c, Stmt *i, location _loc) : cond(c), st(i) {
  loc = _loc;
}
WhileStmt::~WhileStmt() {
  delete cond;
  delete st;
}
Stmt *WhileStmt::clone() {
  return new WhileStmt(cond->clone(), st->clone(), loc);
}

// ------- Print ----------
Print::Print(Expr *_e, location _loc) : e(_e) { loc = _loc; };
Print::~Print() { delete e; }
Stmt *Print::clone() { return new Print(e->clone(), loc); }

/************************
 **  Decl              **
 *************************/

Decl::~Decl() {
  for (Name *n : *names)
    delete n;
  delete names;
  delete type;
}

Decl::Decl(vector<Name *> *_names, Type *_type, location _loc)
    : names(_names), type(_type), loc(_loc) {}

/************************
 **        Proc        **
 *************************/

Proc::Proc(Name *_f, vector<Decl *> *_decls, Type *_returnType, Block *_blk,
           location _loc)
    : f(_f), decls(_decls), blk(_blk), type(nullptr), loc(_loc) {
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
  return new Proc(f->clone(), _decls, type->returnType->clone(), blk->clone(),
                  loc);
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
    : decls(_decls), procs(_procs), st(_st), level(0) {}

// ------- Program ---------
Program::Program(Block *_prog) : prog(_prog) {}

Name *makeName(ident x, location _l) { return new Name(x, _l); };

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
 **  Printing the AST  **
 *************************/

string Expr::str() const { return "Expr"; }
string Constant::str() const { return std::to_string(n); }
string Variable::str() const { return x->x_name; }

string Monop::str() const { return "(" + opNames[o] + e->str() + ")"; }

string Binop::str() const {
  return "(" + el->str() + " " + opNames[o] + " " + er->str() + ")";
}

string Call::str() const {
  string a = "";
  for (Expr *e : *args)
    a += e->str() + ", ";
  return f->x_name + "(" + a + ")";
}

string IfExpr::str() const {
  return "if (" + cond->str() + ") " + ifc->str() + " else " + elsec->str();
}

string Sub::str() const { return arr->str() + "[" + ind->str() + "]"; }

string Decl::str() const {
  string s = "var ";
  int n = names->size();
  for (int i = 0; i < n - 1; i++)
    s += (*names)[i]->str() + ", ";
  s += (*names)[n - 1]->str();
  s += ": " + type->str();
  return s;
}

string Program::str() const {
  string str = "**Program**\n\n" + prog->str() + "\n**eof**";
  return str;
}

string Block::str() const {
  string pad = "";
  for (int i = 0; i < level; i++)
    pad += pad_const;

  string str = "";
  for (Decl *d : *decls)
    str += pad + d->str() + "\n";

  for (Proc *p : *procs)
    str += p->str();

  str += pad + "begin\n";
  str += st->str(pad + pad_const);
  str += pad + "end\n";
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

string Stmt::str(string pad) const { return pad; }
string Skip::str(string pad) const { return ""; }
string Newline::str(string pad) const { return pad + "newline\n"; }

string Seq::str(string pad) const {
  string str = "";
  for (Stmt *st : *stmts)
    str += st->str(pad);
  return str;
}

string Assign::str(string pad) const {
  return pad + x->str() + " = " + e->str() + "\n";
}
string Return::str(string pad) const {
  return pad + "return " + e->str() + "\n";
}

string IfStmt::str(string pad) const {
  string str =
      pad + "if (" + cond->str() + ") {\n" + ifStmt->str(pad + pad_const) + "}";
  str += " else {\n" + elseStmt->str(pad + pad_const) + "\n}\n";
  return str;
}

string WhileStmt::str(string pad) const {
  string str = pad + "while (" + cond->str() + ") {\n" +
               st->str(pad + pad_const) + pad + "}\n";
  return str;
}

string Print::str(string pad) const {
  return pad + "print (" + e->str() + ")\n";
}

/*************
 * Functions *
 *************/

int bound(Expr *e) {
  Type *t = e->type;
  if (typeid(t) == typeid(Array)) {
    Array *a = (Array *)t;
    return a->length;
  }
  // change the error type
  throw std::domain_error("bound on non-array type");
}

} // namespace Pascal
