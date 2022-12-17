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

#include "check.h"
#include "location.hh"

using namespace Pascal;

location err_loc = location();

inline Defn *findDef(Name *x, Env *env) {
  Defn *d = env->lookup(x->x_name);
  x->x_def = d;
  return d;
}

inline void define(Defn *d, Env *env) { env->define(d); }

Type *currentReturn = new Void();

/*********************
 *  semantic_error
 *********************/

semantic_error::semantic_error(char const *const message) throw()
    : domain_error("(" + std::to_string(err_loc.begin.line) + "." +
                   std::to_string(err_loc.begin.column) + "): " + message) {}

// TODO might not work
char const *semantic_error::what() const throw() {
  return domain_error::what();
}

/*********************
 *  Check Constructor
 *********************/

Check::Check(Program *_pgm) : pgm(_pgm) {}
Check::~Check(){};

/*********************
 *  Expression
 *********************/

Type *Check::check(Monop *monop, Env *env) {
  switch (monop->o) {
    case Uminus: {
      Type *x = checkExpr(monop->e, env);
      if (typeid(*x) != typeid(Int))
        throw semantic_error("uniary minus on non integer expression");
      monop->type = x;
      return x;
    }
    case Not: {
      Type *x = checkExpr(monop->e, env);
      if (typeid(*x) != typeid(Bool))
        throw semantic_error("uniary not on non boolean expression");
      monop->type = x;
      return x;
    }
    default:
      throw semantic_error("bad monop");
  }
}

Type *Check::check(Binop *binop, Env *env) {
  Type *tl = checkExpr(binop->el, env);
  Type *tr = checkExpr(binop->er, env);

  switch (binop->o) {
    case Plus:
    case Minus:
    case Times:
    case Div:
    case Mod: {
      if (typeid(*tl) != typeid(*tr))
        throw semantic_error("binary operation on non-compatibale expressions");
      if (typeid(*tl) != typeid(Int))
        throw semantic_error("integer binary operation non integer expression");
      binop->type = tl;
      break;
    }
    case Eq:
    case Lt:
    case Gt:
    case Leq:
    case Geq:
    case Neq: {
      if (typeid(*tl) != typeid(*tr))
        throw semantic_error("binary operation on non-compatibale expressions");
      binop->type = new Bool();
      break;
    }
    case And:
    case Or: {
      if (typeid(*tl) != typeid(*tr))
        throw semantic_error("binary operation on non-compatibale expressions");
      if (typeid(*tl) != typeid(Bool))
        throw semantic_error("boolean binary operation non boolean expression");
      binop->type = tl;
      break;
    }
    default:
      throw semantic_error("bad binop");
  }
  return binop->type;
}

Type *Check::check(Sub *sub, Env *env) {
  Type *_ta = checkExpr(sub->arr, env);
  if (!_ta->isArray())
    throw semantic_error("substituted expression is not an array");
  Type *ti = checkExpr(sub->ind, env);
  if (typeid(*ti) != typeid(Int))
    throw semantic_error("substituting non-integer in array");
  Array *ta = (Array *)_ta;
  sub->type = ta->elemType;
  return sub->type;
}

Type *Check::check(IfExpr *ie, Env *env) {
  Type *c = checkExpr(ie->cond, env);
  if (typeid(*c) != typeid(Bool))
    throw semantic_error("conditional in the if expression is not a boolean");
  Type *t = checkExpr(ie->ifc, env);
  Type *e = checkExpr(ie->elsec, env);
  if (typeid(*t) != typeid(*e))
    throw semantic_error("types of two expressions in ifexpr don't match");
  ie->type = t;
  return t;
}

Type *Check::check(Call *fe, Env *env) {
  Defn *d = findDef(fe->f, env);
  if (typeid(*d->d_kind) != typeid(ProcDef))
    throw semantic_error("calling a non procedure");
  Func *t = (Func *)d->d_type;
  if (t->args.size() != fe->args->size())
    throw semantic_error(
        "calling procedure without the correct number of arguments");
  for (std::size_t i = 0, max = t->args.size(); i < max; i++) {
    Type *ta = checkExpr((*fe->args)[i], env);
    if (!equalType(t->args[i], ta))
      throw semantic_error("argument type mismatch");
  }
  return t->returnType;
}

Type *Check::checkExpr(Expr *e, Env *env) {
  err_loc = e->loc;
  const std::type_info &t = typeid(*e);
  if (t == typeid(Variable)) {
    Variable *v = (Variable *)e;
    Defn *d = findDef(v->x, env);
    return d->d_type;
  }
  if (t == typeid(Monop)) {
    Monop *monop = (Monop *)e;
    return check(monop, env);
  }
  if (t == typeid(Binop)) {
    Binop *binop = (Binop *)e;
    return check(binop, env);
  }
  if (t == typeid(Call)) {
    Call *call = (Call *)e;
    return check(call, env);
  }
  if (t == typeid(IfExpr)) {
    IfExpr *ie = (IfExpr *)e;
    return check(ie, env);
  }
  if (t == typeid(Sub)) {
    Sub *sub = (Sub *)e;
    return check(sub, env);
  }
  return e->type;
}

/******************
 *  Var
 ******************/

void Check::checkVar(Expr *_exp, Env *env) {
  if (typeid(*_exp) == typeid(Variable)) {
    Variable *exp = (Variable *)_exp;
    Defn *d = findDef(exp->x, env);
    if (typeid(*d->d_kind) == typeid(ProcDef))
      throw semantic_error("assigning to proecedure variable");
    return;
  }
  if (typeid(*_exp) == typeid(Sub)) {
    Sub *exp = (Sub *)_exp;
    checkVar(exp->arr, env);
    return;
  }
  throw semantic_error("assigning to non-variable or substitution expression");
}

/******************
 *  Stmt
 ******************/

void Check::check(Seq *sts, bool inproc, Env *env) {
  for (Stmt *s : *sts->stmts)
    checkStmt(s, inproc, env);
}

void Check::check(Assign *ae, bool inproc, Env *env) {
  Type *tl = checkExpr(ae->x, env);
  Type *tr = checkExpr(ae->e, env);
  checkVar(ae->x, env);
  if (!equalType(tl, tr))
    throw semantic_error("assignment on non-compatibale types");
  if (typeid(*tl) != typeid(Int) && typeid(*tl) != typeid(Bool))
    throw semantic_error("assignment only allowed on ints or bools");
}

void Check::check(Return *rt, bool inproc, Env *env) {
  if (!rt && !equalType(new Void(), currentReturn))
    throw semantic_error(
        "procedure with non void return type must return a value");
  if (!inproc)
    throw semantic_error("return statement outside procedure body");
  Type *t = checkExpr(rt->e, env);
  if (!equalType(t, currentReturn))
    throw semantic_error("returned value doesn't match expected return type");
}

void Check::check(IfStmt *ist, bool inproc, Env *env) {
  Type *t = checkExpr(ist->cond, env);
  if (typeid(*t) != typeid(Bool))
    throw semantic_error("conditional must be a boolean value");
  checkStmt(ist->ifStmt, inproc, env);
  checkStmt(ist->elseStmt, inproc, env);
}

void Check::check(WhileStmt *wst, bool inproc, Env *env) {
  Type *t = checkExpr(wst->cond, env);
  if (typeid(*t) != typeid(Bool))
    throw semantic_error("conditional must be a boolean value");
  checkStmt(wst->st, inproc, env);
}

void Check::check(Print *p, bool inproc, Env *env) { checkExpr(p->e, env); }

void Check::checkStmt(Stmt *_stmt, bool inproc, Env *env) {
  err_loc = _stmt->loc;

  const std::type_info &t = typeid(*_stmt);
  if (t == typeid(Seq)) {
    Seq *s = (Seq *)_stmt;
    check(s, inproc, env);
  }
  if (t == typeid(Assign)) {
    Assign *s = (Assign *)_stmt;
    check(s, inproc, env);
  }
  if (t == typeid(Return)) {
    Return *s = (Return *)_stmt;
    check(s, inproc, env);
  }
  if (t == typeid(IfStmt)) {
    IfStmt *s = (IfStmt *)_stmt;
    check(s, inproc, env);
  }
  if (t == typeid(WhileStmt)) {
    WhileStmt *s = (WhileStmt *)_stmt;
    check(s, inproc, env);
  }
  if (t == typeid(Print)) {
    Print *s = (Print *)_stmt;
    check(s, inproc, env);
  }
}

/******************
 *  Procedures
 ******************/

inline void declareLocal(Decl *decl, int level, int base_offset, bool arg,
                         Env *env) {
  Type *t = decl->type;
  int i;
  if (arg)
    i = 1;
  else
    i = -1;

  int offset = base_offset;

  for (Name *n : *decl->names) {
    offset += i * t->size();
    Defn *d = new Defn(n->x_name, new VarDef(), level, "", offset, t);
    define(d, env);
  }
}

inline void declareGlobal(Decl *decl, Env *env) {
  Type *t = decl->type;
  for (Name *n : *decl->names) {
    Defn *d = new Defn(n->x_name, new VarDef(), 0, "_" + n->x_name, 0, t);
    define(d, env);
  }
}

inline void declareProcs(vector<Proc *> *procs, int level, Env *env) {
  for (Proc *proc : *procs) {
    string label = proc->f->x_name + "_" + std::to_string(Label.incr());
    int n = proc->decls->size();
    Defn *d =
        new Defn(proc->f->x_name, new ProcDef(n), level, label, 0, proc->type);
    define(d, env);
  }
}

void Check::check(Proc *proc, int level, Env *_env) {
  err_loc = proc->loc;

  Env *env = new Env(_env);

  for (Decl *decl : *proc->decls)
    declareLocal(decl, level, 16, true, env);
  for (Decl *decl : *proc->blk->decls)
    declareLocal(decl, level, 0, false, env);

  declareProcs(proc->blk->procs, level + 1, env);
  for (Proc *p : *proc->blk->procs)
    check(p, level + 1, env);

  currentReturn = proc->type->returnType;
  checkStmt(proc->blk->st, true, env);
  currentReturn = new Void();
}

/******************
 *  GLOBAL
 ******************/

void Check::check(Env *env) {
  Block *blk = pgm->prog;
  for (Decl *decl : *blk->decls)
    declareGlobal(decl, env);
  declareProcs(blk->procs, 1, env);
  for (Proc *p : *blk->procs)
    check(p, 1, env);
  checkStmt(blk->st, false, env);
}
