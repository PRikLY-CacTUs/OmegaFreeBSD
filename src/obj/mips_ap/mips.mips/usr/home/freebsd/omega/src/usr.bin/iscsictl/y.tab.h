#define AUTH_METHOD 257
#define HEADER_DIGEST 258
#define DATA_DIGEST 259
#define TARGET_NAME 260
#define TARGET_ADDRESS 261
#define INITIATOR_NAME 262
#define INITIATOR_ADDRESS 263
#define INITIATOR_ALIAS 264
#define USER 265
#define SECRET 266
#define MUTUAL_USER 267
#define MUTUAL_SECRET 268
#define SEMICOLON 269
#define SESSION_TYPE 270
#define PROTOCOL 271
#define OFFLOAD 272
#define IGNORED 273
#define EQUALS 274
#define OPENING_BRACKET 275
#define CLOSING_BRACKET 276
#define STR 277
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union
{
	char *str;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;
