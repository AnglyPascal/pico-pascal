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

#ifndef DRIVER_H
#define DRIVER_H

#include <fstream>
#include <vector>

#include "check.h"
#include "parser.h"
#include "scanner.h"
#include "kgen.h"
#include "keiko.h"
#include "location.hh"

namespace Pascal {

struct Program;

// forward declare our simplistic AST node class so we
// can declare container for it without the header

/**
 * This class is the interface for our scanner/lexer. The end user
 * is expected to use this. It drives scanner/lexer, keeps
 * parsed AST and generally is a good place to store additional
 * context data. Both parser and lexer have access to it via internal
 * references.
 *
 * I know that the AST is a bit too strong word for a simple
 * vector with nodes, but this is only an example. Get off me.
 */
class Driver {
  // Used internally by Parser to insert AST nodes.
  void setProgram(Program *pgm);

  /// stream name (file or input stream) used for error messages.
  std::string streamname;

  // Used internally by Scanner YY_USER_ACTION to update location indicator
  void increaseLocation(unsigned int loc);

  void line();

  // Used to get last Scanner location. Used in error messages.
  location yylloc() const;

  Scanner m_scanner;
  Parser m_parser;
  Program *m_program;
  Inst *m_keiko;

  unsigned int m_column; // Used by scanner
  unsigned int m_line;

public:
  Driver();
  Driver(const std::string &filename);

  /**
   * Run parser. Results are stored inside.
   * \returns 0 on success, 1 on failure
   */
  int parse();

  /** Invoke the scanner and parser for a stream.
   * @param in	input stream
   * @param sname	stream name for error messages
   * @return		true if successfully parsed
   */
  int parse_stream(std::istream &in, const std::string &sname = "stream input");

  /** Invoke the scanner and parser on an input string.
   * @param input	input string
   * @param sname	stream name for error messages
   * @return		true if successfully parsed
   */
  int parse_string(const std::string &input,
                   const std::string &sname = "string stream");

  /** Invoke the scanner and parser on a file. Use parse_stream with a
   * std::ifstream if detection of file reading errors is required.
   * @param filename	input file name
   * @return		true if successfully parsed
   */
  int parse_file(const std::string &filename);

  /**
   * Clear AST
   */
  void clear();

  /**
   * Print AST
   */
  std::string str() const;

  /**
   * Switch scanner input stream. Default is standard input (std::cin).
   * It will also reset AST.
   */
  void switchInputStream(std::istream *is);

  unsigned int totalLines();

  // run semantic analyser
  void check();

  // convert to keiko tree
  void transform();

  void keikoStr() const;

  /**
   * This is needed so that Scanner and Parser can call some
   * methods that we want to keep hidden from the end user.
   */
  friend class Parser;
  friend class Scanner;
};

} // namespace Pascal

#endif // INTERPRETER_H
