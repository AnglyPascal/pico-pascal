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
#include "tree.h"
#include <sstream>

using namespace Pascal;

using std::cout;
using std::endl;
using std::ifstream;
using std::istream;
using std::string;

Driver::Driver()
    : m_scanner(*this), m_parser(m_scanner, *this), m_program(nullptr),
      m_column(0) {}

Driver::Driver(const string &filename)
    : m_scanner(*this), m_parser(m_scanner, *this), m_program(nullptr),
      m_column(0), m_line(1) {
  ifstream *in = new ifstream(filename.c_str());
  if (!in->good())
    return;
  streamname = filename;
  m_scanner.switch_streams(in, NULL);
}

int Driver::parse() {
  m_column = 0;
  m_line = 1;
  return m_parser.parse();
}

void Driver::clear() {
  m_column = 0;
  m_line = 1;
  m_program = nullptr;
}

string Driver::str() const { return m_program->str(); }

void Driver::switchInputStream(istream *is) {
  m_scanner.switch_streams(is, NULL);
  m_program = nullptr;
}

void Driver::setProgram(Program *pgm) { m_program = pgm; }

void Driver::increaseLocation(unsigned int loc) {
  m_column += loc;
  /* cout << "increaseLocation(): " << loc << ", total = " << m_column << endl;
   */
}

void Driver::line() { 
  m_column = 0;
  m_line += 1; 
}
unsigned int Driver::totalLines() { return m_line; }

location Driver::yylloc() const {
  class location l;
  l.initialize(new string(streamname), m_line, m_column);
  return l;
}

int Driver::parse_stream(std::istream &in, const std::string &sname) {
  streamname = sname;
  switchInputStream(&in);
  return parse();
}

int Driver::parse_file(const string &filename) {
  ifstream in(filename.c_str());
  if (!in.good())
    return false;
  return parse_stream(in, filename);
}

int Driver::parse_string(const string &input, const string &sname) {
  std::istringstream iss(input);
  return parse_stream(iss, sname);
}
