#include <iostream>
#include "./dict.h"

using namespace std;

using ident = string;

class name {
  ident x_name;
  int x_line;


public:
  name(ident name, int line);
};
