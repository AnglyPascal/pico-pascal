#ifndef dict
#define dict

#include <iostream>
#include <map>

using namespace std;

typedef string ident;
typedef int codelab;

struct {
  int *lab = 0;

public:
  void incr() { lab++; }

} label;

struct def_kind {
  virtual ~def_kind();
};

struct VarDef : public def_kind {};

struct ProcDef : public def_kind {
  const int _nparams;
  ProcDef(int n) : _nparams(n){};
};

struct def {
  ident d_tag;
  def_kind *d_kind = nullptr;
  int d_level;
  string d_label;
  int d_offset;

  def() = default;

  def(ident _tag, def_kind *_kind, int _level, string _label, int _off)
      : d_tag(_tag), d_level(_level), d_label(_label), d_offset(_off) {
    d_kind = _kind;
  }

  def &operator=(def *other) {
    swap(d_tag, other->d_tag);
    swap(d_kind, other->d_kind);
    swap(d_level, other->d_level);
    swap(d_label, other->d_label);
    swap(d_offset, other->d_offset);

    return *this;
  }
};

struct {
private:
  map<string, def> env;

public:
  void define(def *d) {
    if (env.count(d->d_tag)) {
      /* throw an error */
    } else
      env[d->d_tag] = d;
  }

  def &lookup(string tag) {
    if (!env.count(tag)) {
      /* throw an error */
    }
    return env[tag];
  }
} environment;

#endif
