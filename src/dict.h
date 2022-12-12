#ifndef dict
#define dict

#include <map>
#include <stdio.h>
#include <string>

using std::map;
using std::string;

typedef string ident;
typedef int codelab;

namespace Pascal {

struct DefKind {
  virtual ~DefKind();
  virtual DefKind *clone() = 0;
};

struct VarDef : public DefKind {
  virtual ~VarDef();
  virtual DefKind *clone();
};

struct ProcDef : public DefKind {
  int _nparams;
  ProcDef(int n) : _nparams(n){};

  virtual ~ProcDef();
  virtual DefKind *clone();
  ProcDef &operator=(const ProcDef &other);
};

struct Defn {
  ident d_tag;
  DefKind *d_kind = nullptr;
  int d_level;
  string d_label;
  int d_offset;

  Defn();
  Defn(ident _tag, DefKind *_kind, int _level, string _label, int _off);

  virtual ~Defn();
  virtual Defn *clone();
  Defn &operator=(const Defn *other);
};

struct {
  int *lab = 0;
  void incr() { lab++; }
} Label;

class {
  map<string, Defn> env;

public:
  void define(Defn *d) {
    if (env.count(d->d_tag)) {
      /* throw an error */
    } else
      env[d->d_tag] = d;
  }

  Defn &lookup(string tag) {
    if (!env.count(tag)) {
      /* throw an error */
    }
    return env[tag];
  }
} Env;

} // namespace Pascal

#endif
