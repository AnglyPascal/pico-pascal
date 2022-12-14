/*
 * The MIT License (MIT)
 * 
 * Copyright (c) 2014 Krzysztof Narkiewicz <krzysztof.narkiewicz@ezaquarii.com>
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

%{
	#include <iostream>
	#include <cstdlib>
	#include "scanner.h"
	#include "driver.h"
	#include "parser.h"
	#include "location.hh"

	using namespace std;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() Pascal::Parser::make_EOF(Pascal::location());

	// This will track current scanner location.
	// Action is called when length of the token is known.
	#define YY_USER_ACTION m_driver.increaseLocation(yyleng);
	
	// !!!WARNING!!!
	// Location API is used, but the location is not initialized, 'cause I'm lazy. When making
	// a token with make_{something} method you can pass detailed token location. Current location
	// is accessible with m_driver.location() method. All puzzle elements are there - just
	// pass location value in every action code block below. I'm going to waste more time writing
	// this excuse than putting this boilerplate below...
	//
	// Location class can be found in location.hh and posistion.hh files. It's just a bit too much
	// boilerplate for this small example. Bummer.
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Pascal_"

%%

"true"    { 
	cout << "Scanner: true" << endl;
	return Pascal::Parser::make_NUMBER(1, Pascal::location()); 
}

"false"   { 
	cout << "Scanner: false" << endl;
	return Pascal::Parser::make_NUMBER(0, Pascal::location()); 
}

"and"     { 
	cout << "Scanner: and" << endl;
	return Pascal::Parser::make_ADDOP(Pascal::op::Plus, Pascal::location()); 
}

"or"      { 
	cout << "Scanner: or" << endl;
	return Pascal::Parser::make_ADDOP(Pascal::op::Or, Pascal::location()); 
}

"div"     { 
	cout << "Scanner: div" << endl;
	return Pascal::Parser::make_MULOP(Pascal::op::Div, Pascal::location()); 
}

"mod"     { 
	cout << "Scanner: mod" << endl;
	return Pascal::Parser::make_MULOP(Pascal::op::Mod, Pascal::location()); 
}

"not"     { 
	cout << "Scanner: not" << endl;
	return Pascal::Parser::make_MONOP(Pascal::op::Not, Pascal::location()); 
}

"begin"   { 
	cout << "Scanner: begin" << endl;
	return Pascal::Parser::make_PROC_BEGIN(Pascal::location());
}

"end"     { 
	cout << "Scanner: end" << endl;
	return Pascal::Parser::make_PROC_END(Pascal::location());
}

"var"     { 
	cout << "Scanner: end" << endl;
	return Pascal::Parser::make_VAR(Pascal::location());
}

"print"   { 
	cout << "Scanner: print" << endl;
	return Pascal::Parser::make_PRINT(Pascal::location());
}

"if"      { 
	cout << "Scanner: if" << endl;
	return Pascal::Parser::make_IF(Pascal::location());
}

"then"    { 
	cout << "Scanner: then" << endl;
	return Pascal::Parser::make_THEN(Pascal::location());
}

"else"    { 
	cout << "Scanner: else" << endl;
	return Pascal::Parser::make_ELSE(Pascal::location());
}

"while"   { 
	cout << "Scanner: while" << endl;
	return Pascal::Parser::make_WHILE(Pascal::location());
}

"do"      { 
	cout << "Scanner: do" << endl;
	return Pascal::Parser::make_DO(Pascal::location());
}

"proc"    { 
	cout << "Scanner: do" << endl;
	return Pascal::Parser::make_PROC(Pascal::location());
}

"return"  { 
	cout << "Scanner: return" << endl;
	return Pascal::Parser::make_RETURN(Pascal::location());
}

"newline" { 
	cout << "Scanner: newline" << endl;
	return Pascal::Parser::make_NEWLINE(Pascal::location());
}


[A-Za-z][A-Za-z0-9_]* { 
	std::string str = yytext;
	cout << "Scanner: ident \"" << str << "\"" << endl;
	return Pascal::Parser::make_IDENT(str, Pascal::location());
}

[0-9]+	{ 
	int number = strtoull(yytext, 0, 10);
	cout << "Scanner: number " << number << endl;
	return Pascal::Parser::make_NUMBER(number, Pascal::location()); 
}

"="  { 
	cout << "Scanner: =" << endl;
	return Pascal::Parser::make_RELOP(Pascal::op::Eq, Pascal::location());
}

"+"  { 
	cout << "Scanner: +" << endl;
	return Pascal::Parser::make_ADDOP(Pascal::op::Plus, Pascal::location());
}

"-"  { 
	cout << "Scanner: -" << endl;
	return Pascal::Parser::make_MINUS(Pascal::location());
}

"*"  { 
	cout << "Scanner: *" << endl;
	return Pascal::Parser::make_MULOP(Pascal::op::Times, Pascal::location());
}

"<"  { 
	cout << "Scanner: <" << endl;
	return Pascal::Parser::make_RELOP(Pascal::op::Lt, Pascal::location());
}

">"  { 
	cout << "Scanner: >" << endl;
	return Pascal::Parser::make_RELOP(Pascal::op::Gt, Pascal::location());
}

"<>" { 
	cout << "Scanner: <>" << endl;
	return Pascal::Parser::make_RELOP(Pascal::op::Neq, Pascal::location());
}

"<=" { 
	cout << "Scanner: <=" << endl;
	return Pascal::Parser::make_RELOP(Pascal::op::Leq, Pascal::location());
}

">=" { 
	cout << "Scanner: >=" << endl;
	return Pascal::Parser::make_RELOP(Pascal::op::Geq, Pascal::location());
}


\(   { 
	cout << "Scanner: (" << endl;
	return Pascal::Parser::make_LPAR(Pascal::location());
}

\)   { 
	cout << "Scanner: )" << endl;
	return Pascal::Parser::make_RPAR(Pascal::location());
}

,    { 
	cout << "Scanner: ," << endl;
	return Pascal::Parser::make_COMMA(Pascal::location());
}

;    { 
	cout << "Scanner: ;" << endl;
	return Pascal::Parser::make_SEMI(Pascal::location());
}

\.   { 
	cout << "Scanner: ." << endl;
	return Pascal::Parser::make_DOT(Pascal::location());
}

:=   { 
	cout << "Scanner: :=" << endl;
	return Pascal::Parser::make_ASSIGN(Pascal::location());
}


[ \t]+  { /* yylloc->step(); */ }
"\r"    { /* yylloc->step(); */ }
"\n"    { 
	/* return Pascal::Parser::make_EOL(Pascal::location()); */ 
}

_       { 
	cout << "Scanner: unknown character [" << yytext << "]" << endl;
	return Pascal::Parser::make_BADTOK(Pascal::location()); 
}

<<EOF>> { 
	cout << "Scanner: EOF" << endl;
	return yyterminate(); 
}

%%
