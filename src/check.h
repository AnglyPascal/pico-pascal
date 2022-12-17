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

#ifndef CHECK_H
#define CHECK_H

#include "tree.h"
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

namespace Pascal {

int err_line = 0;

class Check {
  Program *pgm;

  Check(Program *_pgm);
  ~Check();

  void check(Env *env);

  void checkStmt(Stmt *stmt, bool inproc, Env *env);
  void check(Seq *sts, bool inproc, Env *env);
  void check(Assign *ae, bool inproc, Env *env);
  void check(Return *rt, bool inproc, Env *env);
  void check(IfStmt *ist, bool inproc, Env *env);
  void check(WhileStmt *wst, bool inproc, Env *env);
  void check(Print *p, bool inproc, Env *env);

  void checkVar(Expr *expr, Env *env);

  void check(Proc *proc, int level, Env *env);

  Type *checkExpr(Expr *expr, Env *env);
  Type *check(Monop *monop, Env *env);
  Type *check(Binop *binop, Env *env);
  Type *check(Sub *sub, Env *env);
  Type *check(Call *call, Env *env);
  Type *check(IfExpr *ie, Env *env);

  Type *check(Decl *decl, Env *env);
};

class semantic_error : public std::domain_error {
public:
  explicit semantic_error(char const *const message) throw();
  virtual char const *what() const throw();
};

} // namespace Pascal

#endif
