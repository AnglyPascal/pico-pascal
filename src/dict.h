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

#ifndef DICT_H
#define DICT_H

#include <map>
#include <stdexcept>
#include <stdio.h>
#include <string>

#include "print.h"
#include "types.h"

using std::map;
using std::string;

typedef string ident;
typedef int codelab;

namespace Pascal {

/*****************
 *  LABEL
 *****************/

struct Label {
  int incr() { return ++lab; }

private:
  int lab = 0;
};

/*****************
 *    LOCATION
 *****************/

struct Location {
  Location() = default;
  ~Location() = default;
  virtual Location *clone() const = 0;
  virtual string str() const = 0;
};
struct Local : public Location {
  int offset;
  Local(int _offset);
  ~Local();
  Location *clone() const;
  string str() const;
};
struct Global : public Location {
  string label;
  Global(string _label);
  ~Global();
  Location *clone() const;
  string str() const;
};

/*****************
 *    DEFKIND
 *****************/

struct Defn;

struct DefKind {
  virtual ~DefKind();
  virtual DefKind *clone() const = 0;
  virtual bool isVariable() const;
  virtual string str() const;
};

struct VarDef : public DefKind {
  VarDef();
  ~VarDef();
  DefKind *clone() const;
  bool isVariable() const;
  string str() const;
};

struct ProcDef : public DefKind {
  int _nparams, _argSize;
  vector<Defn *> *_args;

  void addArgs(vector<Defn *> defs);

  ProcDef();
  ~ProcDef();
  DefKind *clone() const;
  ProcDef &operator=(const ProcDef &other);

  string str() const;
};

// need to define it to differentiate between defined procedure vs procedures
// passed as parameters
//
/* struct PProcDec : public DefKind { */

/* } */

/*****************
 *     DEFN
 *****************/

struct Defn {
  ident d_tag;
  DefKind *d_kind = nullptr;
  int d_level;
  // change the offset to address, and create a datatype for that
  Location *d_addr;
  Type *d_type;

  Defn();
  Defn(ident _tag, DefKind *_kind, int _level, Type *_type);
  ~Defn();

  void addArgs(vector<Defn *> defs);
  int nparams() const;

  Defn *clone() const;
  Defn &operator=(const Defn *other);

  string str() const;
};

/*****************
 *  ENVIRONMENT
 *****************/

class Env {
  map<string, Defn *> env;

public:
  Env();
  Env(Env *env);
  ~Env();

  void define(Defn *d);
  Defn *lookup(string tag);
};

} // namespace Pascal

#endif
