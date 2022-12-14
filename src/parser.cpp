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

// "%code top" blocks.
#line 39 "parser.y"

    #include <iostream>
    #include "scanner.h"
    #include "parser.h"
    #include "driver.h"
    #include "location.hh"
    
    using namespace Pascal;
    
    // yylex() arguments are defined in parser.y
    static Parser::symbol_type yylex(Scanner &scanner, Driver &driver) {
        return scanner.get_next_token();
    }
    
    // you can accomplish the same thing by inlining the code using preprocessor
    // x and y are same as in above static function
    // #define yylex(x, y) scanner.get_next_token()

#line 58 "parser.cpp"




#include "parser.h"




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

#line 8 "parser.y"
namespace  Pascal  {
#line 158 "parser.cpp"

  /// Build a parser object.
   Parser :: Parser  (Pascal::Scanner &scanner_yyarg, Pascal::Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      driver (driver_yyarg)
  {}

   Parser ::~ Parser  ()
  {}

   Parser ::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
   Parser ::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

   Parser ::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
   Parser ::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
   Parser ::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

   Parser ::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

   Parser ::symbol_kind_type
   Parser ::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

   Parser ::stack_symbol_type::stack_symbol_type ()
  {}

   Parser ::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.YY_MOVE_OR_COPY< Block * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_simple: // simple
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.YY_MOVE_OR_COPY< Expr * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.YY_MOVE_OR_COPY< Name * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.YY_MOVE_OR_COPY< Proc * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< Program * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< Stmt * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actuals: // actuals
      case symbol_kind::S_expr_list: // expr_list
        value.YY_MOVE_OR_COPY< exprList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_formals: // formals
        value.YY_MOVE_OR_COPY< identList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MONOP: // "monop"
      case symbol_kind::S_MULOP: // "mulop"
      case symbol_kind::S_ADDOP: // "addop"
      case symbol_kind::S_RELOP: // "relop"
        value.YY_MOVE_OR_COPY< op > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decls: // proc_decls
        value.YY_MOVE_OR_COPY< procList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.YY_MOVE_OR_COPY< stmtList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // "ident"
        value.YY_MOVE_OR_COPY< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

   Parser ::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.move< Block * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_simple: // simple
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< Expr * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.move< Name * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.move< Proc * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< Program * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
        value.move< Stmt * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actuals: // actuals
      case symbol_kind::S_expr_list: // expr_list
        value.move< exprList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_formals: // formals
        value.move< identList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MONOP: // "monop"
      case symbol_kind::S_MULOP: // "mulop"
      case symbol_kind::S_ADDOP: // "addop"
      case symbol_kind::S_RELOP: // "relop"
        value.move< op > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_proc_decls: // proc_decls
        value.move< procList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmtList > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENT: // "ident"
        value.move< string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< uint64_t > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.copy< Block * > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_simple: // simple
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.copy< Expr * > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.copy< Name * > (that.value);
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.copy< Proc * > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< Program * > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
        value.copy< Stmt * > (that.value);
        break;

      case symbol_kind::S_actuals: // actuals
      case symbol_kind::S_expr_list: // expr_list
        value.copy< exprList > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_formals: // formals
        value.copy< identList > (that.value);
        break;

      case symbol_kind::S_MONOP: // "monop"
      case symbol_kind::S_MULOP: // "mulop"
      case symbol_kind::S_ADDOP: // "addop"
      case symbol_kind::S_RELOP: // "relop"
        value.copy< op > (that.value);
        break;

      case symbol_kind::S_proc_decls: // proc_decls
        value.copy< procList > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.copy< stmtList > (that.value);
        break;

      case symbol_kind::S_IDENT: // "ident"
        value.copy< string > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

   Parser ::stack_symbol_type&
   Parser ::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_block: // block
        value.move< Block * > (that.value);
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_simple: // simple
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        value.move< Expr * > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.move< Name * > (that.value);
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        value.move< Proc * > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< Program * > (that.value);
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
        value.move< Stmt * > (that.value);
        break;

      case symbol_kind::S_actuals: // actuals
      case symbol_kind::S_expr_list: // expr_list
        value.move< exprList > (that.value);
        break;

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_formals: // formals
        value.move< identList > (that.value);
        break;

      case symbol_kind::S_MONOP: // "monop"
      case symbol_kind::S_MULOP: // "mulop"
      case symbol_kind::S_ADDOP: // "addop"
      case symbol_kind::S_RELOP: // "relop"
        value.move< op > (that.value);
        break;

      case symbol_kind::S_proc_decls: // proc_decls
        value.move< procList > (that.value);
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        value.move< stmtList > (that.value);
        break;

      case symbol_kind::S_IDENT: // "ident"
        value.move< string > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< uint64_t > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
   Parser ::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
   Parser ::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
   Parser ::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
   Parser ::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
   Parser ::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
   Parser ::debug_stream () const
  {
    return *yycdebug_;
  }

  void
   Parser ::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


   Parser ::debug_level_type
   Parser ::debug_level () const
  {
    return yydebug_;
  }

  void
   Parser ::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

   Parser ::state_type
   Parser ::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
   Parser ::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
   Parser ::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
   Parser ::operator() ()
  {
    return parse ();
  }

  int
   Parser ::parse ()
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
            symbol_type yylookahead (yylex (scanner, driver));
            yyla.move (yylookahead);
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
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_block: // block
        yylhs.value.emplace< Block * > ();
        break;

      case symbol_kind::S_expr: // expr
      case symbol_kind::S_simple: // simple
      case symbol_kind::S_term: // term
      case symbol_kind::S_factor: // factor
        yylhs.value.emplace< Expr * > ();
        break;

      case symbol_kind::S_name: // name
        yylhs.value.emplace< Name * > ();
        break;

      case symbol_kind::S_proc_decl: // proc_decl
        yylhs.value.emplace< Proc * > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< Program * > ();
        break;

      case symbol_kind::S_stmts: // stmts
      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< Stmt * > ();
        break;

      case symbol_kind::S_actuals: // actuals
      case symbol_kind::S_expr_list: // expr_list
        yylhs.value.emplace< exprList > ();
        break;

      case symbol_kind::S_var_decl: // var_decl
      case symbol_kind::S_ident_list: // ident_list
      case symbol_kind::S_formals: // formals
        yylhs.value.emplace< identList > ();
        break;

      case symbol_kind::S_MONOP: // "monop"
      case symbol_kind::S_MULOP: // "mulop"
      case symbol_kind::S_ADDOP: // "addop"
      case symbol_kind::S_RELOP: // "relop"
        yylhs.value.emplace< op > ();
        break;

      case symbol_kind::S_proc_decls: // proc_decls
        yylhs.value.emplace< procList > ();
        break;

      case symbol_kind::S_stmt_list: // stmt_list
        yylhs.value.emplace< stmtList > ();
        break;

      case symbol_kind::S_IDENT: // "ident"
        yylhs.value.emplace< string > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< uint64_t > ();
        break;

      default:
        break;
    }


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
  case 2: // program: block "."
#line 127 "parser.y"
                                        { Program *pgm = new Program(yystack_[1].value.as < Block * > ());
                                          driver.setProgram(pgm); }
#line 864 "parser.cpp"
    break;

  case 3: // block: var_decl proc_decls "begin" stmts "end"
#line 132 "parser.y"
                                                  { yylhs.value.as < Block * > () = new Block(yystack_[4].value.as < identList > (), yystack_[3].value.as < procList > (), yystack_[1].value.as < Stmt * > ()); }
#line 870 "parser.cpp"
    break;

  case 4: // var_decl: %empty
#line 136 "parser.y"
                                        { yylhs.value.as < identList > () = new vector<ident>(); }
#line 876 "parser.cpp"
    break;

  case 5: // var_decl: "var" ident_list ";"
#line 137 "parser.y"
                                        { yylhs.value.as < identList > () = yystack_[1].value.as < identList > (); }
#line 882 "parser.cpp"
    break;

  case 6: // ident_list: "ident"
#line 141 "parser.y"
                                        { vector<ident> *ids = new vector<ident>(); 
                                          ids->push_back(yystack_[0].value.as < string > ()); yylhs.value.as < identList > () = ids; }
#line 889 "parser.cpp"
    break;

  case 7: // ident_list: ident_list "," "ident"
#line 143 "parser.y"
                                        { yystack_[2].value.as < identList > ()->push_back(yystack_[0].value.as < string > ()); yylhs.value.as < identList > () = yystack_[2].value.as < identList > (); }
#line 895 "parser.cpp"
    break;

  case 8: // proc_decls: %empty
#line 147 "parser.y"
                                        { yylhs.value.as < procList > () = new vector<Proc *>(); }
#line 901 "parser.cpp"
    break;

  case 9: // proc_decls: proc_decls proc_decl
#line 148 "parser.y"
                                        { yystack_[1].value.as < procList > ()->push_back(yystack_[0].value.as < Proc * > ()); yylhs.value.as < procList > () = yystack_[1].value.as < procList > (); }
#line 907 "parser.cpp"
    break;

  case 10: // proc_decl: "proc" name formals ";" block ";"
#line 152 "parser.y"
                                        { new Proc(yystack_[4].value.as < Name * > (), yystack_[3].value.as < identList > (), yystack_[1].value.as < Block * > ()); }
#line 913 "parser.cpp"
    break;

  case 11: // formals: "(" ")"
#line 156 "parser.y"
                                        { yylhs.value.as < identList > () = new vector<ident>(); }
#line 919 "parser.cpp"
    break;

  case 12: // formals: "(" ident_list ")"
#line 157 "parser.y"
                                        { yylhs.value.as < identList > () = yystack_[1].value.as < identList > (); }
#line 925 "parser.cpp"
    break;

  case 13: // stmts: stmt_list
#line 161 "parser.y"
                                        { yylhs.value.as < Stmt * > () = Pascal::sequence(yystack_[0].value.as < stmtList > ()); }
#line 931 "parser.cpp"
    break;

  case 14: // stmt_list: stmt
#line 165 "parser.y"
                                        { vector<Stmt *> *sts = new vector<Stmt *>(); 
                                          sts->push_back(yystack_[0].value.as < Stmt * > ()); yylhs.value.as < stmtList > () = sts; }
#line 938 "parser.cpp"
    break;

  case 15: // stmt_list: stmt_list ";" stmt
#line 167 "parser.y"
                                        { yystack_[2].value.as < stmtList > ()->push_back(yystack_[0].value.as < Stmt * > ()); yylhs.value.as < stmtList > () = yystack_[2].value.as < stmtList > (); }
#line 944 "parser.cpp"
    break;

  case 16: // stmt: name ":=" expr
#line 172 "parser.y"
                                       { yylhs.value.as < Stmt * > () = new Assign(yystack_[2].value.as < Name * > (), yystack_[0].value.as < Expr * > ()); }
#line 950 "parser.cpp"
    break;

  case 17: // stmt: "return" expr
#line 173 "parser.y"
                                        { yylhs.value.as < Stmt * > () = new Return(yystack_[0].value.as < Expr * > ()); }
#line 956 "parser.cpp"
    break;

  case 18: // stmt: "if" expr "then" stmts "end"
#line 174 "parser.y"
                                             { yylhs.value.as < Stmt * > () = new IfStmt(yystack_[3].value.as < Expr * > (), yystack_[1].value.as < Stmt * > (), new Skip()); }
#line 962 "parser.cpp"
    break;

  case 19: // stmt: "if" expr "then" stmts "else" stmts "end"
#line 175 "parser.y"
                                             { yylhs.value.as < Stmt * > () = new IfStmt(yystack_[5].value.as < Expr * > (), yystack_[3].value.as < Stmt * > (), yystack_[1].value.as < Stmt * > ()); }
#line 968 "parser.cpp"
    break;

  case 20: // stmt: "while" expr "do" stmts "end"
#line 176 "parser.y"
                                             { yylhs.value.as < Stmt * > () = new WhileStmt(yystack_[3].value.as < Expr * > (), yystack_[1].value.as < Stmt * > ()); }
#line 974 "parser.cpp"
    break;

  case 21: // stmt: "print" expr
#line 177 "parser.y"
                                        { yylhs.value.as < Stmt * > () = new Print(yystack_[0].value.as < Expr * > ()); }
#line 980 "parser.cpp"
    break;

  case 22: // stmt: "newline"
#line 178 "parser.y"
                                        { yylhs.value.as < Stmt * > () = new Newline(); }
#line 986 "parser.cpp"
    break;

  case 23: // actuals: "(" ")"
#line 182 "parser.y"
                                        { yylhs.value.as < exprList > () = new vector<Expr *> (); }
#line 992 "parser.cpp"
    break;

  case 24: // actuals: "(" expr_list ")"
#line 183 "parser.y"
                                        { yylhs.value.as < exprList > () = yystack_[1].value.as < exprList > (); }
#line 998 "parser.cpp"
    break;

  case 25: // expr_list: expr
#line 187 "parser.y"
                                        { vector<Expr *> *exs = new vector<Expr *>(); 
                                          exs->push_back(yystack_[0].value.as < Expr * > ()); yylhs.value.as < exprList > () = exs; }
#line 1005 "parser.cpp"
    break;

  case 26: // expr_list: expr_list "," expr
#line 189 "parser.y"
                                        { yystack_[2].value.as < exprList > ()->push_back(yystack_[0].value.as < Expr * > ()); yylhs.value.as < exprList > () = yystack_[2].value.as < exprList > (); }
#line 1011 "parser.cpp"
    break;

  case 27: // expr: simple
#line 193 "parser.y"
                                        { yylhs.value.as < Expr * > () = yystack_[0].value.as < Expr * > (); }
#line 1017 "parser.cpp"
    break;

  case 28: // expr: expr "relop" simple
#line 194 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Binop(yystack_[1].value.as < op > (), yystack_[2].value.as < Expr * > (), yystack_[0].value.as < Expr * > ()); }
#line 1023 "parser.cpp"
    break;

  case 29: // simple: term
#line 198 "parser.y"
                                        { yylhs.value.as < Expr * > () = yystack_[0].value.as < Expr * > (); }
#line 1029 "parser.cpp"
    break;

  case 30: // simple: simple "addop" term
#line 199 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Binop(yystack_[1].value.as < op > (), yystack_[2].value.as < Expr * > (), yystack_[0].value.as < Expr * > ()); }
#line 1035 "parser.cpp"
    break;

  case 31: // simple: simple "-" term
#line 200 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Binop(Minus, yystack_[2].value.as < Expr * > (), yystack_[0].value.as < Expr * > ()); }
#line 1041 "parser.cpp"
    break;

  case 32: // term: factor
#line 204 "parser.y"
                                        { yylhs.value.as < Expr * > () = yystack_[0].value.as < Expr * > (); }
#line 1047 "parser.cpp"
    break;

  case 33: // term: term "mulop" factor
#line 205 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Binop(yystack_[1].value.as < op > (), yystack_[2].value.as < Expr * > (), yystack_[0].value.as < Expr * > ()); }
#line 1053 "parser.cpp"
    break;

  case 34: // factor: "number"
#line 209 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Constant(yystack_[0].value.as < uint64_t > ()); }
#line 1059 "parser.cpp"
    break;

  case 35: // factor: name
#line 210 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Variable(yystack_[0].value.as < Name * > ()); }
#line 1065 "parser.cpp"
    break;

  case 36: // factor: name actuals
#line 211 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Call(yystack_[1].value.as < Name * > (), yystack_[0].value.as < exprList > ()); }
#line 1071 "parser.cpp"
    break;

  case 37: // factor: "monop" factor
#line 212 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Monop(yystack_[1].value.as < op > (), yystack_[0].value.as < Expr * > ()); }
#line 1077 "parser.cpp"
    break;

  case 38: // factor: "-" factor
#line 213 "parser.y"
                                        { yylhs.value.as < Expr * > () = new Monop(Uminus, yystack_[0].value.as < Expr * > ()); }
#line 1083 "parser.cpp"
    break;

  case 39: // factor: "(" expr ")"
#line 214 "parser.y"
                                        { yylhs.value.as < Expr * > () = yystack_[1].value.as < Expr * > (); }
#line 1089 "parser.cpp"
    break;

  case 40: // name: "ident"
#line 218 "parser.y"
                                        { yylhs.value.as < Name * > () = Pascal::makeName(yystack_[0].value.as < string > (), 0); }
#line 1095 "parser.cpp"
    break;


#line 1099 "parser.cpp"

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
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
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
   Parser ::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
   Parser ::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
   Parser ::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  //  Parser ::context.
   Parser ::context::context (const  Parser & yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
   Parser ::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
   Parser ::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
   Parser ::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char  Parser ::yypact_ninf_ = -45;

  const signed char  Parser ::yytable_ninf_ = -1;

  const signed char
   Parser ::yypact_[] =
  {
       8,    32,    40,    48,   -45,   -45,    37,   -45,   -45,    -9,
      50,   -45,     2,    60,   -45,   -45,   -45,    43,    43,    43,
      43,   -45,    33,    52,   -45,    51,    57,   -45,    43,    43,
      43,    61,    25,    62,   -45,    63,    -3,    -1,    61,   -45,
       2,    43,     9,    58,   -45,   -45,     7,    43,    43,    43,
      43,    34,   -45,     2,     2,   -45,    61,   -45,    44,     8,
     -45,    25,    62,    62,   -45,   -45,    47,    61,    -2,    54,
     -45,    64,   -45,    43,   -45,     2,   -45,   -45,    61,    56,
     -45
  };

  const signed char
   Parser ::yydefact_[] =
  {
       4,     0,     0,     0,     8,     6,     0,     1,     2,     0,
       0,     5,     0,     0,     9,     7,    40,     0,     0,     0,
       0,    22,     0,    13,    14,     0,     0,    34,     0,     0,
       0,    21,    27,    29,    32,    35,     0,     0,    17,     3,
       0,     0,     0,     0,    37,    38,     0,     0,     0,     0,
       0,     0,    36,     0,     0,    15,    16,    11,     0,     4,
      39,    28,    30,    31,    33,    23,     0,    25,     0,     0,
      12,     0,    24,     0,    18,     0,    20,    10,    26,     0,
      19
  };

  const signed char
   Parser ::yypgoto_[] =
  {
     -45,   -45,    11,   -45,    36,   -45,   -45,   -45,   -44,   -45,
      35,   -45,   -45,   -16,    29,    12,   -17,   -12
  };

  const signed char
   Parser ::yydefgoto_[] =
  {
       0,     2,     3,     4,     6,     9,    14,    43,    22,    23,
      24,    52,    66,    31,    32,    33,    34,    35
  };

  const signed char
   Parser ::yytable_[] =
  {
      25,    26,    36,    37,    38,    47,    16,    47,    12,    68,
      69,    44,    45,     5,    46,    47,    74,    13,    60,    53,
      57,    75,    17,    18,    54,    56,    19,     1,    25,    20,
      21,    79,    48,    64,    49,    67,     5,    27,    16,    28,
       7,    25,    25,    29,    30,    65,    27,    16,    28,    10,
      11,    39,    29,    30,    15,    70,    10,    78,    72,    73,
      62,    63,     8,    25,    16,    40,    41,    42,    50,    47,
      71,    59,    76,    51,    80,    55,    61,    77,    58
  };

  const signed char
   Parser ::yycheck_[] =
  {
      12,    13,    18,    19,    20,     8,     4,     8,    17,    53,
      54,    28,    29,     4,    30,     8,    18,    26,    11,    22,
      11,    23,    20,    21,    25,    41,    24,    19,    40,    27,
      28,    75,     7,    50,     9,    51,     4,     3,     4,     5,
       0,    53,    54,     9,    10,    11,     3,     4,     5,    12,
      13,    18,     9,    10,     4,    11,    12,    73,    11,    12,
      48,    49,    14,    75,     4,    13,    15,    10,     6,     8,
      59,    13,    18,    10,    18,    40,    47,    13,    42
  };

  const signed char
   Parser ::yystos_[] =
  {
       0,    19,    31,    32,    33,     4,    34,     0,    14,    35,
      12,    13,    17,    26,    36,     4,     4,    20,    21,    24,
      27,    28,    38,    39,    40,    47,    47,     3,     5,     9,
      10,    43,    44,    45,    46,    47,    43,    43,    43,    18,
      13,    15,    10,    37,    46,    46,    43,     8,     7,     9,
       6,    10,    41,    22,    25,    40,    43,    11,    34,    13,
      11,    44,    45,    45,    46,    11,    42,    43,    38,    38,
      11,    32,    11,    12,    18,    23,    18,    13,    43,    38,
      18
  };

  const signed char
   Parser ::yyr1_[] =
  {
       0,    30,    31,    32,    33,    33,    34,    34,    35,    35,
      36,    37,    37,    38,    39,    39,    40,    40,    40,    40,
      40,    40,    40,    41,    41,    42,    42,    43,    43,    44,
      44,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      47
  };

  const signed char
   Parser ::yyr2_[] =
  {
       0,     2,     2,     5,     0,     3,     1,     3,     0,     2,
       6,     2,     3,     1,     1,     3,     3,     2,     5,     7,
       5,     2,     1,     2,     3,     1,     3,     1,     3,     1,
       3,     3,     1,     3,     1,     1,     2,     2,     2,     3,
       1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const  Parser ::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"number\"",
  "\"ident\"", "\"monop\"", "\"mulop\"", "\"addop\"", "\"relop\"", "\"-\"",
  "\"(\"", "\")\"", "\",\"", "\";\"", "\".\"", "\":=\"", "\"_X_\"",
  "\"begin\"", "\"end\"", "\"var\"", "\"print\"", "\"if\"", "\"then\"",
  "\"else\"", "\"while\"", "\"do\"", "\"proc\"", "\"return\"",
  "\"newline\"", "\"end of line\"", "$accept", "program", "block",
  "var_decl", "ident_list", "proc_decls", "proc_decl", "formals", "stmts",
  "stmt_list", "stmt", "actuals", "expr_list", "expr", "simple", "term",
  "factor", "name", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
   Parser ::yyrline_[] =
  {
       0,   127,   127,   132,   136,   137,   141,   143,   147,   148,
     152,   156,   157,   161,   165,   167,   172,   173,   174,   175,
     176,   177,   178,   182,   183,   187,   189,   193,   194,   198,
     199,   200,   204,   205,   209,   210,   211,   212,   213,   214,
     218
  };

  void
   Parser ::yy_stack_print_ () const
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
   Parser ::yy_reduce_print_ (int yyrule) const
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


#line 8 "parser.y"
} //  Pascal 
#line 1618 "parser.cpp"

#line 221 "parser.y"


// Bison expects us to provide implementation - otherwise linker complains
void Parser::error(const location &loc, const std::string &message) {

  // Location should be initialized inside scanner action, but is not in this
  // example. Let's grab location directly from driver class. 

  // cout << "Error: " << message << endl << "Location: " << loc << endl;
  cout << "Error: " << message << endl
       << "Error location: " << driver.location() << endl;
}
