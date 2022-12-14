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

#include "types.h"
#include <iostream>

using namespace Pascal;

/*****************
 *    TYPES
 *****************/

Type *Int::clone() { return new Int(); }
string Int::str() const { return "int"; }
bool Int::isArray() { return false; }

Type *Bool::clone() { return new Bool(); }
string Bool::str() const { return "bool"; }
bool Bool::isArray() { return false; }

Type *Void::clone() { return new Void(); }
string Void::str() const { return "void"; }
bool Void::isArray() { return false; }

Array::Array(int _length, Type *_elemType)
    : length(_length), elemType(_elemType) {}
Type *Array::clone() { return new Void(); }
string Array::str() const {
  return elemType->str() + "[" + std::to_string(length) + "]";
}
bool Array::isArray() { return true; }
Array::~Array() {}

Func::Func(vector<Type *> _args, Type *_returnType)
    : args(_args), returnType(_returnType) {}

Type *Func::clone() {
  vector<Type *> nargs = vector<Type *>();
  for (Type *t : args)
    nargs.push_back(t->clone());
  return new Func(nargs, returnType->clone());
}

string Func::str() const {
  string s = "(";
  int n = args.size();
  for (int i = 0; i < n - 1; i++)
    s += args[i]->str() + ", ";
  if (n > 0)
    s += args[n - 1]->str();
  return s + ") -> " + returnType->str();
}

bool Func::isArray() { return false; }
Func::~Func() {}

bool Pascal::equalType(Type *t1, Type *t2) {
  if (typeid(*t1) == typeid(*t2)) {
    if (typeid(*t1) == typeid(Array)) {
      Array *_t1 = (Array *)t1;
      Array *_t2 = (Array *)t2;
      return _t1->length == _t2->length &&
             equalType(_t1->elemType, _t2->elemType);
    }
    if (typeid(*t1) == typeid(Func)) {
      Func *_t1 = (Func *)t1;
      Func *_t2 = (Func *)t2;

      if (_t1->args.size() != _t2->args.size())
        return false;
      if (!equalType(_t1->returnType, _t2->returnType))
        return false;
      for (std::size_t i = 0, max = _t1->args.size(); i < max; i++)
        if (!equalType(_t1->args[i], _t2->args[i]))
          return false;
    }
    return true;
  }
  return false;
}

/** Scalar check **/

bool Int::isScalar() { return true; }
bool Bool::isScalar() { return true; }
bool Array::isScalar() { return false; }
bool Func::isScalar() { return false; }
bool Void::isScalar() { return false; }

/** Size **/

int Int::size() { return 4; }
int Bool::size() { return 1; }
int Void::size() { return 0; }
int Array::size() { return length * elemType->size(); }
// maybe useful when passing function types as arguments
int Func::size() { return 8; }

/** Align **/

int Int::align() { return 4; }
int Bool::align() { return 1; }
int Void::align() { return 1; }
int Array::align() { return length * elemType->size(); }
int Func::align() { return 4; }

PascalType Int::P_type() { return P_int; }
PascalType Bool::P_type() { return P_bool; }
PascalType Void::P_type() { return P_void; }
PascalType Array::P_type() { return P_array; }
PascalType Func::P_type() { return P_func; }
