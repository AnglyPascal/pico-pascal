#ifndef DRIVER_H
#define DRIVER_H

#include <string>

#include "parser.h"
#include "scanner.h"
#include "tree.h"

using std::istream;
using std::ostream;

namespace Pascal {

class Driver {
  void parse_helper(istream &stream);

  Pascal::Parser *parser = nullptr;
  Pascal::Scanner *scanner = nullptr;

  /** define some pretty colors **/
  /* const string red = "\033[1;31m"; */
  /* const string blue = "\033[1;36m"; */
  /* const string norm = "\033[0m"; */

public:
  Pascal::Program *parse_tree = nullptr;
  string *errmssg = new string();

  Driver() = default;

  virtual ~Driver();

  /**
   * parse - parse from a file
   * @param filename - valid string with input file
   */
  void parse(const char *filename);

  /**
   * parse - parse from a c++ input stream
   * @param is - istream&, valid input stream
   */
  void parse(istream &iss);
};

} // namespace Pascal
#endif
