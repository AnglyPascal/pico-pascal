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

/************************
 **        Expr        **
 *************************/
Expr::~Expr() {}

// ------- Constant ----------
Constant::Constant(int _n, location _loc) : n(_n) {
  loc = _loc;
  exprType = constant;
}
Constant::~Constant() {}
Expr *Constant::clone() { return new Constant(n, loc); }
Expr &Expr::operator=(Expr &other) { return other; }

// ------- Variable ----------
Variable::Variable(Name *_x, location _loc) : x(_x) {
  loc = _loc;
  exprType = variable;
}
Variable::~Variable() { delete x; }
Expr *Variable::clone() { return new Variable(x->clone(), loc); }

// ------- Monop ----------
Monop::Monop(op _o, Expr *_e, location _loc) : o(_o), e(_e) {
  loc = _loc;
  exprType = monop;
};
Monop::~Monop() { delete e; }
Expr *Monop::clone() { return new Monop(o, e->clone(), loc); }

// ------- Binop ----------
Binop::Binop(op _o, Expr *_el, Expr *_er, location _loc)
    : o(_o), el(_el), er(_er) {
  loc = _loc;
  exprType = binop;
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
  exprType = call;
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
  exprType = ifexpr;
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
  exprType = sub;
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

VarDecl::~VarDecl() {
  for (Name *n : *names)
    delete n;
  delete names;
  delete type;
}

VarDecl::VarDecl(vector<Name *> *_names, Type *_type, location _loc)
    : names(_names), type(_type), loc(_loc) {}

Decl *VarDecl::clone() {
  vector<Name *> *_names = new vector<Name *>();
  for (Name *n : *names)
    _names->push_back(n->clone());
  return new VarDecl(_names, type->clone(), loc);
}

int VarDecl::length() const { return names->size(); }
int VarDecl::size() const { return length() * type->size(); }

ProcDecl::~ProcDecl() {
  for (Decl *d : *args)
    delete d;
  delete args;
  delete f;
  delete type;
}

Decl *ProcDecl::clone() {
  vector<Decl *> *_args = new vector<Decl *>();
  for (Decl *d : *args)
    _args->push_back(d->clone());
  return new ProcDecl(f->clone(), _args, type->returnType->clone(), loc);
}

ProcDecl::ProcDecl(Name *_f, vector<Decl *> *_args, Type *_returnType,
                   location _loc)
    : f(_f), args(_args), type(nullptr), loc(_loc) {
  vector<Type *> argtypes = vector<Type *>();
  for (Decl *d : *args)
    if (typeid(*d) == typeid(VarDecl)) {
      VarDecl *v = (VarDecl *)d;
      argtypes.insert(argtypes.end(), v->names->size(), v->type);
    } else {
      ProcDecl *p = (ProcDecl *)d;
      argtypes.push_back(p->type);
    }
  type = new Func(argtypes, _returnType);
}

int ProcDecl::length() const { return 1; }

int ProcDecl::size() const { return 0; }

/************************
 **        Proc        **
 *************************/

Proc::Proc(ProcDecl *_fun, Block *_blk, location _loc)
    : fun(_fun), blk(_blk), loc(_loc), argSize(0), locSize(0) {}

Proc::~Proc() {
  delete fun;
  delete blk;
}

Proc *Proc::clone() {
  ProcDecl *f = (ProcDecl *)fun->clone();
  return new Proc(f, blk->clone(), loc);
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
