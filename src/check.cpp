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

using namespace Pascal;

inline Type *findDef(Name *x, Env *env) {
  Defn *d = env->lookup(x->x_name);
  x->x_def = d;
  return d->d_type;
}

inline void define(Defn *d, Env *env) { env->define(d); }

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

semantic_error::semantic_error(char const *const message) throw()
    : domain_error(message) {}

// TODO might not work
char const *semantic_error::what() const throw() {
  return domain_error::what();
}

Check::Check(Program *_pgm) : pgm(_pgm) {}
Check::~Check(){};

/*********************
 *  Expression
 *********************/

Type *Check::check(Monop *monop, Env *env) {
  switch (monop->o) {
    case Uminus: {
      Type *x = check(monop->e, env);
      if (typeid(*x) != typeid(Int))
        throw semantic_error("uniary minus on non integer expression");
      monop->type = x;
      return x;
    }
    case Not: {
      Type *x = check(monop->e, env);
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
  Type *tl = check(binop->el, env);
  Type *tr = check(binop->er, env);

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
      break;
    }
    case And:
    case Or: {
      if (typeid(*tl) != typeid(*tr))
        throw semantic_error("binary operation on non-compatibale expressions");
      if (typeid(*tl) != typeid(Bool))
        throw semantic_error("boolean binary operation non boolean expression");
      break;
    }
    default:
      throw semantic_error("bad binop");
  }
  binop->type = tl;
  return tl;
}

Type *Check::check(Sub *sub, Env *env) {
  Type *_ta = check(sub->arr, env);
  if (!_ta->isArray())
    throw semantic_error("substituted expression is not an array");
  Type *ti = check(sub->ind, env);
  if (typeid(*ti) != typeid(Int))
    throw semantic_error("substituting non-integer in array");
  Array *ta = (Array *)_ta;
  sub->type = ta->elemType;
  return sub->type;
}

Type *Check::check(IfExpr *ie, Env *env) {
  Type *c = check(ie->cond, env);
  if (typeid(*c) != typeid(Bool))
    throw semantic_error("conditional in the if expression is not a boolean");
  Type *t = check(ie->ifc, env);
  Type *e = check(ie->elsec, env);
  if (typeid(*t) != typeid(*e))
    throw semantic_error("types of two expressions in ifexpr don't match");
  ie->type = t;
  return t;
}

Type *Check::check(Expr *e, Env *env) {
  const std::type_info &t = typeid(*e);
  if (t == typeid(Variable)) {
    Variable *v = (Variable *)e;
    return findDef(v->x, env);
  }
  if (t == typeid(Monop)) {
    Monop *monop = (Monop *)e;
    return check(monop, env);
  }
  if (t == typeid(Binop)) {
    Binop *binop = (Binop *)e;
    return check(binop, env);
  }
  /* if (t == typeid(Call)) */
  // Proc type is different, we need to add it separate as a type def
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
 *  Procedures
 ******************/

void Check::check(Proc *proc, int level, Env *_env) {
  Env *env = new Env(_env);
  for (Decl *decl : *proc->decls)
    declareLocal(decl, level, 16, true, env);
  for (Decl *decl : *proc->blk->decls)
    declareLocal(decl, level, 0, false, env);
  declareProcs(proc->blk->procs, level + 1, env);
  for (Proc *p : *proc->blk->procs)
    check(p, level + 1, env);
  check(proc->blk->st, true, env);
}


