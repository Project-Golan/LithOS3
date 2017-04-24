//-----------------------------------------------------------------------------
//
// Copyright © 2016-2017 Project Golan
//
// See "LICENSE.lithos3" for more information.
//
//-----------------------------------------------------------------------------
//
// Tokenizer.
//
// If an x-macro is defined, the file will give info about token names.
//    Format: (name)
//    name - Name of the token.
//
//-----------------------------------------------------------------------------

#include "Lth_libinfo.h"

#if defined(Lth_X)

Lth_X(ChrSeq)
Lth_X(Identi)
Lth_X(Number)
Lth_X(Space )
Lth_X(String)

Lth_X(Minus ) // -
Lth_X(Dot   ) // .
Lth_X(Equals) // =
Lth_X(Semico) // ;

Lth_X(BrackO) // [
Lth_X(BrackC) // ]

Lth_X(LnEnd ) // \n

#undef Lth_X

#elif !defined(lithos3__Lth_token_h) && !LITHOS3_NO_TOKEN
#define lithos3__Lth_token_h

#include <stdio.h>

#define Lth_TokenSet(out, tok) \
   ((out)->str = NULL, (out)->type = Lth_TOK_##tok)

#define Lth_TokenCleanup(out) \
   ((out).str != NULL ? free((out).str) : ((void)0))


// Extern Functions ----------------------------------------------------------|

void Lth_TokenGet(FILE *fp, struct Lth_Token *out);


// Type Definitions ----------------------------------------------------------|

//
// Lth_TokenType
//
typedef enum Lth_TokenType
{
   Lth_TOK_None,
#define Lth_X(name) Lth_TOK_##name,
#include "Lth_token.h"
   Lth_TOK_EOF,
   Lth_TOK_Max
} Lth_TokenType;

//
// Lth_Token
//
typedef struct Lth_Token
{
   __prop get {call: Lth_TokenGet(__arg, this)}
   
   Lth_TokenType type;
   char         *str;
} Lth_Token;


// Extern Functions ----------------------------------------------------------|

char const *Lth_TokenName(Lth_TokenType type);

#endif//lithos3__Lth_token_h
