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

#include "exceptions.h"

using std::domain_error;
using namespace Pascal;

/*********************
 *  semantic_error
 *********************/

semantic_error::semantic_error(char const *const message,
                               location &err_loc) throw()
    : domain_error("(" + std::to_string(err_loc.begin.line) + "." +
                   std::to_string(err_loc.begin.column) + "): " + Colors.Red +
                   message + Colors.White) {}

// TODO might not work
char const *semantic_error::what() const throw() {
  return domain_error::what();
}

internal_error::internal_error(char const *const message) throw()
    : domain_error(Colors.Red + message + Colors.White) {}

// TODO might not work
char const *internal_error::what() const throw() {
  return domain_error::what();
}
