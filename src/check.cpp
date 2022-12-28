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
#include "exceptions.h"
#include "location.hh"

namespace Pascal {

location err_loc = location();

inline Defn *findDef(Name *x, Env *env) {
  Defn *d = env->lookup(x->x_name);
  x->x_def = d;
  return d;
}

inline void define(Defn *d, Env *env) { env->define(d); }

Type *currentReturn = new Void();

Label label = Label();

inline void sem_error(char const *const mssg) {
  throw semantic_error(mssg, err_loc);
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
        sem_error("uniary minus on non integer expression");
      monop->type = x;
      return x;
    }
    case Not: {
      Type *x = checkExpr(monop->e, env);
      if (typeid(*x) != typeid(Bool))
        sem_error("uniary not on non boolean expression");
      monop->type = x;
      return x;
    }
    default:
      sem_error("bad monop");
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
        sem_error("binary operation on non-compatibale expressions");
      if (typeid(*tl) != typeid(Int))
        sem_error("integer binary operation non integer expression");
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
        sem_error("binary operation on non-compatibale expressions");
      binop->type = new Bool();
      break;
    }
    case And:
    case Or: {
      if (typeid(*tl) != typeid(*tr))
        sem_error("binary operation on non-compatibale expressions");
      if (typeid(*tl) != typeid(Bool))
        sem_error("boolean binary operation non boolean expression");
      binop->type = tl;
      break;
    }
    default:
      sem_error("bad binop");
  }
  return binop->type;
}

Type *Check::check(Sub *sub, Env *env) {
  Type *_ta = checkExpr(sub->arr, env);
  if (!_ta->isArray())
    sem_error("substituted expression is not an array");
  Type *ti = checkExpr(sub->ind, env);
  if (typeid(*ti) != typeid(Int))
    sem_error("substituting non-integer in array");
  Array *ta = (Array *)_ta;
  sub->type = ta->elemType;
  return sub->type;
}

Type *Check::check(IfExpr *ie, Env *env) {
  Type *c = checkExpr(ie->cond, env);
  if (typeid(*c) != typeid(Bool))
    sem_error("conditional in the if expression is not a boolean");
  Type *t = checkExpr(ie->ifc, env);
  Type *e = checkExpr(ie->elsec, env);
  if (typeid(*t) != typeid(*e))
    sem_error("types of two expressions in ifexpr don't match");
  ie->type = t;
  return t;
}

Type *Check::check(Call *fe, Env *env) {
  Defn *d = findDef(fe->f, env);
  if (typeid(*d->d_kind) != typeid(ProcDef))
    sem_error("calling a non procedure");
  Func *t = (Func *)d->d_type;
  if (t->args.size() != fe->args->size())
    sem_error("calling procedure without the correct number of arguments");
  for (std::size_t i = 0, max = t->args.size(); i < max; i++) {
    Type *ta = checkExpr((*fe->args)[i], env);
    if (!equalType(t->args[i], ta))
      sem_error("argument type mismatch");
    if (typeid(*ta) == typeid(Func) &&
        typeid((*fe->args)[i]) != typeid(Variable))
      sem_error("function arguments need to passed as variables");
  }
  return t->returnType;
}

Type *Check::checkExpr(Expr *e, Env *env) {
  err_loc = e->loc;
  const std::type_info &t = typeid(*e);
  if (t == typeid(Variable)) {
    Variable *v = (Variable *)e;
    Defn *d = findDef(v->x, env);
    e->type = d->d_type;
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
      sem_error("assigning to proecedure variable");
    return;
  }
  if (typeid(*_exp) == typeid(Sub)) {
    Sub *exp = (Sub *)_exp;
    checkVar(exp->arr, env);
    return;
  }
  sem_error("assigning to non-variable or substitution expression");
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
    sem_error("assignment on non-compatibale types");
  if (typeid(*tl) != typeid(Int) && typeid(*tl) != typeid(Bool))
    sem_error("assignment only allowed on ints or bools");
}

void Check::check(Return *rt, bool inproc, Env *env) {
  if (!rt && !equalType(new Void(), currentReturn))
    sem_error("procedure with non void return type must return a value");
  if (!inproc)
    sem_error("return statement outside procedure body");
  Type *t = checkExpr(rt->e, env);
  if (!equalType(t, currentReturn))
    sem_error("returned value doesn't match expected return type");
}

void Check::check(IfStmt *ist, bool inproc, Env *env) {
  Type *t = checkExpr(ist->cond, env);
  if (typeid(*t) != typeid(Bool))
    sem_error("conditional must be a boolean value");
  checkStmt(ist->ifStmt, inproc, env);
  checkStmt(ist->elseStmt, inproc, env);
}

void Check::check(WhileStmt *wst, bool inproc, Env *env) {
  Type *t = checkExpr(wst->cond, env);
  if (typeid(*t) != typeid(Bool))
    sem_error("conditional must be a boolean value");
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

// Storage allocation needs to be done in this stage.
//
// So in the block and procs, keep a counter, for each decl, increase the
// counter gby the offset, set the address of the defnition as the offset, and
// at the end, return the total increase

void align(int alignment, int *offset) {
  int margin = *offset % alignment;
  if (margin != 0)
    *offset = *offset - margin + alignment;
}

inline void declareLocal(Decl *decl, int level, int base_offset, bool arg,
                         Env *env) {
  Type *t = decl->type;
  int *offset = &base_offset;

  for (Name *n : *decl->names) {
    Defn *d = new Defn(n->x_name, new VarDef(), level, t);

    align(d->d_type->align(), offset);
    if (arg) {
      d->d_addr = new Local(*offset);
      *offset += t->size();
    } else {
      *offset -= t->size();
      d->d_addr = new Local(*offset);
    }

    n->x_def = d;
    define(d, env);
  }
}

inline void declareGlobal(Decl *decl, Env *env) {
  Type *t = decl->type;
  for (Name *n : *decl->names) {
    Defn *d = new Defn(n->x_name, new VarDef(), 0, t);
    d->d_addr = new Global("_" + n->x_name);
    n->x_def = d;
    define(d, env);
  }
}

inline void declareProcs(vector<Proc *> *procs, int level, Env *env) {
  for (Proc *proc : *procs) {
    string lab = proc->f->x_name + "_" + std::to_string(label.incr());
    int n = proc->decls->size();

    Defn *d = new Defn(proc->f->x_name, new ProcDef(n), level, proc->type);
    d->d_addr = new Global(lab);

    proc->f->x_def = d;
    define(d, env);
  }
}

void Check::check(Proc *proc, int level, Env *_env) {
  err_loc = proc->loc;

  Env *env = new Env(_env);

  for (Decl *decl : *proc->decls)
    declareLocal(decl, level, 40, true, env);

  vector<Defn *> *pps = proc->type->params;
  for (Decl *decl : *proc->decls)
    for (Name *n : *decl->names)
      pps->push_back(n->x_def);

  for (Decl *decl : *proc->blk->decls)
    declareLocal(decl, level, 0, false, env);

  declareProcs(proc->blk->procs, level + 1, env);
  for (Proc *p : *proc->blk->procs)
    check(p, level + 1, env);

  currentReturn = proc->type->returnType;
  checkStmt(proc->blk->st, true, env);
  currentReturn = new Void();
  proc->blk->level = level;
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
  blk->level = 0;
}

} // namespace Pascal
