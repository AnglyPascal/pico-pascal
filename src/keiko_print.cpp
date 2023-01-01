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

string k_pad_const = "  ";
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

using std::to_string;

/***********************
 ** string generation **
 ***********************/

namespace Keiko {

string Const::str(string pad) const {
  return pad + "<CONST " + to_string(n) + ">";
}
string Global::str(string pad) const { return pad + "<GLOBAL " + x + ">"; }
string Local::str(string pad) const {
  return pad + "<LOCAL " + to_string(offset) + ">";
}
string Loadc::str(string pad) const {
  return pad + "<LOADC,\n" + inst->str(pad + k_pad_const) + ">";
}
string Loadw::str(string pad) const {
  return pad + "<LOADW,\n" + inst->str(pad + k_pad_const) + ">";
}
string Storec::str(string pad) const {
  return pad + "<STOREC,\n" + source->str(pad + k_pad_const) + "\n" +
         addr->str(pad + k_pad_const) + ">";
}
string Storew::str(string pad) const {
  return pad + "<STOREW,\n" + source->str(pad + k_pad_const) + "\n" +
         addr->str(pad + k_pad_const) + ">";
}
string Resultw::str(string pad) const {
  return pad + "<RESULTW,\n" + inst->str(pad + k_pad_const) + ">";
}
string Arg::str(string pad) const {
  return pad + "<ARG " + to_string(ind) + ",\n" + arg->str(pad) + ">";
}
string Static::str(string pad) const {
  return pad + "<STATIC\n" + link->str(pad) + ">";
}
string Call::str(string pad) const {
  string s = pad + "<CALL " + to_string(nparams) + ",\n";
  s += func->str(pad);
  s += ", ";
  s += staticLink->str(pad);
  s += ", ";

  string a = "";
  for (Inst *arg : *args->insts)
    a += arg->str(pad) + "\n";
  s += a + pad + ">";
  return s;
}
string Monop::str(string pad) const {
  return pad + "<MONOP " + opNames[o] + ",\n" + e->str(pad + k_pad_const) + ">";
}
string Binop::str(string pad) const {
  return pad + "<MONOP " + opNames[o] + ",\n" + el->str(pad + k_pad_const) +
         "\n" + er->str(pad + k_pad_const) + ">";
}
string Offset::str(string pad) const {
  return pad + "<OFFSET,\n" + base->str(pad + k_pad_const) + "\n" +
         offset->str(pad + k_pad_const) + ">";
}
string Bound::str(string pad) const {
  return pad + "<BOUND,\n" + arr->str(pad + k_pad_const) + "\n" +
         bound->str(pad + k_pad_const) + ">";
}
string Label::str(string pad) const {
  return pad + "<LABEL " + to_string(lab) + ">";
}
string Jump::str(string pad) const {
  return pad + "<JUMP " + to_string(lab) + ">";
}
string Jumpc::str(string pad) const {
  string s = pad + "<JUMPC " + opNames[lab.first] + k_pad_const +
             to_string(lab.second) + "\n";
  s += ifc->str(pad + k_pad_const);
  s += elsec->str(pad + k_pad_const);
  s += "\n" + pad + ">";
  return s;
}
string Seq::str(string pad) const {
  string s = pad + "<SEQ,\n";
  for (Inst *inst : *insts)
    s += inst->str(pad + k_pad_const) + "\n";
  return s + pad + ">\n";
}
string Line::str(string pad) const {
  return pad + "<LINE " + to_string(line) + ">";
}
string Nop::str(string pad) const { return ""; }

string GlobalDecl::str(string pad) const {
  return pad + "<GLOBAL_DECL " + label + ">";
}

string ProcDecl::str(string pad) const {
  string s = pad + "<PROC_DECL " + label;
  s += ", " + to_string(nparams);
  s += ", " + to_string(argSize);
  s += ", " + to_string(locSize);
  s += ">\n";
  s += code->str(pad + k_pad_const);

  return s;
}

string Program::str(string pad) const {
  string s = "";
  std::cout << "haha" << std::endl;
  for (GlobalDecl *g : *globDecls){
    s += g->str(pad) + "\n";
  }
  for (ProcDecl *p : *procDecls)
    s += p->str(pad) + "\n\n";
  return s;
}

} // namespace Keiko
