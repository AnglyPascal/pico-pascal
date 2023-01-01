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

#ifndef KEIKO_H
#define KEIKO_H

#include "tree.h"
#include <string>

using std::string;

namespace Keiko {

enum KeikoType {
  K_Nop,
  K_Seq,
  K_Line,
  K_Const,
  K_Global,
  K_Local,
  K_Loadw,
  K_Loadc,
  K_Storew,
  K_Storec,
  K_Resultw,
  K_Arg,
  K_Static,
  K_Call,
  K_Monop,
  K_Binop,
  K_Offset,
  K_Label,
  K_Jump,
  K_Jumpc,
  K_Bound,
  K_GlobalDecl,
  K_ProcDecl,
  K_Program
};

inline void debug(string mssg) {
  if (0)
    Pascal::debug(mssg);
}

typedef string symbol;
typedef Pascal::op op;
typedef std::pair<op, int> fork;

struct Inst {
  Inst();

  virtual ~Inst();
  virtual Inst *simplify() = 0;
  virtual Inst *clone() = 0;
  virtual KeikoType type() = 0;
  virtual void str(string tab) const = 0;
};

struct Seq : public Inst {
  vector<Inst *> *insts;

  Seq(vector<Inst *> *_insts);
  ~Seq();
  KeikoType type();
  Inst *simplify();
  Inst *clone();
  void str(string tab) const;
};

struct Nop : public Inst {
  Nop() = default;
  ~Nop() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Line : public Inst {
  int line;

  Line(int _line);
  ~Line() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Const : public Inst {
  int n;

  Const(int _n);
  ~Const() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Global : public Inst {
  symbol x;

  Global(symbol _x);
  ~Global() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Local : public Inst {
  int offset;

  Local(int _offset);
  ~Local() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Loadc : public Inst {
  Inst *inst;

  Loadc(Inst *_inst);
  ~Loadc();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Loadw : public Inst {
  Inst *inst;

  Loadw(Inst *_inst);
  ~Loadw();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Storec : public Inst {
  Inst *source, *addr;

  Storec(Inst *_source, Inst *_addr);
  ~Storec();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Storew : public Inst {
  Inst *source, *addr;

  Storew(Inst *_source, Inst *_addr);
  ~Storew();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Resultw : public Inst {
  Inst *inst;

  Resultw(Inst *_inst);
  ~Resultw();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Arg : public Inst {
  int ind;
  Inst *arg;

  Arg(int _ind, Inst *_arg);
  ~Arg();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Static : public Inst {
  Inst *link;

  Static(Inst *_link);
  ~Static();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Call : public Inst {
  int nparams;
  Inst *func;
  Static *staticLink;
  Seq *args;

  Call(int _nparams, Inst *_func, Static *staticLink, Seq *args);
  ~Call();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Monop : public Inst {
  op o;
  Inst *e;

  Monop(op _o, Inst *_e);
  ~Monop();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Binop : public Inst {
  op o;
  Inst *el, *er;

  Binop(op _o, Inst *_el, Inst *_er);
  ~Binop();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Offset : public Inst {
  Inst *base, *offset;

  Offset(Inst *_base, Inst *_offset);
  ~Offset();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Bound : public Inst {
  Inst *arr, *bound;

  Bound(Inst *_arr, Inst *_bound);
  ~Bound();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Label : public Inst {
  int lab;

  Label(int _lab);
  ~Label() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Jump : public Inst {
  int lab;

  Jump(int _lab);
  ~Jump() = default;
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Jumpc : public Inst {
  fork lab;
  Inst *ifc, *elsec;

  Jumpc(fork _lab, Inst *_ifc, Inst *_elsec);
  ~Jumpc();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct GlobalDecl : public Inst {
  string label;

  GlobalDecl(string _label);
  ~GlobalDecl();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct ProcDecl : public Inst {
  string label;
  int level, nparams, argSize, locSize;
  Inst *code;

  ProcDecl(string _label, int _level, int _nparams, int _argSize, int _locSize,
           Inst *_code);
  ~ProcDecl();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

struct Program : public Inst {
  vector<GlobalDecl *> *globDecls;
  vector<ProcDecl *> *procDecls;

  Program(vector<GlobalDecl *> *_globDecls, vector<ProcDecl *> *_procDecls);
  ~Program();
  Inst *simplify();
  Inst *clone();
  KeikoType type();
  void str(string tab) const;
};

} // namespace Keiko

#endif
