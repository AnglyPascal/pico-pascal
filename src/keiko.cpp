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

map<op, string> opNames = {{Pascal::Plus, "Plus"},     {Pascal::Minus, "Minus"},
                           {Pascal::Times, "Times"},   {Pascal::Div, "Div"},
                           {Pascal::Mod, "Mod"},       {Pascal::Eq, "Eq"},
                           {Pascal::Uminus, "Uminus"}, {Pascal::Lt, "Lt"},
                           {Pascal::Gt, "Gt"},         {Pascal::Leq, "Leq"},
                           {Pascal::Geq, "Geq"},       {Pascal::Neq, "Neq"},
                           {Pascal::And, "And"},       {Pascal::Or, "Or"},
                           {Pascal::Not, "Not"},       {Pascal::Lsl, "Lsl"},
                           {Pascal::Lsr, "Lsr"},       {Pascal::Asr, "Asr"},
                           {Pascal::BitAnd, "BitAnd"}, {Pascal::BitOr, "BitOr"},
                           {Pascal::BitNot, "BitNot"}};

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

Arg::Arg(int _ind, Inst *_arg) : ind(_ind), arg(_arg) { delete arg; }

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

/***********************
 ** string generation **
 ***********************/

string Const::str(string tab) const {
  return tab + "<CONST " + std::to_string(n) + ">";
}
string Global::str(string tab) const { return tab + "<GLOBAL " + x + ">"; }
string Local::str(string tab) const {
  return tab + "<LOCAL " + std::to_string(offset) + ">";
}
string Loadc::str(string tab) const {
  return tab + "<LOADC,\n" + inst->str(tab + " ") + ">";
}
string Loadw::str(string tab) const {
  return tab + "<LOADW,\n" + inst->str(tab + " ") + ">";
}
string Storec::str(string tab) const {
  return tab + "<STOREC,\n" + source->str(tab + " ") + "\n" +
         addr->str(tab + " ") + ">";
}
string Storew::str(string tab) const {
  return tab + "<STOREW,\n" + source->str(tab + " ") + "\n" +
         addr->str(tab + " ") + ">";
}
string Resultw::str(string tab) const {
  return tab + "<RESULTW,\n" + inst->str(tab + " ") + ">";
}
string Arg::str(string tab) const {
  return tab + "<ARG " + std::to_string(ind) + ",\n" + arg->str(tab) + ">";
}
string Static::str(string tab) const {
  return tab + "<STATIC\n" + link->str(tab) + ">";
}
string Call::str(string tab) const {
  string s = tab + "<CALL " + std::to_string(nparams) + ",\n";
  s += func->str(tab);
  s += ", ";
  s += staticLink->str(tab);
  s += ", ";

  string a = "";
  for (Inst *arg : *args->insts)
    a += arg->str(tab) + "\n";
  s += a + tab + ">";
  return s;
}
string Monop::str(string tab) const {
  return tab + "<MONOP " + opNames[o] + ",\n" + e->str(tab + " ") + ">";
}
string Binop::str(string tab) const {
  return tab + "<MONOP " + opNames[o] + ",\n" + el->str(tab + " ") + "\n" +
         er->str(tab + " ") + ">";
}
string Offset::str(string tab) const {
  return tab + "<OFFSET,\n" + base->str(tab + " ") + "\n" +
         offset->str(tab + " ") + ">";
}
string Bound::str(string tab) const {
  return tab + "<BOUND,\n" + arr->str(tab + " ") + "\n" +
         bound->str(tab + " ") + ">";
}
string Label::str(string tab) const {
  return tab + "<LABEL " + std::to_string(lab) + ">";
}
string Jump::str(string tab) const {
  return tab + "<JUMP " + std::to_string(lab) + ">";
}
string Jumpc::str(string tab) const {
  string s = tab + "<JUMPC " + opNames[lab.first] + " " +
             std::to_string(lab.second) + "\n";
  s += ifc->str(tab + " ");
  s += elsec->str(tab + " ");
  s += "\n" + tab + ">";
  return s;
}
string Seq::str(string tab) const {
  string s = tab + "<SEQ,\n";
  for (Inst *inst : *insts)
    s += inst->str(tab + " ") + "\n";
  return s + tab + ">\n";
}
string Line::str(string tab) const {
  return tab + "<LINE " + std::to_string(line) + ">";
}
string Nop::str(string tab) const { return ""; }

string GlobalDecl::str(string tab) const { return ""; }
string ProcDecl::str(string tab) const { return ""; }
string Program::str(string tab) const { return ""; }
