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

#include "keiko.h"

using namespace Keiko;

Const::Const(int _n) : n(_n) {}

Global::Global(symbol _x) : x(_x) {}

Local::Local(int _x) : offset(_x) {}

Loadc::Loadc(Inst *_inst) : inst(_inst) {}
Loadc::~Loadc() { delete inst; }

Loadw::Loadw(Inst *_inst) : inst(_inst) {}
Loadw::~Loadw() { delete inst; }

Storec::Storec(Inst *_inst) : inst(_inst) {}
Storec::~Storec() { delete inst; }

Storew::Storew(Inst *_inst) : inst(_inst) {}
Storew::~Storew() { delete inst; }

Resultw::Resultw(Inst *_inst) : inst(_inst) {}
Resultw::~Resultw() { delete inst; }

Arg::Arg(int _ind) : ind(_ind) {}

Call::Call(int _nparams, Inst *_func) : nparams(_nparams), func(_func) {}
Call::~Call() { delete func; }

Monop::Monop(op _o, Inst *_e) : o(_o), e(_e) {}
Monop::~Monop() { delete e; }

Binop::Binop(op _o, Inst *_el, Inst *_er) : o(_o), el(_el), er(_er) {}
Binop::~Binop() {
  delete el;
  delete er;
}

Offset::Offset(Inst *_base, Inst *_offset) : base(_base), offset(_offset) {}
Offset::~Offset() {
  delete base;
  delete offset;
}

Bound::Bound(Inst *_arr, Inst *_bound) : arr(_arr), bound(_bound) {}
Bound::~Bound() {
  delete arr;
  delete bound;
}

Label::Label(int _lab) : lab(_lab) {}

Jump::Jump(int _lab) : lab(_lab) {}

Jumpc::Jumpc(fork _lab, Inst *_ifc, Inst *_elsec)
    : lab(_lab), ifc(_ifc), elsec(_elsec){};
Jumpc::~Jumpc() {
  delete ifc;
  delete elsec;
}

Seq::Seq(vector<Inst *> *_insts) : insts(_insts) {}
Seq::~Seq() {
  for (Inst *inst : *insts)
    delete inst;
}

Line::Line(int _line) : line(_line) {}