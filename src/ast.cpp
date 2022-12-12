#include "tree.h"

using namespace Pascal;

int main() {

  Expr *e = new Constant(1);
  Name *n = makeName("x", 0);
  Stmt *s = new Assign(n, e);
  WhileStmt *w = new WhileStmt(e, s);
  vector<Stmt *> *v = new vector<Stmt *>();
  v->push_back(s);
  v->push_back(w);

  Block *b = new Block(new vector<ident>(), new vector<Proc *>(), sequence(v));
  Program *pgm = new Program(b);
  std::cout << pgm->str() << std::endl;;

  return 0;
}
