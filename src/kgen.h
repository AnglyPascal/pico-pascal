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

#ifndef KGEN_H
#define KGEN_H

#include "keiko.h"
#include "tree.h"

using Keiko::Inst;
using std::pair;

namespace Pascal {

class KGen {
public:
  Inst *transform(Program *program);

private:
  Inst *address(Defn *d);

  Inst *genAddr(Expr *e);
  Inst *genAddr(Variable *x);
  Inst *genAddr(Sub *sub);

  Inst *genExpr(Expr *exp);
  Inst *genExpr(Constant *c);
  Inst *genExpr(Variable *x);
  Inst *genExpr(Monop *monop);
  Inst *genExpr(Binop *binop);
  Inst *genExpr(IfExpr *e);
  Inst *genExpr(Sub *sub);
  Inst *genExpr(Call *call);

  Inst *genCond(Expr *exp, int lab1, int lab2);
  Inst *genCond(Binop *binop, int lab1, int lab2);
  Inst *genCond(Monop *monop, int lab1, int lab2);

  Inst *genCall(Call *call);

  void genArg(int *i, Type *t, Expr *e, vector<Inst *> *args);
  pair<Inst *, Inst*> genClosure(Defn *d);
  /* Inst *genClosureAddr(Defn *d); */
  /* Inst *genClosureSLink(Defn *d); */

  Inst *genStmt(Stmt *stmt);
  Inst *genStmt(Skip *skip);
  Inst *genStmt(Newline *nl);
  Inst *genStmt(Seq *sequence);
  Inst *genStmt(Assign *assign);
  Inst *genStmt(Return *rt);
  Inst *genStmt(IfStmt *ifstmt);
  Inst *genStmt(WhileStmt *whilestmt);
  Inst *genStmt(Print *print);

  Inst *genBlock(Block *block, vector<Keiko::ProcDecl *> *procs);
  void genProc(Proc *proc, vector<Keiko::ProcDecl *> *procs);
};

} // namespace Pascal

#endif

