#include <cassert>
#include <cctype>
#include <fstream>

#include "driver.h"

namespace Pascal {

Driver::~Driver() {
  delete scanner;
  scanner = nullptr;
  delete parser;
  parser = nullptr;
  delete parse_tree;
  parse_tree = nullptr;
}

void Driver::parse(const char *const filename) {
  /**
   * Remember, if you want to have checks in release mode
   * then this needs to be an if statement
   */
  assert(filename != nullptr);
  std::ifstream in_file(filename);

  if (!in_file.good())
    exit(EXIT_FAILURE);

  parse_helper(in_file);
}

void Driver::parse(istream &stream) {
  if (!stream.good() && stream.eof())
    return;
  parse_helper(stream);
}

void Driver::parse_helper(istream &stream) {

  delete scanner;
  try {
    scanner = new Scanner(&stream);
  } catch (std::bad_alloc &ba) {
    std::cerr << "Failed to allocate scanner: (" << ba.what()
              << "), exiting!!\n";
    exit(EXIT_FAILURE);
  }

  delete parser;
  try {
    parser = new Parser((*scanner), (*this), parse_tree, errmssg);
  } catch (std::bad_alloc &ba) {
    std::cerr << "Failed to allocate parser: (" << ba.what()
              << "), exiting!!\n";
    exit(EXIT_FAILURE);
  }

  const int accept(0);
  if (parser->parse() != accept)
    std::cerr << "Parse failed!!\n";

  return;
}
} // namespace Pascal
