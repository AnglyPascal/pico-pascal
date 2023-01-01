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

/**************
 ** Simplify **
 **************/

Inst *Nop::simplify() { return this; }

Inst *Seq::simplify() {
  if (insts->size() == 0) {
    delete this;
    return new Nop();
  } else if (insts->size() == 1) {
    Inst *inst = (*insts)[0]->clone();
    delete this;
    return inst;
  } else {
    vector<Inst *> *ninsts = new vector<Inst *>();
    for (Inst *inst : *insts) {
      Inst *ninst = inst->simplify();
      if (ninst->type() == K_Seq) {
        for (Inst *i : *((Seq *)ninst)->insts)
          ninsts->push_back(i);
      } else
        ninsts->push_back(ninst);
    }
    delete insts;
    insts = ninsts;
    return this;
  }
  return this;
}

Inst *Line::simplify() { return this; }
Inst *Const::simplify() { return this; }
Inst *Global::simplify() { return this; }
Inst *Local::simplify() { return this; }

Inst *Loadw::simplify() { return this; }
Inst *Loadc::simplify() { return this; }
Inst *Storew::simplify() { return this; }
Inst *Storec::simplify() { return this; }
Inst *Resultw::simplify() { return this; }
Inst *Arg::simplify() { return this; }
Inst *Static::simplify() { return this; }
Inst *Call::simplify() { return this; }
Inst *Monop::simplify() { return this; }
Inst *Binop::simplify() { return this; }
Inst *Offset::simplify() { return this; }
Inst *Label::simplify() { return this; }
Inst *Jump::simplify() { return this; }
Inst *Jumpc::simplify() { return this; }
Inst *Bound::simplify() { return this; }
Inst *GlobalDecl::simplify() { return this; }
Inst *ProcDecl::simplify() { return this; }
Inst *Program::simplify() { return this; }

