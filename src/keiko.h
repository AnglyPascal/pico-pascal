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

#ifndef KEIKO_H
#define KEIKO_H

#include "tree.h"
#include <string>

using std::string;

namespace Keiko {

typedef string symbol;
typedef Pascal::op op;
typedef std::pair<op, int> fork;

struct Inst {
  Inst();
  virtual ~Inst();
  virtual void simplify() = 0;
  virtual string str(string tab) const = 0;
};

struct Seq : public Inst {
  vector<Inst *> *insts;

  Seq(vector<Inst *> *_insts);
  ~Seq();
  void simplify();
  string str(string tab) const;
};

struct Nop : public Inst {
  Nop() = default;
  ~Nop() = default;
  void simplify();
  string str(string tab) const;
};

struct Line : public Inst {
  int line;

  Line(int _line);
  ~Line() = default;
  void simplify();
  string str(string tab) const;
};

struct Const : public Inst {
  int n;

  Const(int _n);
  ~Const() = default;
  void simplify();
  string str(string tab) const;
};

struct Global : public Inst {
  symbol x;

  Global(symbol _x);
  ~Global() = default;
  void simplify();
  string str(string tab) const;
};

struct Local : public Inst {
  int offset;

  Local(int _offset);
  ~Local() = default;
  void simplify();
  string str(string tab) const;
};

struct Loadc : public Inst {
  Inst *inst;

  Loadc(Inst *_inst);
  ~Loadc();
  void simplify();
  string str(string tab) const;
};

struct Loadw : public Inst {
  Inst *inst;

  Loadw(Inst *_inst);
  ~Loadw();
  void simplify();
  string str(string tab) const;
};

struct Storec : public Inst {
  Inst *source, *addr;

  Storec(Inst *_source, Inst *_addr);
  ~Storec();
  void simplify();
  string str(string tab) const;
};

struct Storew : public Inst {
  Inst *source, *addr;

  Storew(Inst *_source, Inst *_addr);
  ~Storew();
  void simplify();
  string str(string tab) const;
};

struct Resultw : public Inst {
  Inst *inst;

  Resultw(Inst *_inst);
  ~Resultw();
  void simplify();
  string str(string tab) const;
};

struct Arg : public Inst {
  int ind;
  Inst *arg;

  Arg(int _ind, Inst *_arg);
  ~Arg() = default;
  void simplify();
  string str(string tab) const;
};

struct Static : public Inst {
  Inst *link;

  Static(Inst *_link);
  ~Static();
  void simplify();
  string str(string tab) const;
};

struct Call : public Inst {
  int nparams;
  Inst *func;
  Static *staticLink;
  Seq *args;

  Call(int _nparams, Inst *_func, Static *staticLink, Seq *args);
  ~Call();
  void simplify();
  string str(string tab) const;
};

struct Monop : public Inst {
  op o;
  Inst *e;

  Monop(op _o, Inst *_e);
  ~Monop();
  void simplify();
  string str(string tab) const;
};

struct Binop : public Inst {
  op o;
  Inst *el, *er;

  Binop(op _o, Inst *_el, Inst *_er);
  ~Binop();
  void simplify();
  string str(string tab) const;
};

struct Offset : public Inst {
  Inst *base, *offset;

  Offset(Inst *_base, Inst *_offset);
  ~Offset();
  void simplify();
  string str(string tab) const;
};

struct Bound : public Inst {
  Inst *arr, *bound;

  Bound(Inst *_arr, Inst *_bound);
  ~Bound();
  void simplify();
  string str(string tab) const;
};

struct Label : public Inst {
  int lab;

  Label(int _lab);
  ~Label() = default;
  void simplify();
  string str(string tab) const;
};

struct Jump : public Inst {
  int lab;

  Jump(int _lab);
  ~Jump() = default;
  void simplify();
  string str(string tab) const;
};

struct Jumpc : public Inst {
  fork lab;
  Inst *ifc, *elsec;

  Jumpc(fork _lab, Inst *_ifc, Inst *_elsec);
  ~Jumpc();
  void simplify();
  string str(string tab) const;
};

} // namespace Keiko

#endif
