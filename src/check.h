#ifndef CHECK_H
#define CHECK_H

#include "tree.h"

namespace Pascal {

class Check {
  Program *pgm;

  Check(Program *_pgm);
  ~Check();

  void check();
  void check(Stmt *stmt);
  void check(Expr *expr);
  void check(Monop *monop);
  void check(Binop *binop);
  void check(Decl *decl);
};

} // namespace Pascal

#endif
