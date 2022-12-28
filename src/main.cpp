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

#include "driver.h"
#include "parser.h"
#include "scanner.h"
#include "tree.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace Pascal;
using namespace std;

string str(Expr *expr) { return expr->str(); }

int main(int argc, char **argv) {
  Driver driver;
  int res;

  if (std::strncmp(argv[1], "-o", 2) == 0)
    res = driver.parse_stream(cin);

  /** simple help menu **/
  /* else if (std::strncmp(argv[1], "-h", 2) == 0) { */
  /*   std::cout << "use -o for pipe to std::cin\n"; */
  /*   std::cout << "just give a filename to count from a file\n"; */
  /*   std::cout << "use -h to get this menu\n"; */
  /*   return (EXIT_SUCCESS); */
  /* } */

  /** example reading input from a file **/
  else
    /** assume file, prod code, use stat to check **/
    res = driver.parse_file(argv[1]);

  driver.check();
  cout << driver.str() << endl;

  return res;
}
