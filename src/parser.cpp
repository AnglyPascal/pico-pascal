// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.h"


// Unqualified %code blocks.
#line 32 "parser.y"

   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <vector>
   #include <string>
   
   /* include for all driver functions */
   #include "driver.h"

   #undef yylex
   #define yylex scanner.yylex

#line 60 "parser.cpp"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "parser.y"
namespace Pascal {
#line 153 "parser.cpp"

  /// Build a parser object.
  Parser::Parser (Scanner  &scanner_yyarg, Driver  &driver_yyarg, Program *pgm_yyarg, string *errmsg_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg),
      pgm (pgm_yyarg),
      errmsg (errmsg_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
    , location (that.location)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_MOVE_REF (location_type) l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (value_type) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}


  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
    location = YY_MOVE (s.location);
  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value), YY_MOVE (that.location))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value), YY_MOVE (that.location))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YY_USE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: block DOT
#line 96 "parser.y"
                                        { (yylhs.value.progval) = new Program((yystack_[1].value.blockval)); pgm = (yylhs.value.progval); }
#line 629 "parser.cpp"
    break;

  case 3: // block: var_decl proc_decls PROC_BEGIN stmts PROC_END
#line 100 "parser.y"
                                                  { (yylhs.value.blockval) = new Block((yystack_[4].value.ident_list), (yystack_[3].value.proc_list), (yystack_[1].value.stmtptr)); }
#line 635 "parser.cpp"
    break;

  case 4: // var_decl: %empty
#line 104 "parser.y"
                                        { (yylhs.value.ident_list) = new vector<ident>(); }
#line 641 "parser.cpp"
    break;

  case 5: // var_decl: VAR ident_list SEMI
#line 105 "parser.y"
                                        { (yylhs.value.ident_list) = (yystack_[1].value.ident_list); }
#line 647 "parser.cpp"
    break;

  case 6: // ident_list: IDENT
#line 109 "parser.y"
                                        { vector<ident> *ids = new vector<ident>(); 
                                          ids->push_back(*(yystack_[0].value.strval)); (yylhs.value.ident_list) = ids; }
#line 654 "parser.cpp"
    break;

  case 7: // ident_list: ident_list COMMA IDENT
#line 111 "parser.y"
                                        { (yystack_[2].value.ident_list)->push_back(*(yystack_[0].value.strval)); (yylhs.value.ident_list) = (yystack_[2].value.ident_list); }
#line 660 "parser.cpp"
    break;

  case 8: // proc_decls: %empty
#line 115 "parser.y"
                                        { (yylhs.value.proc_list) = new vector<Proc *>(); }
#line 666 "parser.cpp"
    break;

  case 9: // proc_decls: proc_decls proc_decl
#line 116 "parser.y"
                                        { (yystack_[1].value.proc_list)->push_back((yystack_[0].value.procval)); (yylhs.value.proc_list) = (yystack_[1].value.proc_list); }
#line 672 "parser.cpp"
    break;

  case 10: // proc_decl: PROC name formals SEMI block SEMI
#line 120 "parser.y"
                                        { new Proc((yystack_[4].value.nameval), (yystack_[3].value.ident_list), (yystack_[1].value.blockval)); }
#line 678 "parser.cpp"
    break;

  case 11: // formals: LPAR RPAR
#line 124 "parser.y"
                                        { (yylhs.value.ident_list) = new vector<ident>(); }
#line 684 "parser.cpp"
    break;

  case 12: // formals: LPAR ident_list RPAR
#line 125 "parser.y"
                                        { (yylhs.value.ident_list) = (yystack_[1].value.ident_list); }
#line 690 "parser.cpp"
    break;

  case 13: // stmts: stmt_list
#line 129 "parser.y"
                                        { (yylhs.value.stmtptr) = Pascal::sequence((yystack_[0].value.stmt_list)); }
#line 696 "parser.cpp"
    break;

  case 14: // stmt_list: stmt
#line 133 "parser.y"
                                        { vector<Stmt *> *sts = new vector<Stmt *>(); 
                                          sts->push_back((yystack_[0].value.stmtptr)); (yylhs.value.stmt_list) = sts; }
#line 703 "parser.cpp"
    break;

  case 15: // stmt_list: stmt_list SEMI stmt
#line 135 "parser.y"
                                        { (yystack_[2].value.stmt_list)->push_back((yystack_[0].value.stmtptr)); (yylhs.value.stmt_list) = (yystack_[2].value.stmt_list); }
#line 709 "parser.cpp"
    break;

  case 16: // stmt: %empty
#line 139 "parser.y"
                                        { (yylhs.value.stmtptr) = new Skip(); }
#line 715 "parser.cpp"
    break;

  case 17: // stmt: name ASSIGN expr
#line 140 "parser.y"
                                        { (yylhs.value.stmtptr) = new Assign((yystack_[2].value.nameval), (yystack_[0].value.exprval)); }
#line 721 "parser.cpp"
    break;

  case 18: // stmt: RETURN expr
#line 141 "parser.y"
                                        { (yylhs.value.stmtptr) = new Return((yystack_[0].value.exprval)); }
#line 727 "parser.cpp"
    break;

  case 19: // stmt: IF expr THEN stmts PROC_END
#line 142 "parser.y"
                                             { (yylhs.value.stmtptr) = new IfStmt((yystack_[3].value.exprval), (yystack_[1].value.stmtptr), new Skip()); }
#line 733 "parser.cpp"
    break;

  case 20: // stmt: IF expr THEN stmts ELSE stmts PROC_END
#line 143 "parser.y"
                                             { (yylhs.value.stmtptr) = new IfStmt((yystack_[5].value.exprval), (yystack_[3].value.stmtptr), (yystack_[1].value.stmtptr)); }
#line 739 "parser.cpp"
    break;

  case 21: // stmt: WHILE expr DO stmts PROC_END
#line 144 "parser.y"
                                             { (yylhs.value.stmtptr) = new WhileStmt((yystack_[3].value.exprval), (yystack_[1].value.stmtptr)); }
#line 745 "parser.cpp"
    break;

  case 22: // stmt: PRINT expr
#line 145 "parser.y"
                                        { (yylhs.value.stmtptr) = new Print((yystack_[0].value.exprval)); }
#line 751 "parser.cpp"
    break;

  case 23: // stmt: NEWLINE
#line 146 "parser.y"
                                        { (yylhs.value.stmtptr) = new Newline(); }
#line 757 "parser.cpp"
    break;

  case 24: // actuals: LPAR RPAR
#line 150 "parser.y"
                                        { (yylhs.value.expr_list) = new vector<Expr *> (); }
#line 763 "parser.cpp"
    break;

  case 25: // actuals: LPAR expr_list RPAR
#line 151 "parser.y"
                                        { (yylhs.value.expr_list) = (yystack_[1].value.expr_list); }
#line 769 "parser.cpp"
    break;

  case 26: // expr_list: expr
#line 155 "parser.y"
                                        { vector<Expr *> *exs = new vector<Expr *>(); 
                                          exs->push_back((yystack_[0].value.exprval)); (yylhs.value.expr_list) = exs; }
#line 776 "parser.cpp"
    break;

  case 27: // expr_list: expr_list COMMA expr
#line 157 "parser.y"
                                        { (yystack_[2].value.expr_list)->push_back((yystack_[0].value.exprval)); (yylhs.value.expr_list) = (yystack_[2].value.expr_list); }
#line 782 "parser.cpp"
    break;

  case 28: // expr: simple
#line 161 "parser.y"
                                        { (yylhs.value.exprval) = (yystack_[0].value.exprval); }
#line 788 "parser.cpp"
    break;

  case 29: // expr: expr RELOP simple
#line 162 "parser.y"
                                        { (yylhs.value.exprval) = new Binop((yystack_[1].value.opval), (yystack_[2].value.exprval), (yystack_[0].value.exprval)); }
#line 794 "parser.cpp"
    break;

  case 30: // simple: term
#line 166 "parser.y"
                                        { (yylhs.value.exprval) = (yystack_[0].value.exprval); }
#line 800 "parser.cpp"
    break;

  case 31: // simple: simple ADDOP term
#line 167 "parser.y"
                                        { (yylhs.value.exprval) = new Binop((yystack_[1].value.opval), (yystack_[2].value.exprval), (yystack_[0].value.exprval)); }
#line 806 "parser.cpp"
    break;

  case 32: // simple: simple MINUS term
#line 168 "parser.y"
                                        { (yylhs.value.exprval) = new Binop(Minus, (yystack_[2].value.exprval), (yystack_[0].value.exprval)); }
#line 812 "parser.cpp"
    break;

  case 33: // term: factor
#line 172 "parser.y"
                                        { (yylhs.value.exprval) = (yystack_[0].value.exprval); }
#line 818 "parser.cpp"
    break;

  case 34: // term: term MULOP factor
#line 173 "parser.y"
                                        { (yylhs.value.exprval) = new Binop((yystack_[1].value.opval), (yystack_[2].value.exprval), (yystack_[0].value.exprval)); }
#line 824 "parser.cpp"
    break;

  case 35: // factor: NUMBER
#line 177 "parser.y"
                                        { (yylhs.value.exprval) = new Constant((yystack_[0].value.intval)); }
#line 830 "parser.cpp"
    break;

  case 36: // factor: name
#line 178 "parser.y"
                                        { (yylhs.value.exprval) = new Variable((yystack_[0].value.nameval)); }
#line 836 "parser.cpp"
    break;

  case 37: // factor: name actuals
#line 179 "parser.y"
                                        { (yylhs.value.exprval) = new Call((yystack_[1].value.nameval), (yystack_[0].value.expr_list)); }
#line 842 "parser.cpp"
    break;

  case 38: // factor: MONOP factor
#line 180 "parser.y"
                                        { (yylhs.value.exprval) = new Monop((yystack_[1].value.opval), (yystack_[0].value.exprval)); }
#line 848 "parser.cpp"
    break;

  case 39: // factor: MINUS factor
#line 181 "parser.y"
                                        { (yylhs.value.exprval) = new Monop(Uminus, (yystack_[0].value.exprval)); }
#line 854 "parser.cpp"
    break;

  case 40: // factor: LPAR expr RPAR
#line 182 "parser.y"
                                        { (yylhs.value.exprval) = (yystack_[1].value.exprval); }
#line 860 "parser.cpp"
    break;

  case 41: // name: IDENT
#line 186 "parser.y"
                                        { (yylhs.value.nameval) = Pascal::makeName(*(yystack_[0].value.strval), 0); }
#line 866 "parser.cpp"
    break;


#line 870 "parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        std::string msg = YY_("syntax error");
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

#if YYDEBUG || 0
  const char *
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytname_[yysymbol];
  }
#endif // #if YYDEBUG || 0









  const signed char Parser::yypact_ninf_ = -47;

  const signed char Parser::yytable_ninf_ = -1;

  const signed char
  Parser::yypact_[] =
  {
       6,    19,    36,    20,   -47,   -47,    38,   -47,   -47,    -9,
      37,   -47,     2,    59,   -47,   -47,   -47,    43,    43,    43,
      43,   -47,    45,    52,   -47,    51,    57,   -47,    43,    43,
      43,    60,    10,    63,   -47,    61,    -2,     7,    60,   -47,
       2,    43,     9,    62,   -47,   -47,     5,    43,    43,    43,
      43,    34,   -47,     2,     2,   -47,    60,   -47,    44,     6,
     -47,    10,    63,    63,   -47,   -47,    47,    60,    30,    53,
     -47,    64,   -47,    43,   -47,     2,   -47,   -47,    60,    54,
     -47
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     0,     0,     8,     6,     0,     1,     2,     0,
       0,     5,    16,     0,     9,     7,    41,     0,     0,     0,
       0,    23,     0,    13,    14,     0,     0,    35,     0,     0,
       0,    22,    28,    30,    33,    36,     0,     0,    18,     3,
      16,     0,     0,     0,    38,    39,     0,     0,     0,     0,
       0,     0,    37,    16,    16,    15,    17,    11,     0,     4,
      40,    29,    31,    32,    34,    24,     0,    26,     0,     0,
      12,     0,    25,     0,    19,    16,    21,    10,    27,     0,
      20
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -47,   -47,    11,   -47,    32,   -47,   -47,   -47,   -46,   -47,
      39,   -47,   -47,   -16,    29,    12,   -18,   -12
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     2,     3,     4,     6,     9,    14,    43,    22,    23,
      24,    52,    66,    31,    32,    33,    34,    35
  };

  const signed char
  Parser::yytable_[] =
  {
      25,    26,    36,    37,    38,    16,    47,    68,    69,    12,
      44,    45,     5,    47,    46,    47,    60,    48,    13,    49,
      57,    53,     5,    17,    18,    56,     1,    19,    25,    79,
      20,    21,    64,    54,     8,    67,     7,    16,    27,    28,
      15,    25,    25,    29,    30,    65,    16,    27,    28,    74,
      10,    11,    29,    30,    75,    70,    10,    78,    72,    73,
      62,    63,    16,    25,    39,    40,    41,    42,    47,    50,
      71,    51,    76,    80,    58,    59,    61,    77,     0,    55
  };

  const signed char
  Parser::yycheck_[] =
  {
      12,    13,    18,    19,    20,     3,     8,    53,    54,    18,
      28,    29,     3,     8,    30,     8,    11,     7,    27,     9,
      11,    23,     3,    21,    22,    41,    20,    25,    40,    75,
      28,    29,    50,    26,    14,    51,     0,     3,     4,     5,
       3,    53,    54,     9,    10,    11,     3,     4,     5,    19,
      12,    13,     9,    10,    24,    11,    12,    73,    11,    12,
      48,    49,     3,    75,    19,    13,    15,    10,     8,     6,
      59,    10,    19,    19,    42,    13,    47,    13,    -1,    40
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    20,    31,    32,    33,     3,    34,     0,    14,    35,
      12,    13,    18,    27,    36,     3,     3,    21,    22,    25,
      28,    29,    38,    39,    40,    47,    47,     4,     5,     9,
      10,    43,    44,    45,    46,    47,    43,    43,    43,    19,
      13,    15,    10,    37,    46,    46,    43,     8,     7,     9,
       6,    10,    41,    23,    26,    40,    43,    11,    34,    13,
      11,    44,    45,    45,    46,    11,    42,    43,    38,    38,
      11,    32,    11,    12,    19,    24,    19,    13,    43,    38,
      19
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    30,    31,    32,    33,    33,    34,    34,    35,    35,
      36,    37,    37,    38,    39,    39,    40,    40,    40,    40,
      40,    40,    40,    40,    41,    41,    42,    42,    43,    43,
      44,    44,    44,    45,    45,    46,    46,    46,    46,    46,
      46,    47
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     5,     0,     3,     1,     3,     0,     2,
       6,     2,     3,     1,     1,     3,     0,     3,     2,     5,
       7,     5,     2,     1,     2,     3,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     1,     1,     2,     2,     2,
       3,     1
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "IDENT", "NUMBER",
  "MONOP", "MULOP", "ADDOP", "RELOP", "MINUS", "LPAR", "RPAR", "COMMA",
  "SEMI", "DOT", "ASSIGN", "EOFP", "BADTOK", "PROC_BEGIN", "PROC_END",
  "VAR", "PRINT", "IF", "THEN", "ELSE", "WHILE", "DO", "PROC", "RETURN",
  "NEWLINE", "$accept", "program", "block", "var_decl", "ident_list",
  "proc_decls", "proc_decl", "formals", "stmts", "stmt_list", "stmt",
  "actuals", "expr_list", "expr", "simple", "term", "factor", "name", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    96,    96,   100,   104,   105,   109,   111,   115,   116,
     120,   124,   125,   129,   133,   135,   139,   140,   141,   142,
     143,   144,   145,   146,   150,   151,   155,   157,   161,   162,
     166,   167,   168,   172,   173,   177,   178,   179,   180,   181,
     182,   186
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29
    };
    // Last valid token kind.
    const int code_max = 284;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 6 "parser.y"
} // Pascal
#line 1277 "parser.cpp"

#line 189 "parser.y"


void Pascal::Parser::error(const location_type &l,
                           const std::string &err_message) {
  std::cerr << "Error: " << err_message << " at " << l << "\n";
}
