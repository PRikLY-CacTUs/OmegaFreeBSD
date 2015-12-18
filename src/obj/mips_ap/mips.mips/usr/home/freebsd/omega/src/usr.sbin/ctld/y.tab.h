#define ALIAS 257
#define AUTH_GROUP 258
#define AUTH_TYPE 259
#define BACKEND 260
#define BLOCKSIZE 261
#define CHAP 262
#define CHAP_MUTUAL 263
#define CLOSING_BRACKET 264
#define CTL_LUN 265
#define DEBUG 266
#define DEVICE_ID 267
#define DEVICE_TYPE 268
#define DISCOVERY_AUTH_GROUP 269
#define DISCOVERY_FILTER 270
#define FOREIGN 271
#define INITIATOR_NAME 272
#define INITIATOR_PORTAL 273
#define ISNS_SERVER 274
#define ISNS_PERIOD 275
#define ISNS_TIMEOUT 276
#define LISTEN 277
#define LISTEN_ISER 278
#define LUN 279
#define MAXPROC 280
#define OFFLOAD 281
#define OPENING_BRACKET 282
#define OPTION 283
#define PATH 284
#define PIDFILE 285
#define PORT 286
#define PORTAL_GROUP 287
#define REDIRECT 288
#define SEMICOLON 289
#define SERIAL 290
#define SIZE 291
#define STR 292
#define TAG 293
#define TARGET 294
#define TIMEOUT 295
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
