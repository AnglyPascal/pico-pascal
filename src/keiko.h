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

#include <string>

using std::string;

namespace Keiko {

enum op {
  Plus,
  Minus,
  Times,
  Div,
  Mod,
  Eq,
  Uminus,
  Lt,
  Gt,
  Leq,
  Geq,
  Neq,
  And,
  Or,
  Not,
  Lsl,
  Lsr,
  Asr,
  BitAnd,
  BitOr,
  BitNot
};

/*****************
 *  LABEL
 *****************/

struct {
  int incr() { return ++lab; }

private:
  int lab = 0;
} Label;

typedef string symbol;
typedef std::pair<op, int> fork;

struct Inst {
  Inst();
  virtual ~Inst() = 0;
};

struct Const : public Inst {
  int n;

  Const(int _n);
  ~Const();
};

struct Global : public Inst {
  symbol x;

  Global(symbol _x);
  ~Global();
};

struct Local : public Inst {
  int offset;

  Local(int _offset);
  ~Local();
};

struct Loadc : public Inst {
  Inst *inst;

  Loadc(Inst *_inst);
  ~Loadc();
};

struct Loadw : public Inst {
  Inst *inst;

  Loadw(Inst *_inst);
  ~Loadw();
};

struct Storec : public Inst {
  Inst *inst;

  Storec(Inst *_inst);
  ~Storec();
};
struct Storew : public Inst {
  Inst *inst;

  Storew(Inst *_inst);
  ~Storew();
};
struct Resultw : public Inst {
  Inst *inst;

  Resultw(Inst *_inst);
  ~Resultw();
};

struct Arg : public Inst {
  int ind;

  Arg(int _ind);
  ~Arg();
};

struct Static : public Inst {
  Static();
  ~Static();
};

struct Call : public Inst {
  int nparams;
  Inst *func;

  Call(int _nparams, Inst *_func);
  ~Call();
};

struct Monop : public Inst {
  op o;
  Inst *e;

  Monop(op _o, Inst *_e);
  ~Monop();
};

struct Binop : public Inst {
  op o;
  Inst *el, *er;

  Binop(op _o, Inst *_el, Inst *_er);
  ~Binop();
};

struct Offset : public Inst {
  Inst *base, *offset;

  Offset(Inst *_base, Inst *_offset);
  ~Offset();
};

struct Bound : public Inst {
  Inst *arr, *bound;

  Bound(Inst *_arr, Inst *_bound);
  ~Bound();
};

struct Jump : public Inst {
  int lab;

  Jump(int _lab);
  ~Jump();
};

struct Jumpc : public Inst {
  fork lab;
  Inst *ifc, *elsec;

  Jumpc(fork _lab, Inst *_ifc, Inst *_elsec);
  ~Jumpc();
};

} // namespace Keiko

#endif
