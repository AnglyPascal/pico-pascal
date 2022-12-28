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
int retlab = 0;
Label label1 = Label();

Inst *staticChain(int n) {
  if (n == 0)
    return new Keiko::Local(0);
  return new Keiko::Loadw(
      new Keiko::Offset(staticChain(n - 1), new Keiko::Const(stat_link)));
}

/*************
 ** GenExpr **
 *************/

Inst *KGen::genExpr(Expr *e) {
  const std::type_info &t = typeid(*e);
  if (t == typeid(Constant)) {
    Constant *v = (Constant *)e;
    return genExpr(v);
  }
  if (t == typeid(Variable)) {
    Variable *v = (Variable *)e;
    return genExpr(v);
  }
  if (t == typeid(Monop)) {
    Monop *monop = (Monop *)e;
    return genExpr(monop);
  }
  if (t == typeid(Binop)) {
    Binop *binop = (Binop *)e;
    return genExpr(binop);
  }
  if (t == typeid(Call)) {
    Call *call = (Call *)e;
    return genExpr(call);
  }
  if (t == typeid(IfExpr)) {
    IfExpr *ie = (IfExpr *)e;
    return genExpr(ie);
  }
  if (t == typeid(Sub)) {
    Sub *sub = (Sub *)e;
    return genExpr(sub);
  }
  throw std::domain_error("failed to match any expression type");
}

Inst *KGen::genExpr(Constant *c) { return new Keiko::Const(c->n); }

Inst *KGen::genExpr(Variable *v) {
  Defn *d = v->x->getDef();
  vector<Inst *> *insts = new vector<Inst *>();
  insts->push_back(new Keiko::Line(v->x->x_loc.begin.line));

  if (typeid(d->d_kind) == typeid(VarDef)) {
    if (v->type->size() == 1)
      insts->push_back(new Keiko::Loadc(genAddr(v)));
    else
      insts->push_back(new Keiko::Loadw(genAddr(v)));
    return new Keiko::Seq(insts);
  }

  throw std::domain_error("generating expression for ProcDef");
  /* int lev = d->d_level; */
  /* Inst *sl; */
  /* if (lev == 0) */
  /*   sl = new Keiko::Const(0); */
  /* else if (level + 1 < lev) */
  /*   throw std::domain_error("accessing out of scope procedure"); */
  /* else */
  /*   sl = staticChain(level + 1 - lev); */

  /* int off = d->d_offset; */
}

Inst *KGen::genExpr(Sub *s) {
  if (s->type->size() == 1)
    return new Keiko::Loadc(genAddr(s));
  return new Keiko::Loadw(genAddr(s));
}

Inst *KGen::genExpr(Monop *monop) {
  return new Keiko::Monop(monop->o, genExpr(monop->e));
}

Inst *KGen::genExpr(Binop *binop) {
  return new Keiko::Binop(binop->o, genExpr(binop->el), genExpr(binop->er));
}

Inst *KGen::genExpr(IfExpr *ie) {
  int l1 = label1.incr();
  int l2 = label1.incr();
  int l3 = label1.incr();

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
  int *index = 0;
  for (int i = 0, max = call->args->size(); i < max; i++)
    genArg(index, (*t->params)[i], (*call->args)[i], args);
  int n = args->size();
  delete index;

  // get the closure of the function definition
  pair<Inst *, Inst *> p = genClosure(d);
  return new Keiko::Call(n, p.first, new Keiko::Static(p.second),
                         new Keiko::Seq(args));
}

void KGen::genArg(int *index, Defn *d, Expr *e, vector<Inst *> *args) {
  if (typeid(d->d_kind) == typeid(VarDef)) {
    if (d->d_type->isScalar())
      args->push_back(new Keiko::Arg(*index, genExpr(e)));
    else
      // TODO might be a problem
      args->push_back(genAddr(e));
  } else {
    if (typeid(e) != typeid(Variable))
      throw std::domain_error("function must be passed as a variable");
    Variable *v = (Variable *)e;
    pair<Inst *, Inst *> p = genClosure(v->x->getDef());
    args->push_back(new Keiko::Arg(*index, p.first));
    (*index)++;
    args->push_back(new Keiko::Arg(*index, p.second));
  }
  (*index)++;
}

pair<Inst *, Inst *> KGen::genClosure(Defn *d) {
  Inst *st;
  if (d->d_level == 0)
    st = new Keiko::Const(0);
  else
    st = staticChain(level + 1 - d->d_level);
  return pair<Inst *, Inst *>(address(d), st);
}

/***************
 *  GenAddr
 **************/

Inst *KGen::address(Defn *d) {
  int lev = d->d_level;
  // global variable or procedure definition
  if (lev == 0 || typeid(d->d_kind) == typeid(ProcDef))
    return new Keiko::Global(d->d_label);
  if (level < lev)
    throw std::domain_error("trying to access variable defined out of scope");
  if (level == d->d_offset)
    return new Keiko::Local(d->d_offset);
  Inst *chain = staticChain(level - lev);
  return new Keiko::Offset(chain, new Keiko::Const(d->d_offset));
}

Inst *boundCheck(Inst *inst, Expr *e) {
  if (typeid(e->type) != typeid(Array))
    throw std::domain_error("bound on non aray");
  Array *t = (Array *)e->type;
  return new Keiko::Bound(inst, new Keiko::Const(t->length));
}

Inst *KGen::genAddr(Variable *v) { return address(v->x->getDef()); }

Inst *KGen::genAddr(Sub *sub) {
  Inst *arr = genAddr(sub->arr);
  Inst *ind = genExpr(sub->ind);
  Inst *word = new Keiko::Const(sub->type->size());
  Inst *off;
  if (boundcheck)
    off = new Keiko::Binop(Times, boundCheck(ind, sub->arr), word);
  else
    off = new Keiko::Binop(Times, ind, word);
  return new Keiko::Offset(arr, off);
}

Inst *KGen::genAddr(Expr *e) {
  const std::type_info &t = typeid(*e);
  if (t == typeid(Variable)) {
    Variable *v = (Variable *)e;
    return genAddr(v);
  }
  if (t == typeid(Sub)) {
    Sub *sub = (Sub *)e;
    return genAddr(sub);
  }
  throw std::domain_error("genAddr called on invalid value");
}

/***************
 *  GenCond
 **************/

Inst *KGen::genCond(Binop *binop, int lab1, int lab2) {
  vector<Inst *> *insts = new vector<Inst *>();

  if (binop->o == Or) {
    int lab3 = label1.incr();
    insts->push_back(genCond(binop->el, lab1, lab3));
    insts->push_back(new Keiko::Label(lab3));
    insts->push_back(genCond(binop->er, lab1, lab2));
  } else if (binop->o == And) {
    int lab3 = label1.incr();
    insts->push_back(genCond(binop->el, lab3, lab2));
    insts->push_back(new Keiko::Label(lab3));
    insts->push_back(genCond(binop->er, lab1, lab2));
  } else if (binop->o == Eq || binop->o == Neq || binop->o == Gt ||
             binop->o == Lt || binop->o == Leq || binop->o == Geq) {
    insts->push_back(new Keiko::Jumpc(pair<op, int>(binop->o, lab1),
                                      genExpr(binop->el), genExpr(binop->er)));
    insts->push_back(new Keiko::Jump(lab2));
  } else {
    insts->push_back(new Keiko::Jumpc(pair<op, int>(Neq, lab1), genExpr(binop),
                                      new Keiko::Const(0)));
    insts->push_back(new Keiko::Jump(lab2));
  }

  return new Keiko::Seq(insts);
}

Inst *KGen::genCond(Monop *monop, int lab1, int lab2) {
  vector<Inst *> *insts = new vector<Inst *>();
  if (monop->o == Not)
    return genCond(monop->e, lab2, lab1);
  else {
    insts->push_back(new Keiko::Jumpc(pair<op, int>(Neq, lab1), genExpr(monop),
                                      new Keiko::Const(0)));
    insts->push_back(new Keiko::Jump(lab2));
  }
  return new Keiko::Seq(insts);
}

Inst *KGen::genCond(Expr *e, int lab1, int lab2) {
  const std::type_info &t = typeid(*e);
  if (t == typeid(Monop))
    return genCond((Monop *)e, lab1, lab2);
  else if (t == typeid(Binop))
    return genCond((Binop *)e, lab1, lab2);
  else {
    vector<Inst *> *insts = new vector<Inst *>();
    insts->push_back(new Keiko::Jumpc(pair<op, int>(Neq, lab1), genExpr(e),
                                      new Keiko::Const(0)));
    insts->push_back(new Keiko::Jump(lab2));
    return new Keiko::Seq(insts);
  }
}

/***************
 *  GenStmt
 **************/

Inst *KGen::genStmt(Stmt *e) {
  const std::type_info &t = typeid(*e);
  if (t == typeid(Skip)) {
    Skip *s = (Skip *)e;
    return genStmt(s);
  }
  if (t == typeid(Newline)) {
    Newline *n = (Newline *)e;
    return genStmt(n);
  }
  if (t == typeid(Seq)) {
    Seq *monop = (Seq *)e;
    return genStmt(monop);
  }
  if (t == typeid(Assign)) {
    Assign *binop = (Assign *)e;
    return genStmt(binop);
  }
  if (t == typeid(Return)) {
    Return *call = (Return *)e;
    return genStmt(call);
  }
  if (t == typeid(IfStmt)) {
    IfStmt *ie = (IfStmt *)e;
    return genStmt(ie);
  }
  if (t == typeid(WhileStmt)) {
    WhileStmt *sub = (WhileStmt *)e;
    return genStmt(sub);
  }
  if (t == typeid(Print)) {
    Print *sub = (Print *)e;
    return genStmt(sub);
  }
  throw std::domain_error("failed to match any expression type");
}

Inst *KGen::genStmt(Skip *skip) { return new Keiko::Nop(); }

Inst *KGen::genStmt(Newline *nl) { return new Keiko::Nop(); }

Inst *KGen::genStmt(Seq *sequence) {
  vector<Inst *> *stmts = new vector<Inst *>();
  for (Stmt *stmt : *sequence->stmts)
    stmts->push_back(genStmt(stmt));
  return new Keiko::Seq(stmts);
}

Inst *KGen::genStmt(Assign *assign) {
  Inst *source = genExpr(assign->e);
  Inst *addr = genAddr(assign->x);
  if (assign->x->type->size() == 1)
    return new Keiko::Storec(source, addr);
  else
    return new Keiko::Storew(source, addr);
}

Inst *KGen::genStmt(Return *rt) {
  if (rt->e) {
    vector<Inst *> *stmts = new vector<Inst *>();
    stmts->push_back(new Keiko::Resultw(genExpr(rt->e)));
    stmts->push_back(new Keiko::Jump(retlab));
    return new Keiko::Seq(stmts);
  } else
    return new Keiko::Jump(retlab);
}

Inst *KGen::genStmt(IfStmt *ifstmt) {
  int l1 = label1.incr();
  int l2 = label1.incr();
  int l3 = label1.incr();

  vector<Inst *> *insts = new vector<Inst *>();
  insts->push_back(genCond(ifstmt->cond, l1, l2));
  insts->push_back(new Keiko::Label(l1));
  insts->push_back(genStmt(ifstmt->ifStmt));
  insts->push_back(new Keiko::Jump(l3));
  insts->push_back(new Keiko::Label(l2));
  insts->push_back(genStmt(ifstmt->elseStmt));
  insts->push_back(new Keiko::Label(l3));
  return new Keiko::Seq(insts);
}

Inst *KGen::genStmt(WhileStmt *whilestmt) {
  int l1 = label1.incr();
  int l2 = label1.incr();
  int l3 = label1.incr();

  vector<Inst *> *insts = new vector<Inst *>();
  insts->push_back(new Keiko::Label(l1));
  insts->push_back(genCond(whilestmt->cond, l2, l3));
  insts->push_back(new Keiko::Label(l2));
  insts->push_back(genStmt(whilestmt->st));
  insts->push_back(new Keiko::Jump(l1));
  insts->push_back(new Keiko::Label(l3));
  return new Keiko::Seq(insts);
}

// For now, let's not allow printing
Inst *KGen::genStmt(Print *print) { return new Keiko::Nop(); }


/*************
 ** GenProc **
 *************/

Inst *KGen::genProc(Proc *proc) {

}

// I need to take a different approach since i want this to be separate from the code
// generation part. 
//
// In keiko, we call the Tgen.translsate as the root translator function, that int turn
// calls the Tran.translate function. I want the parts to be decoupled, so in KGen, i
// will only generate the intermediate tree. then simplify it, and then produce the arm
// code. 
//
// For procs, i need to calculate all the necessary stuff in here
