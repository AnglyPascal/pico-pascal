#include "tree.h"
#include <iostream>
using namespace std;

int main() {
  expr *e1 = new Constant(3);
  expr *e2 = new Constant(1);
  expr *e = new Binop(op::Plus, e1, e2);
  cout << e->str() << endl;
  return 0;
}
