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
	using namespace Pascal;

	// Original yyterminate() macro returns int. Since we're using Bison 3 variants
	// as tokens, we must redefine it to change type from `int` to `Parser::semantic_type`
	#define yyterminate() Parser::make_EOF(location());

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

	void scannerTrace(string mssg) { cout << "Scanner: " + mssg << endl; }
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Pascal_"

%%

"true"    { scannerTrace("true"); return Parser::make_BOOLCONST(1, location()); }
"false"   { scannerTrace("false"); return Parser::make_BOOLCONST(0, location()); }

"and"     { scannerTrace("and"); return Parser::make_ADDOP(op::Plus, location()); }
"or"      { scannerTrace("or"); return Parser::make_ADDOP(op::Or, location()); }
"div"     { scannerTrace("div"); return Parser::make_MULOP(op::Div, location()); }
"mod"     { scannerTrace("mod"); return Parser::make_MULOP(op::Mod, location()); }
"not"     { scannerTrace("not"); return Parser::make_MONOP(op::Not, location()); }

"begin"   { scannerTrace("begin"); return Parser::make_BEGINT(location()); }
"end"     { scannerTrace("end"); return Parser::make_END(location()); }

"var"     { scannerTrace("var"); return Parser::make_VAR(location()); }
"array"   { scannerTrace("array"); return Parser::make_ARRAY(location()); }
"of"      { scannerTrace("of"); return Parser::make_OF(location()); }
"integer" { scannerTrace("integer type"); return Parser::make_INTEGER(location()); }
"boolean" { scannerTrace("boolean type"); return Parser::make_BOOLEAN(location()); }

"if"      { scannerTrace("if"); return Parser::make_IF(location()); }
"then"    { scannerTrace("then"); return Parser::make_THEN(location()); }
"else"    { scannerTrace("else"); return Parser::make_ELSE(location()); }
"while"   { scannerTrace("while"); return Parser::make_WHILE(location()); }
"do"      { scannerTrace("do"); return Parser::make_DO(location()); }

"proc"    { scannerTrace("do"); return Parser::make_PROC(location()); }
"print"   { scannerTrace("print"); return Parser::make_PRINT(location()); }
"return"  { scannerTrace("return"); return Parser::make_RETURN(location()); }
"newline" { scannerTrace("newline"); return Parser::make_NEWLINE(location()); }

[A-Za-z][A-Za-z0-9_]* { 
	std::string str = yytext;
	scannerTrace("ident \"" + str + "\"");
	return Parser::make_IDENT(str, location());
}

[0-9]+	{ 
	int number = strtoull(yytext, 0, 10);
	cout << "Scanner: number " << number << endl;
	return Parser::make_NUMBER(number, location()); 
}

"+"  { scannerTrace("+"); return Parser::make_ADDOP(op::Plus, location()); }
"-"  { scannerTrace("-"); return Parser::make_MINUS(location()); }
"*"  { scannerTrace("*"); return Parser::make_MULOP(op::Times, location()); }

"<"  { scannerTrace("<"); return Parser::make_RELOP(op::Lt, location()); }
">"  { scannerTrace(">"); return Parser::make_RELOP(op::Gt, location()); }
"="  { scannerTrace("="); return Parser::make_RELOP(op::Eq, location()); }
"<>" { scannerTrace("<>"); return Parser::make_RELOP(op::Neq, location()); }
"<=" { scannerTrace("<="); return Parser::make_RELOP(op::Leq, location()); }
">=" { scannerTrace(">="); return Parser::make_RELOP(op::Geq, location()); }

\(   { scannerTrace("("); return Parser::make_LPAR(location()); }
\)   { scannerTrace(")"); return Parser::make_RPAR(location()); }
"["  { scannerTrace("["); return Parser::make_SUB(location()); }
"]"  { scannerTrace("]"); return Parser::make_BUS(location()); }

,    { scannerTrace(","); return Parser::make_COMMA(location()); }
;    { scannerTrace(";"); return Parser::make_SEMI(location()); }
\.   { scannerTrace("."); return Parser::make_DOT(location()); }
:=   { scannerTrace(":="); return Parser::make_ASSIGN(location()); }

[ \t]+  { /* yylloc->step(); */ }
"\r"    { /* yylloc->step(); */ }
"\n"    { /* return Parser::make_EOL(location()); */ }

_       { 
	scannerTrace("unknown character [" + string(yytext) + "]");
	return Parser::make_BADTOK(location()); 
}

<<EOF>> { scannerTrace("EOF"); return yyterminate(); }

%%
