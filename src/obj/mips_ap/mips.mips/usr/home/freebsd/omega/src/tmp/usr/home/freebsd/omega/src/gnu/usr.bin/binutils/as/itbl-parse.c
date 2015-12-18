/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20141006

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 22 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"

/* 

Yacc grammar for instruction table entries.

=======================================================================
Original Instruction table specification document:

	    MIPS Coprocessor Table Specification
	    ====================================

This document describes the format of the MIPS coprocessor table.  The
table specifies a list of valid functions, data registers and control
registers that can be used in coprocessor instructions.  This list,
together with the coprocessor instruction classes listed below,
specifies the complete list of coprocessor instructions that will
be recognized and assembled by the GNU assembler.  In effect,
this makes the GNU assembler table-driven, where the table is
specified by the programmer.

The table is an ordinary text file that the GNU assembler reads when
it starts.  Using the information in the table, the assembler
generates an internal list of valid coprocessor registers and
functions.  The assembler uses this internal list in addition to the
standard MIPS registers and instructions which are built-in to the 
assembler during code generation.

To specify the coprocessor table when invoking the GNU assembler, use
the command line option "--itbl file", where file is the
complete name of the table, including path and extension.

Examples:

	    gas -t cop.tbl test.s -o test.o
	    gas -t /usr/local/lib/cop.tbl test.s -o test.o
	    gas --itbl d:\gnu\data\cop.tbl test.s -o test.o

Only one table may be supplied during a single invocation of
the assembler.


Instruction classes
===================

Below is a list of the valid coprocessor instruction classes for
any given coprocessor "z".  These instructions are already recognized
by the assembler, and are listed here only for reference.

Class   format	    	    	      instructions
-------------------------------------------------
Class1:
	op base rt offset
	    	    	    	    	    	    	    LWCz rt,offset (base)
	    	    	    	    	    	    	    SWCz rt,offset (base)
Class2:
	COPz sub rt rd 0
	    	    	    	    	    	    	    MTCz rt,rd
	    	    	    	    	    	    	    MFCz rt,rd
	    	    	    	    	    	    	    CTCz rt,rd
	    	    	    	    	    	    	    CFCz rt,rd
Class3:
	COPz CO cofun
	    	    	    	    	    	    	    COPz cofun
Class4:
	COPz BC br offset
	    	    	    	    	    	    	    BCzT offset
	    	    	    	    	    	    	    BCzF offset
Class5:
	COPz sub rt rd 0
	    	    	    	    	    	    	    DMFCz rt,rd
	    	    	    	    	    	    	    DMTCz rt,rd
Class6:
	op base rt offset
	    	    	    	    	    	    	    LDCz rt,offset (base)
	    	    	    	    	    	    	    SDCz rt,offset (base)
Class7:
	COPz BC br offset
	    	    	    	    	    	    	    BCzTL offset
	    	    	    	    	    	    	    BCzFL offset

The coprocessor table defines coprocessor-specific registers that can
be used with all of the above classes of instructions, where
appropriate.  It also defines additional coprocessor-specific
functions for Class3 (COPz cofun) instructions, Thus, the table allows
the programmer to use convenient mnemonics and operands for these
functions, instead of the COPz mmenmonic and cofun operand.

The names of the MIPS general registers and their aliases are defined
by the assembler and will be recognized as valid register names by the
assembler when used (where allowed) in coprocessor instructions.
However, the names and values of all coprocessor data and control
register mnemonics must be specified in the coprocessor table.


Table Grammar
=============

Here is the grammar for the coprocessor table:

	    table -> entry*

	    entry -> [z entrydef] [comment] '\n'

	    entrydef -> type name val
	    entrydef -> 'insn' name val funcdef ; type of entry (instruction)

	    z -> 'p'['0'..'3']	    	     ; processor number 
	    type -> ['dreg' | 'creg' | 'greg' ]	     ; type of entry (register)
	; 'dreg', 'creg' or 'greg' specifies a data, control, or general
	;	    register mnemonic, respectively
	    name -> [ltr|dec]*	    	     ; mnemonic of register/function
	    val -> [dec|hex]	    	     ; register/function number (integer constant)

	    funcdef -> frange flags fields
	    	    	    	; bitfield range for opcode
	    	    	    	; list of fields' formats
	    fields -> field*
	    field -> [','] ftype frange flags
	    flags -> ['*' flagexpr]
	    flagexpr -> '[' flagexpr ']'
	    flagexpr -> val '|' flagexpr 
	    ftype -> [ type | 'immed' | 'addr' ]
	; 'immed' specifies an immediate value; see grammar for "val" above
	    	; 'addr' specifies a C identifier; name of symbol to be resolved at 
	;	    link time
	    frange -> ':' val '-' val	; starting to ending bit positions, where
	    	    	    	; where 0 is least significant bit
	    frange -> (null)	    	; default range of 31-0 will be assumed

	    comment -> [';'|'#'] [char]*
	    char -> any printable character
	    ltr -> ['a'..'z'|'A'..'Z'] 
	    dec -> ['0'..'9']*	    	    	    	    	     ; value in decimal
	    hex -> '0x'['0'..'9' | 'a'..'f' | 'A'..'F']*	; value in hexadecimal 


Examples
========

Example 1:

The table:

	    p1 dreg d1 1	     ; data register "d1" for COP1 has value 1
	    p1 creg c3 3	     ; ctrl register "c3" for COP1 has value 3
	    p3 func fill 0x1f:24-20	      ; function "fill" for COP3 has value 31 and 
	    	    	; no fields

will allow the assembler to accept the following coprocessor instructions:

	    LWC1 d1,0x100 ($2)
	    fill

Here, the general purpose register "$2", and instruction "LWC1", are standard 
mnemonics built-in to the MIPS assembler.  


Example 2:

The table:

	    p3 dreg d3 3	     ; data register "d3" for COP3 has value 3
	    p3 creg c2 22	     ; control register "c2" for COP3 has value 22
	    p3 func fee 0x1f:24-20 dreg:17-13 creg:12-8 immed:7-0 
	    	; function "fee" for COP3 has value 31, and 3 fields 
	    	; consisting of a data register, a control register, 
	    	; and an immediate value.

will allow the assembler to accept the following coprocessor instruction:

	    fee d3,c2,0x1

and will emit the object code:

	    31-26  25 24-20 19-18  17-13 12-8  7-0
	    COPz   CO fun	    	      dreg  creg  immed
	    010011 1  11111 00	     00011 10110 00000001 

	    0x4ff07601


Example 3:

The table:

	    p3 dreg d3 3	     ; data register "d3" for COP3 has value 3
	    p3 creg c2 22	     ; control register "c2" for COP3 has value 22
	    p3 func fuu 0x01f00001 dreg:17-13 creg:12-8

will allow the assembler to accept the following coprocessor
instruction:

	    fuu d3,c2

and will emit the object code:

	    31-26  25 24-20 19-18  17-13 12-8  7-0
	    COPz   CO fun	    	      dreg  creg  
	    010011 1  11111 00	     00011 10110 00000001 

	    0x4ff07601

In this way, the programmer can force arbitrary bits of an instruction
to have predefined values.

=======================================================================
Additional notes:

Encoding of ranges:
To handle more than one bit position range within an instruction,
use 0s to mask out the ranges which don't apply.
May decide to modify the syntax to allow commas separate multiple 
ranges within an instruction (range','range).

Changes in grammar:
	The number of parms argument to the function entry
was deleted from the original format such that we now count the fields.

----
FIXME! should really change lexical analyzer 
to recognize 'dreg' etc. in context sensitive way.
Currently function names or mnemonics may be incorrectly parsed as keywords

FIXME! hex is ambiguous with any digit

*/

#include "as.h"
#include "itbl-lex.h"
#include "itbl-ops.h"

/* #define DEBUG */

#ifdef DEBUG
#ifndef DBG_LVL
#define DBG_LVL 1
#endif
#else
#define DBG_LVL 0
#endif

#if DBG_LVL >= 1
#define DBG(x) printf x
#else
#define DBG(x) 
#endif

#if DBG_LVL >= 2
#define DBGL2(x) printf x
#else
#define DBGL2(x) 
#endif

static int sbit, ebit;
static struct itbl_entry *insn=0;
static int yyerror (const char *);

#line 281 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union 
  {
    char *str;
    int num;
    int processor;
    unsigned long val;
  } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 294 "itbl-parse.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define DREG 257
#define CREG 258
#define GREG 259
#define IMMED 260
#define ADDR 261
#define INSN 262
#define NUM 263
#define ID 264
#define NL 265
#define PNUM 266
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    9,    9,   10,   13,   10,   10,   10,   12,   12,
   12,    5,    5,    5,   14,    3,    3,    3,    2,    2,
   11,   11,    7,    6,    6,    6,    8,    4,    1,
};
static const YYINT yylen[] = {                            2,
    1,    2,    0,    5,    0,    9,    1,    2,    3,    2,
    0,    1,    1,    1,    3,    3,    3,    1,    2,    0,
    4,    0,    1,    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         0,
    0,    7,   23,    0,    0,    1,    0,    8,   24,   25,
   26,    0,    0,    2,   27,    0,    0,   29,    0,    0,
    0,    0,    4,    0,    0,    5,    0,    0,    0,   19,
    0,   21,    0,    0,   14,   13,    0,    0,   12,    0,
    0,   16,   17,    0,    0,    6,   10,    9,   15,
};
static const YYINT yydgoto[] = {                          4,
   19,   26,   30,    0,   38,   39,    5,   16,    6,    7,
   22,   40,   31,   41,
};
static const YYINT yysindex[] = {                      -253,
 -256,    0,    0,    0, -252,    0, -253,    0,    0,    0,
    0, -241, -241,    0,    0, -242, -242,    0,  -34, -240,
 -237,  -14,    0,  -18,  -90,    0, -233,  -93,  -90,    0,
  -15,    0,  -90,  -61,    0,    0, -243,  -34,    0, -232,
  -15,    0,    0,  -15,  -14,    0,    0,    0,    0,
};
static const YYINT yyrindex[] = {                        34,
    0,    0,    0,    0,    0,    0,   34,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  -42,    0,
    0,  -24,    0,    0,    0,    0,    0,  -33,    0,    0,
 -230,    0,    0,    0,    0,    0,    0,  -42,    0,    0,
 -230,    0,    0, -230,  -24,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
   19,   -8,  -25,    0,    0,   33,    0,   26,   35,    0,
    2,  -22,    0,    4,
};
#define YYTABLESIZE 246
static const YYINT yytable[] = {                         22,
   29,   22,    1,   34,    9,   10,   11,   42,    8,   12,
   18,    2,    3,    9,   10,   11,   35,   36,   47,   20,
   18,   48,   15,   21,   23,   24,   27,   25,   37,   32,
   33,   43,   46,    3,   11,   20,   49,   13,   17,   45,
   44,   14,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   18,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   28,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   22,   22,   22,   22,   22,    0,
    0,    0,   22,   18,   18,   18,   18,   18,    0,    0,
    0,   18,   20,   20,   20,   20,   20,    0,    0,    0,
   20,    9,   10,   11,   35,   36,
};
static const YYINT yycheck[] = {                         42,
   91,   44,  256,   29,  257,  258,  259,   33,  265,  262,
   44,  265,  266,  257,  258,  259,  260,  261,   41,   44,
  263,   44,  264,   58,  265,  263,   45,   42,   44,  263,
  124,   93,  265,    0,  265,   17,   45,    5,   13,   38,
   37,    7,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   93,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  263,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  257,  258,  259,  260,  261,   -1,
   -1,   -1,  265,  257,  258,  259,  260,  261,   -1,   -1,
   -1,  265,  257,  258,  259,  260,  261,   -1,   -1,   -1,
  265,  257,  258,  259,  260,  261,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 266
#define YYUNDFTOKEN 283
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,"'*'",0,"','","'-'",0,0,0,0,0,0,0,0,0,0,0,0,"':'",0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"DREG","CREG","GREG","IMMED","ADDR","INSN","NUM","ID","NL","PNUM",0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : insntbl",
"insntbl : entrys",
"entrys : entry entrys",
"entrys :",
"entry : pnum regtype name value NL",
"$$1 :",
"entry : pnum INSN name value range flags $$1 fieldspecs NL",
"entry : NL",
"entry : error NL",
"fieldspecs : ',' fieldspec fieldspecs",
"fieldspecs : fieldspec fieldspecs",
"fieldspecs :",
"ftype : regtype",
"ftype : ADDR",
"ftype : IMMED",
"fieldspec : ftype range flags",
"flagexpr : NUM '|' flagexpr",
"flagexpr : '[' flagexpr ']'",
"flagexpr : NUM",
"flags : '*' flagexpr",
"flags :",
"range : ':' NUM '-' NUM",
"range :",
"pnum : PNUM",
"regtype : DREG",
"regtype : CREG",
"regtype : GREG",
"name : ID",
"number : NUM",
"value : NUM",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 451 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"

static int
yyerror (msg)
     const char *msg;
{
  printf ("line %d: %s\n", insntbl_line, msg);
  return 0;
}
#line 530 "itbl-parse.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 4:
#line 309 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBG (("line %d: entry pnum=%d type=%d name=%s value=x%x\n", 
	    	    insntbl_line, yystack.l_mark[-4].num, yystack.l_mark[-3].num, yystack.l_mark[-2].str, yystack.l_mark[-1].val));
	    itbl_add_reg (yystack.l_mark[-4].num, yystack.l_mark[-3].num, yystack.l_mark[-2].str, yystack.l_mark[-1].val);
	  }
break;
case 5:
#line 315 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBG (("line %d: entry pnum=%d type=INSN name=%s value=x%x",
	    	    insntbl_line, yystack.l_mark[-5].num, yystack.l_mark[-3].str, yystack.l_mark[-2].val));
	    DBG ((" sbit=%d ebit=%d flags=0x%x\n", sbit, ebit, yystack.l_mark[0].val));
	    insn=itbl_add_insn (yystack.l_mark[-5].num, yystack.l_mark[-3].str, yystack.l_mark[-2].val, sbit, ebit, yystack.l_mark[0].val);
	  }
break;
case 6:
#line 322 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{}
break;
case 12:
#line 335 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("ftype\n"));
	    yyval.num = yystack.l_mark[0].num;
	  }
break;
case 13:
#line 340 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("addr\n"));
	    yyval.num = ADDR;
	  }
break;
case 14:
#line 345 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("immed\n"));
	    yyval.num = IMMED;
	  }
break;
case 15:
#line 353 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBG (("line %d: field type=%d sbit=%d ebit=%d, flags=0x%x\n", 
	    	    insntbl_line, yystack.l_mark[-2].num, sbit, ebit, yystack.l_mark[0].val));
	    itbl_add_operand (insn, yystack.l_mark[-2].num, sbit, ebit, yystack.l_mark[0].val);
	  }
break;
case 16:
#line 362 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    yyval.val = yystack.l_mark[-2].num | yystack.l_mark[0].val;
	  }
break;
case 17:
#line 366 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    yyval.val = yystack.l_mark[-1].val;
	  }
break;
case 18:
#line 370 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    yyval.val = yystack.l_mark[0].num;
	  }
break;
case 19:
#line 377 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("flags=%d\n", yystack.l_mark[0].val));
	    yyval.val = yystack.l_mark[0].val;
	  }
break;
case 20:
#line 382 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    yyval.val = 0;
	  }
break;
case 21:
#line 389 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("range %d %d\n", yystack.l_mark[-2].num, yystack.l_mark[0].num));
	    sbit = yystack.l_mark[-2].num;
	    ebit = yystack.l_mark[0].num;
	  }
break;
case 22:
#line 395 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    sbit = 31;
	    ebit = 0;
	  }
break;
case 23:
#line 403 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("pnum=%d\n",yystack.l_mark[0].num));
	    yyval.num = yystack.l_mark[0].num;
	  }
break;
case 24:
#line 411 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("dreg\n"));
	    yyval.num = DREG;
	  }
break;
case 25:
#line 416 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("creg\n"));
	    yyval.num = CREG;
	  }
break;
case 26:
#line 421 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("greg\n"));
	    yyval.num = GREG;
	  }
break;
case 27:
#line 429 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("name=%s\n",yystack.l_mark[0].str));
	    yyval.str = yystack.l_mark[0].str; 
	  }
break;
case 28:
#line 437 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("num=%d\n",yystack.l_mark[0].num));
	    yyval.num = yystack.l_mark[0].num;
	  }
break;
case 29:
#line 445 "/usr/home/freebsd/omega/src/gnu/usr.bin/binutils/as/../../../../contrib/binutils/gas/itbl-parse.y"
	{
	    DBGL2 (("val=x%x\n",yystack.l_mark[0].num));
	    yyval.val = yystack.l_mark[0].num;
	  }
break;
#line 877 "itbl-parse.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
