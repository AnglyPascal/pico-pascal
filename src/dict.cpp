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
 *    DEFKIND
 *****************/

DefKind::~DefKind() {}

VarDef::~VarDef() {}
DefKind *VarDef::clone() { return new VarDef(*this); }

ProcDef::~ProcDef() {}
DefKind *ProcDef::clone() { return new ProcDef(_nparams); }

ProcDef &ProcDef::operator=(const ProcDef &other) {
  if (&other != this) {
    _nparams = other._nparams;
  }
  return *this;
}

/*****************
 *     DEFN
 *****************/

Defn::Defn() = default;

Defn::Defn(ident _tag, DefKind *_kind, int _level, string _label, int _off,
           Type *_type)
    : d_tag(_tag), d_level(_level), d_label(_label), d_offset(_off),
      d_type(_type) {
  d_kind = _kind;
}

Defn::~Defn() { delete d_kind; }
Defn *Defn::clone() {
  return new Defn(d_tag, d_kind->clone(), d_level, d_label, d_offset, d_type);
}

Defn &Defn::operator=(const Defn *other) {
  delete d_kind;

  d_tag = other->d_tag;
  d_kind = other->d_kind;
  d_level = other->d_level;
  d_label = other->d_label;
  d_offset = other->d_offset;

  return *this;
}

Defn *Defn::clone() const {
  return new Defn(d_tag, d_kind->clone(), d_level, d_label, d_offset,
                  d_type->clone());
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
