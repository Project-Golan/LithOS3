//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Font layout handling.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_font_h
#define lithos3__Lth_font_h


// Type Definitions ----------------------------------------------------------|

//
// Lth_Glyph
//
typedef struct Lth_Glyph
{
   int w, h;
} Lth_Glyph;

//
// Lth_Font
//
typedef struct Lth_Font
{
   __str name;
   Lth_Glyph glyphs[126];
} Lth_Font;


// Extern Functions ----------------------------------------------------------|

Lth_Font *Lth_FontNew(char const *name);

#endif//lithos3__Lth_font_h
