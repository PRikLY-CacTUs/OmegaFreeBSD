#define NEWLINE 257
#define VERBOSE 258
#define FILENAME 259
#define ADDLIB 260
#define LIST 261
#define ADDMOD 262
#define CLEAR 263
#define CREATE 264
#define DELETE 265
#define DIRECTORY 266
#define END 267
#define EXTRACT 268
#define FULLDIR 269
#define HELP 270
#define QUIT 271
#define REPLACE 272
#define SAVE 273
#define OPEN 274
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
  char *name;
struct list *list ;

} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
