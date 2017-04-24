//-----------------------------------------------------------------------------
//
// Copyright © 2016-2017 Project Golan
//
// See "LICENSE.lithos3" for more information.
//
//-----------------------------------------------------------------------------
//
// Token stream.
//
//-----------------------------------------------------------------------------

#include "Lth_libinfo.h"

#if !defined(lithos3__Lth_tokenstream_h) && !LITHOS3_NO_TOKENSTREAM
#define lithos3__Lth_tokenstream_h

#include "Lth_token.h"

#include <stdio.h>


// Extern Functions ----------------------------------------------------------|

struct Lth_TokenStream *Lth_TokenStreamOpen(void *data, size_t size);
void Lth_TokenStreamClose(struct Lth_TokenStream *stream);

Lth_Token const *Lth_TokenStreamBump(struct Lth_TokenStream *stream);
Lth_Token const *Lth_TokenStreamPeek(struct Lth_TokenStream *stream);
bool             Lth_TokenStreamDrop(struct Lth_TokenStream *stream, Lth_TokenType tt);


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
//    skipeol: Skip line end tokens.   Defaults to true.
//    skipspc: Skip whitespace tokens. Defaults to true.
//
typedef struct Lth_TokenStream
{
   __prop close {call: Lth_TokenStreamClose(this)}
   __prop bump  {call: Lth_TokenStreamBump(this)}
   __prop peek  {call: Lth_TokenStreamPeek(this)}
   __prop drop  {call: Lth_TokenStreamDrop(this)}
   
   FILE     *fp;
   Lth_Token tokbuf;
   bool      filled;

   bool skipeol;
   bool skipspc;
} Lth_TokenStream;

#endif//lithos3__Lth_tokenstream_h
