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

	void scannerTrace(string mssg) { 
		/* cout << "Scanner: " + mssg << endl; */ 
	}
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="Pascal_"

%%

"true"    { scannerTrace("true"); return Parser::make_BOOLCONST(1, yylloc()); }
"false"   { scannerTrace("false"); return Parser::make_BOOLCONST(0, yylloc()); }

"and"     { scannerTrace("and"); return Parser::make_ADDOP(op::Plus, yylloc()); }
"or"      { scannerTrace("or"); return Parser::make_ADDOP(op::Or, yylloc()); }
"div"     { scannerTrace("div"); return Parser::make_MULOP(op::Div, yylloc()); }
"mod"     { scannerTrace("mod"); return Parser::make_MULOP(op::Mod, yylloc()); }
"not"     { scannerTrace("not"); return Parser::make_MONOP(op::Not, yylloc()); }

"begin"   { scannerTrace("begin"); return Parser::make_BEGINT(yylloc()); }
"end"     { scannerTrace("end"); return Parser::make_END(yylloc()); }

"var"     { scannerTrace("var"); return Parser::make_VAR(yylloc()); }
"array"   { scannerTrace("array"); return Parser::make_ARRAY(yylloc()); }
"of"      { scannerTrace("of"); return Parser::make_OF(yylloc()); }
"integer" { scannerTrace("integer type"); return Parser::make_INTEGER(yylloc()); }
"boolean" { scannerTrace("boolean type"); return Parser::make_BOOLEAN(yylloc()); }

"if"      { scannerTrace("if"); return Parser::make_IF(yylloc()); }
"then"    { scannerTrace("then"); return Parser::make_THEN(yylloc()); }
"else"    { scannerTrace("else"); return Parser::make_ELSE(yylloc()); }
"while"   { scannerTrace("while"); return Parser::make_WHILE(yylloc()); }
"do"      { scannerTrace("do"); return Parser::make_DO(yylloc()); }

"proc"    { scannerTrace("do"); return Parser::make_PROC(yylloc()); }
"print"   { scannerTrace("print"); return Parser::make_PRINT(yylloc()); }
"return"  { scannerTrace("return"); return Parser::make_RETURN(yylloc()); }
"newline" { scannerTrace("newline"); return Parser::make_NEWLINE(yylloc()); }

[A-Za-z][A-Za-z0-9_]* { 
	std::string str = yytext;
	scannerTrace("ident \"" + str + "\"");
	return Parser::make_IDENT(str, yylloc());
}

[0-9]+	{ 
	int number = strtoull(yytext, 0, 10);
	scannerTrace("number " + std::to_string(number));
	return Parser::make_NUMBER(number, yylloc()); 
}

"+"  { scannerTrace("+"); return Parser::make_ADDOP(op::Plus, yylloc()); }
"-"  { scannerTrace("-"); return Parser::make_MINUS(yylloc()); }
"*"  { scannerTrace("*"); return Parser::make_MULOP(op::Times, yylloc()); }

"<"  { scannerTrace("<"); return Parser::make_RELOP(op::Lt, yylloc()); }
">"  { scannerTrace(">"); return Parser::make_RELOP(op::Gt, yylloc()); }
"="  { scannerTrace("="); return Parser::make_RELOP(op::Eq, yylloc()); }
"<>" { scannerTrace("<>"); return Parser::make_RELOP(op::Neq, yylloc()); }
"<=" { scannerTrace("<="); return Parser::make_RELOP(op::Leq, yylloc()); }
">=" { scannerTrace(">="); return Parser::make_RELOP(op::Geq, yylloc()); }

\(   { scannerTrace("("); return Parser::make_LPAR(yylloc()); }
\)   { scannerTrace(")"); return Parser::make_RPAR(yylloc()); }
"["  { scannerTrace("["); return Parser::make_SUB(yylloc()); }
"]"  { scannerTrace("]"); return Parser::make_BUS(yylloc()); }

,    { scannerTrace(","); return Parser::make_COMMA(yylloc()); }
:    { scannerTrace(":"); return Parser::make_COLON(yylloc()); }
;    { scannerTrace(";"); return Parser::make_SEMI(yylloc()); }
\.   { scannerTrace("."); return Parser::make_DOT(yylloc()); }
:=   { scannerTrace(":="); return Parser::make_ASSIGN(yylloc()); }

[ \t]+  { /* IGNORE WHITESPACE */ }
"\r"    { /* IGNORE WHITESPACE */ }
"\n"    { m_driver.line(); }

[\(][*][^*]*[*]+([^*\)][^*]*[*]+)*[\)]    { /* DO NOTHING */ }
[\(][*]                                   { /* unfinished comment error */ }

_       { 
	scannerTrace("unknown character [" + string(yytext) + "]");
	return Parser::make_BADTOK(yylloc()); 
}

<<EOF>> { scannerTrace("EOF"); return yyterminate(); }

%%

location Scanner::yylloc() {
	return m_driver.yylloc();
}
