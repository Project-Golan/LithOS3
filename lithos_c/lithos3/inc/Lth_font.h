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

#define Lth_FontRunBegin() ACS_BeginPrint()


// Type Definitions ----------------------------------------------------------|

struct Lth_Context;

enum
{
   Lth_AX_Lef = 1,
   Lth_AX_Rig,
   Lth_AX_Cen,

   Lth_AY_Top = 1,
   Lth_AY_Bot,
   Lth_AY_Cen
};

//
// Lth_FontCasing
//
typedef enum Lth_FontCasing
{
   Lth_Case_Both,
   Lth_Case_Uppr,
   Lth_Case_Lowr
} Lth_FontCasing;

//
// Lth_GlyphLookupType
//
typedef enum Lth_GlyphLookupType
{
   Lth_GT_Chara,
   Lth_GT_Codep,
   Lth_GT_Digit
} Lth_GlyphLookupType;

//
// Lth_Glyph
//
typedef struct Lth_Glyph
{
   Lth_Inherits(Lth_Rect);
   __str   fname;
   _Accum  s;
   wchar_t ch;
   char    mb[MB_CUR_MAX + 1];
} Lth_Glyph;

//
// Lth_Font
//
typedef struct Lth_Font
{
   Lth_FontCasing casing;
   __str baseName;
   int   spaceWidth;
   int   height;
   __str fnamePref;
   __str fnameSuff;
   Lth_HashMap           glyphs;
   Lth_Vector(Lth_Glyph) glyphV;
} Lth_Font;


// Extern Functions ----------------------------------------------------------|

Lth_ScriptCall Lth_Font *Lth_FontNew(char const *fname);
void Lth_FontDestroy(Lth_Font *font);

Lth_OptArgs(2) void Lth_FontRunPlain(struct Lth_Context *ctx, Lth_Font *font, int x, int y, int ax, int ay);

#endif//lithos3__Lth_font_h
