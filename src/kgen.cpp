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

#include "kgen.h"
#include "consts.h"

using namespace Pascal;

int level = 0;
Label label = Label();

Inst *staticChain(int n) {
  if (n == 0)
    return new Keiko::Local(0);
  return new Keiko::Loadw(
      new Keiko::Offset(staticChain(n - 1), new Keiko::Const(stat_link)));
}

/*************
 ** GenExpr **
 *************/

Inst *KGen::genExpr(Constant *c) { return new Keiko::Const(c->n); }

Inst *KGen::genExpr(Variable *v) {
  Defn *d = v->x->getDef();
  vector<Inst *> *insts = new vector<Inst *>();
  insts->push_back(new Keiko::Line(v->x->x_loc.begin.line));

  if (typeid(d->d_kind) == typeid(VarDef)) {
    insts->push_back(new Keiko::Loadw(genAddr(v)));
    return new Keiko::Seq(insts);
  }

  int lev = d->d_level;
  int off = d->d_offset;
}

Inst *KGen::genExpr(Sub *s) {
  Inst *a = genAddr(s->arr);
  Inst *i = genExpr(s->ind);
  Inst *b = new Keiko::Bound(i, new Keiko::Const(bound(s->arr)));
  return new Keiko::Offset(
      a, new Keiko::Binop(Times, b, new Keiko::Const(s->type->size())));
}

Inst *KGen::genExpr(Monop *monop) {
  return new Keiko::Monop(monop->o, genExpr(monop->e));
}

Inst *KGen::genExpr(Binop *binop) {
  return new Keiko::Binop(binop->o, genExpr(binop->el), genExpr(binop->er));
}

Inst *KGen::genExpr(IfExpr *ie) {
  int l1 = label.incr();
  int l2 = label.incr();
  int l3 = label.incr();

  vector<Inst *> *insts = new vector<Inst *>();
  insts->push_back(genCond(ie->cond, l1, l2));
  insts->push_back(new Keiko::Label(l1));
  insts->push_back(genExpr(ie->ifc));
  insts->push_back(new Keiko::Jump(l3));
  insts->push_back(new Keiko::Label(l2));
  insts->push_back(genExpr(ie->elsec));
  insts->push_back(new Keiko::Label(l3));
  return new Keiko::Seq(insts);
}

Inst *KGen::genExpr(Call *call) { return genCall(call); }

Inst *KGen::genCall(Call *call) {
  Defn *d = call->f->getDef();
  if (typeid(d->d_type) != typeid(Func))
    throw std::domain_error("calling non function");
  Func *t = (Func *)d->d_type;

  vector<Inst *> *args = new vector<Inst *>();

  pair<Inst *, Inst *> p = genClosure(d);
  args->push_back(p.first);
  args->push_back(p.second);

  for (int i = 0, max = call->args->size(); i < max; i++) {
    genArg((*t->params)[i], (*call->args)[i], args);
  }

  int n = args->size() - 2;
  // now need to return n, addr, static_link, args
  return new Keiko::Call(n, new Keiko::Seq(args));
}

void KGen::genArg(Defn *d, Expr *e, vector<Inst *> *args) {
  if (typeid(d->d_kind) == typeid(VarDef)) {
    if (d->d_type->isScalar())
      args->push_back(genExpr(e));
    else
      // TODO might be a problem
      args->push_back(genAddr(e));
  } else {
    if (typeid(e) != typeid(Variable))
      throw std::domain_error("function must be passed as a variable");
    Variable *v = (Variable *)e;
    pair<Inst *, Inst *> p = genClosure(v->x->getDef());
    args->push_back(p.first);
    args->push_back(p.second);
  }
}

pair<Inst *, Inst *> KGen::genClosure(Defn *d) {
  Inst *st;
  if (d->d_level == 0)
    st = new Keiko::Const(0);
  else
    st = staticChain(level + 1 - d->d_level);
  return pair<Inst *, Inst *>(genAddr(d), st);
}
