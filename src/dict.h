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

#include "types.h"

using std::map;
using std::string;

typedef string ident;
typedef int codelab;

namespace Pascal {

/*****************
 *    DEFKIND
 *****************/

struct DefKind {
  virtual ~DefKind();
  virtual DefKind *clone() = 0;
};

struct VarDef : public DefKind {
  virtual ~VarDef();
  virtual DefKind *clone();
};

struct ProcDef : public DefKind {
  int _nparams;
  ProcDef(int n) : _nparams(n){};

  virtual ~ProcDef();
  virtual DefKind *clone();
  ProcDef &operator=(const ProcDef &other);
};

/*****************
 *     DEFN
 *****************/

struct Defn {
  ident d_tag;
  DefKind *d_kind = nullptr;
  int d_level;
  string d_label;
  int d_offset;
  Type *d_type;

  Defn();
  Defn(ident _tag, DefKind *_kind, int _level, string _label, int _off,
       Type *_type);

  Defn *clone() const;

  virtual ~Defn();
  virtual Defn *clone();
  Defn &operator=(const Defn *other);
};

/*****************
 *  LABEL
 *****************/

struct {
  int incr() { return ++lab; }

private:
  int lab = 0;
} Label;

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
