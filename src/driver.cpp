#include <cassert>
#include <cctype>
#include <fstream>

#include "driver.h"

Pascal::Driver::~Driver() {
  delete (scanner);
  scanner = nullptr;
  delete (parser);
  parser = nullptr;
}

void Pascal::Driver::parse(const char *const filename) {
  /**
   * Remember, if you want to have checks in release mode
   * then this needs to be an if statement
   */
  assert(filename != nullptr);
  std::ifstream in_file(filename);
  if (!in_file.good()) {
    exit(EXIT_FAILURE);
  }
  parse_helper(in_file);
  return;
}

void Pascal::Driver::parse(std::istream &stream) {
  if (!stream.good() && stream.eof()) {
    return;
  }
  // else
  parse_helper(stream);
  return;
}

void Pascal::Driver::parse_helper(std::istream &stream) {

  delete (scanner);
  try {
    scanner = new Pascal::Scanner(&stream);
  } catch (std::bad_alloc &ba) {
    std::cerr << "Failed to allocate scanner: (" << ba.what()
              << "), exiting!!\n";
    exit(EXIT_FAILURE);
  }

  delete (parser);
  try {
    parser = new Pascal::Parser((*scanner) /* scanner */, (*this) /* driver */);
  } catch (std::bad_alloc &ba) {
    std::cerr << "Failed to allocate parser: (" << ba.what()
              << "), exiting!!\n";
    exit(EXIT_FAILURE);
  }
  const int accept(0);
  if (parser->parse() != accept) {
    std::cerr << "Parse failed!!\n";
  }
  return;
}

void Pascal::Driver::add_upper() {
  uppercase++;
  chars++;
  words++;
}

void Pascal::Driver::add_lower() {
  lowercase++;
  chars++;
  words++;
}

void Pascal::Driver::add_word(const std::string &word) {
  words++;
  chars += word.length();
  for (const char &c : word) {
    if (islower(c)) {
      lowercase++;
    } else if (isupper(c)) {
      uppercase++;
    }
  }
}

void Pascal::Driver::add_newline() {
  lines++;
  chars++;
}

void Pascal::Driver::add_char() { chars++; }

std::ostream &Pascal::Driver::print(std::ostream &stream) {
  /** NOTE: Colors are defined as class variables w/in Driver **/
  stream << red << "Results: " << norm << "\n";
  stream << blue << "Uppercase: " << norm << uppercase << "\n";
  stream << blue << "Lowercase: " << norm << lowercase << "\n";
  stream << blue << "Lines: " << norm << lines << "\n";
  stream << blue << "Words: " << norm << words << "\n";
  stream << blue << "Characters: " << norm << chars << "\n";
  return (stream);
}
