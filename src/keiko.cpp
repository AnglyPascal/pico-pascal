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

Inst::Inst() {}
Inst::~Inst() {}

Const::Const(int _n) : n(_n) {}

Global::Global(symbol _x) : x(_x) {}

Local::Local(int _x) : offset(_x) {}

Loadc::Loadc(Inst *_inst) : inst(_inst) {}
Loadc::~Loadc() { delete inst; }

Loadw::Loadw(Inst *_inst) : inst(_inst) {}
Loadw::~Loadw() { delete inst; }

Storec::Storec(Inst *_source, Inst *_addr) : source(_source), addr(_addr) {}
Storec::~Storec() {
  delete source;
  delete addr;
}

Storew::Storew(Inst *_source, Inst *_addr) : source(_source), addr(_addr) {}
Storew::~Storew() {
  delete source;
  delete addr;
}

Resultw::Resultw(Inst *_inst) : inst(_inst) {}
Resultw::~Resultw() { delete inst; }

Arg::Arg(int _ind, Inst *_arg) : ind(_ind), arg(_arg) {}
Arg::~Arg() { delete arg; }

Call::Call(int _nparams, Inst *_func, Static *_staticLink, Seq *_args)
    : nparams(_nparams), func(_func), staticLink(_staticLink), args(_args) {}
Call::~Call() {
  delete func;
  delete staticLink;
  delete args;
}

Static::Static(Inst *_link) : link(_link) {}
Static::~Static() { delete link; }

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

GlobalDecl::GlobalDecl(string _label) : label(_label) {}
GlobalDecl::~GlobalDecl() {}

ProcDecl::ProcDecl(string _label, int _level, int _nparams, int _argSize,
                   int _locSize, Inst *_code)
    : label(_label), level(_level), nparams(_nparams), argSize(_argSize),
      locSize(_locSize), code(_code) {}
ProcDecl::~ProcDecl() { delete code; }

Program::Program(vector<GlobalDecl *> *_globDecls,
                 vector<ProcDecl *> *_procDecls)
    : globDecls(_globDecls), procDecls(_procDecls) {}
Program::~Program() {
  for (GlobalDecl *g : *globDecls)
    delete g;
  delete globDecls;
  for (ProcDecl *p : *procDecls)
    delete p;
  delete procDecls;
};

/** Typing */

KeikoType Nop::type() { return K_Nop; }
KeikoType Seq::type() { return K_Seq; }
KeikoType Line::type() { return K_Line; }
KeikoType Const::type() { return K_Const; }
KeikoType Global::type() { return K_Global; }
KeikoType Local::type() { return K_Local; }
KeikoType Loadw::type() { return K_Loadw; }
KeikoType Loadc::type() { return K_Loadc; }
KeikoType Storew::type() { return K_Storew; }
KeikoType Storec::type() { return K_Storec; }
KeikoType Resultw::type() { return K_Resultw; }
KeikoType Arg::type() { return K_Arg; }
KeikoType Static::type() { return K_Static; }
KeikoType Call::type() { return K_Call; }
KeikoType Monop::type() { return K_Monop; }
KeikoType Binop::type() { return K_Binop; }
KeikoType Offset::type() { return K_Offset; }
KeikoType Label::type() { return K_Label; }
KeikoType Jump::type() { return K_Jump; }
KeikoType Jumpc::type() { return K_Jumpc; }
KeikoType Bound::type() { return K_Bound; }
KeikoType GlobalDecl::type() { return K_GlobalDecl; }
KeikoType ProcDecl::type() { return K_ProcDecl; }
KeikoType Program::type() { return K_Program; }

/** Cloning */

Inst *Nop::clone() { return this; }
Inst *Seq::clone() {
  vector<Inst *> *ninsts = new vector<Inst *>();
  for (Inst *i : *insts)
    ninsts->push_back(i->clone());
  return new Seq(ninsts);
}
Inst *Line::clone() { return new Line(line); }
Inst *Const::clone() { return new Const(n); }
Inst *Global::clone() { return new Global(x); }
Inst *Local::clone() { return new Local(offset); }
Inst *Loadw::clone() { return new Loadw(inst->clone()); }
Inst *Loadc::clone() { return new Loadc(inst->clone()); }
Inst *Storew::clone() { return new Storew(source->clone(), addr->clone()); }
Inst *Storec::clone() { return new Storec(source->clone(), addr->clone()); }
Inst *Resultw::clone() { return new Resultw(inst->clone()); }
Inst *Arg::clone() { return new Arg(ind, arg->clone()); }
Inst *Static::clone() { return new Static(link->clone()); }
Inst *Call::clone() {
  return new Call(nparams, func->clone(), (Static *)staticLink->clone(),
                  (Seq *)args->clone());
}
Inst *Monop::clone() { return new Monop(o, e->clone()); }
Inst *Binop::clone() { return new Binop(o, el->clone(), er->clone()); }
Inst *Offset::clone() { return new Offset(base->clone(), offset->clone()); }
Inst *Label::clone() { return new Label(lab); }
Inst *Jump::clone() { return new Jump(lab); }
Inst *Jumpc::clone() { return new Jumpc(lab, ifc->clone(), elsec->clone()); }
Inst *Bound::clone() { return new Bound(arr->clone(), bound->clone()); }
Inst *GlobalDecl::clone() { return new GlobalDecl(label); }
Inst *ProcDecl::clone() {
  return new ProcDecl(label, level, nparams, argSize, locSize, code->clone());
}

Inst *Program::clone() {
  vector<GlobalDecl *> *_globDecls = new vector<GlobalDecl *>();
  vector<ProcDecl *> *_procDecls = new vector<ProcDecl *>();
  for (GlobalDecl *gdl : *globDecls)
    _globDecls->push_back((GlobalDecl *)gdl->clone());
  for (ProcDecl *pdl : *procDecls)
    _procDecls->push_back((ProcDecl *)pdl->clone());
  return new Program(_globDecls, _procDecls);
}

