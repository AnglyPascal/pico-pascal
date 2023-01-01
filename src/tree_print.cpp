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

#include "print.h"
#include "tree.h"

#include <iostream>
#include <vector>

namespace Pascal {

string pad_const = "  ";
bool print_infos = true;

// ------- opName ----------
map<op, string> opNames = {
    {Plus, "+"},  {Minus, "-"},  {Times, "*"}, {Div, "/"},    {Mod, "%"},
    {Eq, "=="},   {Uminus, "-"}, {Lt, "<"},    {Gt, ">"},     {Leq, "<="},
    {Geq, ">="},  {Neq, "!="},   {And, "&&"},  {Or, "||"},    {Not, "!"},
    {Lsl, "<<"},  {Lsr, ">>"},   {Asr, "asr"}, {BitAnd, "&"}, {BitOr, "|"},
    {BitNot, "~"}};

/************************
 **  Printing the AST  **
 *************************/

string Name::str() const {
  if (x_def) {
    string s = x_name;
    string info = Colors.Black + "{" + std::to_string(x_def->d_level) + ",";
    if (x_def->d_addr)
      info += x_def->d_addr->str() + "}" + Colors.White;
    else
      info += Colors.Red + "_" + Colors.Black + "}" + Colors.White;
    if (print_infos)
      return s + info;
    else 
      return s;
  }
  else return Colors.Black + "_" + Colors.White;
}

string Expr::str() const { return "Expr"; }
string Constant::str() const { return std::to_string(n); }
string Variable::str() const { return x->str(); }

bool simple(Expr *e) {
  switch (e->exprType){
    case constant:
    case sub:
    case call:
    case variable:
      return true;
    default:
      return false;
  }
}

string Monop::str() const { 
  if (simple(e))
    return opNames[o] + e->str(); 
  else 
    return opNames[o] + "(" + e->str() + ")"; 
}

string Binop::str() const {
  string s1, s2;
  if (simple(el))
    s1 = el->str(); 
  else 
    s1 = "(" + el->str() + ")";
  if (simple(el))
    s2 = er->str(); 
  else 
    s2 = "(" + er->str() + ")";

  return s1 + " " + opNames[o] + " " + s2;
}

string Call::str() const {
  string a = "";
  int n = args->size();
  for (int i = 0; i < n - 1; i++)
    a += (*args)[i]->str() + ", ";
  a += (*args)[n - 1]->str();
  return f->str() + "(" + a + ")";
}

string IfExpr::str() const {
  return "if (" + cond->str() + ") " + ifc->str() + " else " + elsec->str();
}

string Sub::str() const { return arr->str() + "[" + ind->str() + "]"; }

string VarDecl::str() const {
  string s = "var ";
  int n = names->size();
  for (int i = 0; i < n - 1; i++)
    s += (*names)[i]->str() + ", ";
  s += (*names)[n - 1]->str();
  s += ": " + type->str();
  return s;
}

string ProcDecl::str() const {
  string s = "proc " + f->str() + "(";
  int n = args->size();
  for (int i = 0; i < n - 1; i++)
    s += (*args)[i]->str() + ", ";
  s += (*args)[n - 1]->str();
  s += "): " + type->returnType->str();
  return s;
}

string Program::str() const {
  string str = "**Program**\n\n" + prog->str("") + "\n**eof**";
  return str;
}

string Block::str(string pad) const {
  for (int i = 0; i < level; i++)
    pad += pad_const;

  string str = "";
  for (Decl *d : *decls)
    str += pad + d->str() + "\n";
  str += "\n";

  for (Proc *p : *procs)
    str += p->str(pad);

  str += pad + "begin\n";
  str += st->str(pad + pad_const);
  str += pad + "end\n";
  return str;
}

string Proc::str(string pad) const {
  string str = pad + fun->str() + "\n";
  str += blk->str(pad) + "\n";
  return str;
}

string Stmt::str(string pad) const { return pad; }
string Skip::str(string pad) const { return ""; }
string Newline::str(string pad) const { return pad + "newline\n"; }

string Seq::str(string pad) const {
  string str = "";
  for (Stmt *st : *stmts)
    str += st->str(pad);
  return str;
}

string Assign::str(string pad) const {
  return pad + x->str() + " := " + e->str() + "\n";
}
string Return::str(string pad) const {
  return pad + "return " + e->str() + "\n";
}

string IfStmt::str(string pad) const {
  string _pad = pad + pad_const;
  string str =
      pad + "if (" + cond->str() + ") {\n" + ifStmt->str(_pad) + pad + "}";
  str += " else {\n" + elseStmt->str(_pad) + pad + "}\n";
  return str;
}

string WhileStmt::str(string pad) const {
  string str = pad + "while (" + cond->str() + ") {\n" +
               st->str(pad + pad_const) + pad + "}\n";
  return str;
}

string Print::str(string pad) const {
  return pad + "print (" + e->str() + ")\n";
}

} // namespace Pascal
