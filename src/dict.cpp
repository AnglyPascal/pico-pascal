#include "dict.h"

using namespace Pascal;

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

Defn::Defn() = default;

Defn::Defn(ident _tag, DefKind *_kind, int _level, string _label, int _off)
    : d_tag(_tag), d_level(_level), d_label(_label), d_offset(_off) {
  d_kind = _kind;
}

Defn::~Defn() { delete d_kind; }
Defn *Defn::clone() {
  return new Defn(d_tag, d_kind->clone(), d_level, d_label, d_offset);
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
