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

#ifndef TYPES_H
#define TYPES_H

#include <string>
using std::string;

namespace Pascal {

/*****************
 *    TYPES
 *****************/

struct Type {
  Type() = default;
  virtual ~Type() = 0;
  virtual Type *clone() = 0;
  virtual string str() const = 0;

  virtual int size() = 0;
  virtual bool isArray() = 0;
};

struct Int : public Type {
  Int() = default;
  ~Int() = default;

  Type *clone();
  string str() const;

  int size();
  bool isArray();
};

struct Void : public Type {
  Void() = default;
  ~Void() = default;

  Type *clone();
  string str() const;

  int size();
  bool isArray();
};

struct Array : public Type {
  int length;
  Type *elemType;

  Array(int _length, Type *_elemType);
  ~Array();

  Type *clone();
  string str() const;

  int size();
  bool isArray();
};

struct Bool : public Type {
  Bool() = default;
  ~Bool() = default;

  Type *clone();
  string str() const;

  int size();
  bool isArray();
};

bool equals(Type *t1, Type *t2);

} // namespace Pascal

#endif
