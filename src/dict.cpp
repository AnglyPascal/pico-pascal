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

#include "dict.h"

using namespace Pascal;

/*****************
 *    LOCATION
 *****************/

Local::Local(int _offset) : offset(_offset) {}
Local::~Local() {}
Location *Local::clone() const { return new Local(offset); }
string Local::str() const { return std::to_string(offset); }

Global::Global(string _label) : label(_label) {}
Global::~Global() {}
Location *Global::clone() const { return new Global(label); }
string Global::str() const { return label; }

/*****************
 *    DEFKIND
 *****************/

DefKind::~DefKind() {}
bool DefKind::isVariable() const { return false; }
bool DefKind::isProc() const { return false; }
bool DefKind::isProcParam() const { return false; }
string DefKind::str() const { return "_"; }

VarDef::VarDef() {}
VarDef::~VarDef() {}
DefKind *VarDef::clone() const { return new VarDef(); }
bool VarDef::isVariable() const { return true; }
string VarDef::str() const { return "vardef"; }

ProcDef::ProcDef() : _nparams(0), _args(new vector<Defn *>()){};
ProcDef::~ProcDef() {
  for (Defn *d : *_args)
    delete d;
  delete _args;
}
DefKind *ProcDef::clone() const {
  ProcDef *np = new ProcDef();
  np->_nparams = _nparams;
  for (Defn *d : *_args)
    np->_args->push_back(d->clone());
  return np;
}
string ProcDef::str() const { return "procdef"; }
bool ProcDef::isProc() const { return true; }
void ProcDef::addArgs(vector<Defn *> defs) {
  _nparams = 0;
  for (Defn *d : defs) {
    _args->push_back(d->clone());
    _nparams += d->nparams();
    _argSize += d->d_type->size();
  }
}

ProcDef &ProcDef::operator=(const ProcDef &other) {
  if (&other != this)
    _nparams = other._nparams;
  _args->clear();
  for (Defn *d : *other._args)
    _args->push_back(d->clone());
  return *this;
}

PProcDef::PProcDef() : _nparams(0), _args(new vector<Defn *>()){};
PProcDef::~PProcDef() {
  for (Defn *d : *_args)
    delete d;
  delete _args;
}
DefKind *PProcDef::clone() const {
  PProcDef *np = new PProcDef();
  np->_nparams = _nparams;
  for (Defn *d : *_args)
    np->_args->push_back(d->clone());
  return np;
}
string PProcDef::str() const { return "procparamdef"; }
bool PProcDef::isProcParam() const { return true; }
void PProcDef::addArgs(vector<Defn *> defs) {
  _nparams = 0;
  for (Defn *d : defs) {
    _args->push_back(d->clone());
    _nparams += d->nparams();
    _argSize += d->d_type->size();
  }
}

PProcDef &PProcDef::operator=(const PProcDef &other) {
  if (&other != this)
    _nparams = other._nparams;
  _args->clear();
  for (Defn *d : *other._args)
    _args->push_back(d->clone());
  return *this;
}

/*****************
 *     DEFN
 *****************/

Defn::Defn() = default;

Defn::Defn(ident _tag, DefKind *_kind, int _level, Type *_type)
    : d_tag(_tag), d_kind(_kind), d_level(_level), d_type(_type) {
  d_addr = nullptr;
}

Defn::~Defn() { delete d_kind; }

Defn *Defn::clone() const {
  Defn *nd = new Defn(d_tag, d_kind->clone(), d_level, d_type);
  if (d_addr)
    nd->d_addr = d_addr->clone();
  return nd;
}

int Defn::nparams() const {
  if (typeid(*d_kind) == typeid(VarDef))
    return 1;
  else
    return 2;
}

Defn &Defn::operator=(const Defn *other) {
  delete d_kind;

  d_tag = other->d_tag;
  d_kind = other->d_kind;
  d_level = other->d_level;
  if (other->d_addr)
    d_addr = other->d_addr->clone();
  else
    d_addr = nullptr;

  return *this;
}

void Defn::addArgs(vector<Defn *> defs) {
  if (typeid(*d_kind) == typeid(ProcDef))
    ((ProcDef *)d_kind)->addArgs(defs);
  else if (typeid(*d_kind) == typeid(PProcDef))
    ((PProcDef *)d_kind)->addArgs(defs);
  else
    throw std::domain_error("adding arguments to a vardef?");
}

string Defn::str() const {
  return Colors.Green + d_kind->str() + " " + d_tag + Colors.White + " at " +
         d_addr->str();
}

/*****************
 *     Env
 *****************/

void Env::define(Defn *d) {
  if (env.count(d->d_tag))
    throw std::domain_error("variable " + d->d_tag + " is already declared");
  env[d->d_tag] = d;
}

Defn *Env::lookup(string tag) {
  if (!env.count(tag))
    throw std::domain_error("variable " + tag + " is not declared");
  return env[tag];
}

Env::Env() : env(map<string, Defn *>()) {}

Env::Env(Env *e) : env(map<string, Defn *>()) {
  for (const auto &[key, value] : e->env)
    env[key] = value;
}

Env::~Env() {}
