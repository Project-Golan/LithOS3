//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Token stream.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_tokenstream_h
#define lithos3__Lth_tokenstream_h

#include "Lth_token.h"

#include <stdbool.h>


// Type Definitions ----------------------------------------------------------|

//
// Lth_TokenStream
//
// internal data
//    fp
//    tokbuf
//    filled
//
// read-write
//    skipeol:    Skip line end tokens.
//    skipspc:    Skip whitespace tokens.
//
typedef struct Lth_TokenStream
{
   FILE     *fp;
   Lth_Token tokbuf;
   bool      filled;

   bool skipeol;
   bool skipspc;
} Lth_TokenStream;


// Extern Functions ----------------------------------------------------------|

Lth_TokenStream *Lth_TokenStreamOpen(void *data, size_t size);
void Lth_TokenStreamClose(Lth_TokenStream *stream);

Lth_Token const *Lth_TokenStreamBump(Lth_TokenStream *stream);
Lth_Token const *Lth_TokenStreamPeek(Lth_TokenStream *stream);
bool             Lth_TokenStreamDrop(Lth_TokenStream *stream, Lth_TokenType tt);

#endif//lithos3__Lth_tokenstream_h
