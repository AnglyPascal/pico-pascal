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
#include <typeinfo>

using namespace Pascal;

/*****************
 *    TYPES
 *****************/

Type *Int::clone() { return new Int(); }
string Int::str() const { return "int"; }
int Int::size() { return 4; }
bool Int::isArray() { return false; }

Type *Bool::clone() { return new Bool(); }
string Bool::str() const { return "bool"; }
int Bool::size() { return 1; }
bool Bool::isArray() { return false; }

Type *Void::clone() { return new Void(); }
string Void::str() const { return "void"; }
int Void::size() { return 0; }
bool Void::isArray() { return false; }

Array::Array(int _length, Type *_elemType)
    : length(_length), elemType(_elemType) {}
Type *Array::clone() { return new Void(); }
string Array::str() const {
  return "[" + elemType->str() + "](" + std::to_string(length) + ")";
}
int Array::size() { return length * elemType->size(); }
bool Array::isArray() { return true; }
Array::~Array() { delete elemType; }

bool equalType(Type *t1, Type *t2) {
  if (typeid(*t1) == typeid(*t2)) {
    if (typeid(*t1) == typeid(Array)) {
      Array *_t1 = (Array *)t1;
      Array *_t2 = (Array *)t2;
      return _t1->length == _t2->length &&
             equalType(_t1->elemType, _t2->elemType);
    }
    return true;
  }
  return false;
}
