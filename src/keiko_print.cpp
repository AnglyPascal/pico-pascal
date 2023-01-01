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
#include "print.h"

using Pascal::Colors;
using std::cout;
using std::endl;
using std::to_string;

string k_pad_const = "  ";
string _err = Colors.Red + "_" + Colors.White;

map<Keiko::op, string> opNames = {
    {Pascal::Plus, "Plus"},     {Pascal::Minus, "Minus"},
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

inline string tab(string pad) { return pad + k_pad_const; }

/***********************
 ** string generation **
 ***********************/

namespace Keiko {

void Const::str(string pad) const {
  debug("Const");
  cout << pad + "<CONST " + to_string(n) + ">" << endl;
}
void Global::str(string pad) const {
  debug("Global");
  cout << pad + "<GLOBAL " + x + ">" << endl;
}
void Local::str(string pad) const {
  debug("Local");
  cout << pad + "<LOCAL " + to_string(offset) + ">" << endl;
}
void Loadc::str(string pad) const {
  debug("Loadc");
  cout << pad + "<LOADC,\n";
  if (inst) {
    inst->str(tab(pad));
    cout << pad + ">" << endl;
  } else
    cout << _err + ">" << endl;
}
void Loadw::str(string pad) const {
  debug("Loadw");
  cout << pad + "<LOADW,\n";
  if (inst) {
    inst->str(tab(pad));
    cout << pad + ">" << endl;
  } else
    cout << _err + ">" << endl;
}
void Storec::str(string pad) const {
  debug("Storec");
  cout << pad + "<STOREC,";
  if (source) {
    cout << endl;
    source->str(tab(pad));
    cout << endl;
  } else {
    cout << " " + _err;
  }

  if (addr) {
    cout << endl;
    addr->str(tab(pad));
    cout << ">" << endl;
  } else {
    cout << ", " + _err << endl;
  }
}
void Storew::str(string pad) const {
  debug("Storew");
  cout << pad + "<STOREW, ";
  if (source) {
    cout << endl;
    source->str(tab(pad));
  } else
    cout << _err + ", " << endl;

  if (addr) {
    addr->str(tab(pad));
    cout << pad + ">" << endl;
  } else
    cout << _err + ">" << endl;
}

void Resultw::str(string pad) const {
  debug("Resultw");
  cout << pad + "<RESULTW, ";
  if (inst) {
    cout << endl;
    inst->str(tab(pad));
    cout << pad + ">" << endl;
  } else {
    cout << _err + ">";
  }
}
void Arg::str(string pad) const {
  debug("Arg");
  cout << pad + "<ARG " + to_string(ind) + ", ";
  if (arg) {
    cout << endl;
    arg->str(tab(pad));
    cout << pad + ">" << endl;
  } else {
    cout << _err + ">" << endl;
  }
}

void Static::str(string pad) const {
  debug("Static");
  cout << pad + "<STATIC, ";
  if (link) {
    cout << endl;
    link->str(tab(pad));
  } else {
    cout << _err << endl;
  }
  cout << pad + ">" << endl;
}

void Call::str(string pad) const {
  debug("Call");
  cout << pad + "<CALL " + to_string(nparams) + ", ";

  if (func) {
    cout << endl;
    func->str(tab(pad));
  } else
    cout << _err + ", " << endl;

  if (staticLink)
    staticLink->str(tab(pad));
  else
    cout << _err << endl;

  for (Inst *arg : *args->insts)
    if (arg) {
      arg->str(tab(pad));
      cout << pad + ">" << endl;
    } else
      cout << _err + ">" << endl;
}

void Monop::str(string pad) const {
  debug("Monop");
  cout << pad + "<MONOP " + opNames[o] + ",";
  if (e) {
    cout << endl;
    e->str(tab(pad));
  } else
    cout << _err;
  cout << ">";
}

void Binop::str(string pad) const {
  debug("Binop");
  cout << pad + "<BINOP " + opNames[o] + "," << endl;
  if (el)
    el->str(tab(pad));
  else
    cout << _err << endl;
  if (er) {
    er->str(tab(pad));
    cout << pad + ">" << endl;
  } else
    cout << _err + ">" << endl;
}

void Offset::str(string pad) const {
  debug("Offset");
  cout << pad + "<OFFSET, ";
  if (base) {
    cout << endl;
    base->str(tab(pad));
  } else
    cout << _err;
  if (offset) {
    offset->str(tab(pad));
    cout << pad + ">" << endl;
  } else
    cout << _err + ">" << endl;
}

void Bound::str(string pad) const {
  debug("Bound");
  cout << pad + "<BOUND, ";
  if (arr) {
    cout << endl;
    arr->str(tab(pad));
  } else
    cout << _err;
  cout << ", ";
  if (bound) {
    cout << endl;
    bound->str(tab(pad));
  } else
    cout << _err;
  cout << ">";
}

void Label::str(string pad) const {
  debug("Label");
  cout << pad + "<LABEL " + to_string(lab) + ">" << endl;
}

void Jump::str(string pad) const {
  debug("Jump");
  cout << pad + "<JUMP " + to_string(lab) + ">" << endl;
}

void Jumpc::str(string pad) const {
  debug("Jumpc");
  cout << pad + "<JUMPC " + opNames[lab.first] + ", " + to_string(lab.second) +
              ", ";
  if (ifc) {
    cout << endl;
    ifc->str(tab(pad));
  } else
    cout << _err << endl;

  if (elsec) {
    elsec->str(tab(pad));
  } else
    cout << _err;
  cout << pad + ">" << endl;
}

void Seq::str(string pad) const {
  debug("Seq");
  cout << pad + "<SEQ," << endl;
  for (Inst *inst : *insts) {
    if (inst)
      inst->str(tab(pad));
    else
      cout << _err;
  }
  cout << pad + ">" << endl;
}

void Line::str(string pad) const {
  debug("Line");
  cout << pad + "<LINE " + to_string(line) + ">" << endl;
}

void Nop::str(string pad) const { debug("Nop"); }

void GlobalDecl::str(string pad) const {
  debug("GlobalDecl");
  cout << pad + "<GLOBAL_DECL " + label + ">";
}

void ProcDecl::str(string pad) const {
  debug("ProcDecl");
  string s = pad + "<PROC_DECL " + label;
  s += ", " + to_string(nparams);
  s += ", " + to_string(argSize);
  s += ", " + to_string(locSize);
  s += ">\n";
  cout << s;

  if (code)
    code->str(tab(pad));
  else
    cout << _err << endl;
}

void Program::str(string pad) const {
  debug("Program");
  for (GlobalDecl *g : *globDecls)
    if (g) {
      g->str(pad);
      cout << endl;
    } else
      cout << _err;

  for (ProcDecl *p : *procDecls)
    if (p) {
      p->str(pad);
      cout << endl;
    } else
      cout << _err << endl;
}

} // namespace Keiko
