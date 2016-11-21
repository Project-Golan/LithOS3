//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Font rendering.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <stdlib.h>
#include <string.h>
#include "Lth_stdfix.h"

#define FontCheckASCII(rst) if((rst)->asciiPrint) FontRenderAPr((rst))


// Type Definitions ----------------------------------------------------------|

typedef struct FontRenderState
{
   Lth_Context *ctx;
   Lth_Font *font;
   bool asciiPrint;
   _Accum ax, ay;
   int x, y;
   int tmpx;
   int origx, origy;
} FontRenderState;


// Static Objects ------------------------------------------------------------|

static Lth_Glyph FontReplacementGlyph = {
   .fname = s"lithos_gfx/ReplacementCharacter.png",
   .ch = 0xFFFD,
   .mb = u8"�",
   .w = 32,
   .h = 32,
   .s = -1
};


// Static Functions ----------------------------------------------------------|

//
// ASCII Character
// Advance Line
// ASCII Print
// Advance Space
// Advance Tabulator
// Character
// Finish
// Glyph
// Return Line
// Wide Character
//
static void FontRenderACh(FontRenderState *rst, Lth_Glyph *glyph);
static void FontRenderALn(FontRenderState *rst);
static void FontRenderAPr(FontRenderState *rst);
static void FontRenderASp(FontRenderState *rst, int amt);
static void FontRenderATa(FontRenderState *rst);
static void FontRenderChr(FontRenderState *rst, wchar_t wc);
static void FontRenderFin(FontRenderState *rst);
static void FontRenderGly(FontRenderState *rst, Lth_Glyph *glyph);
static void FontRenderRLn(FontRenderState *rst);
static void FontRenderWCh(FontRenderState *rst, wchar_t wc, bool noascii);

//
// FontRenderACh
//
static void FontRenderACh(FontRenderState *rst, Lth_Glyph *glyph)
{
   if(!rst->asciiPrint)
   {
      Lth_HudMessageBegin();
      rst->asciiPrint = true;
   }

   rst->tmpx += glyph->w;
   ACS_PrintChar(glyph->ch);

#if Lth_DEBUG_FONTRUN
   printf("ASCII_CHAR[%c] ", glyph->ch);
#endif
}

//
// FontRenderALn
//
static void FontRenderALn(FontRenderState *rst)
{
   FontCheckASCII(rst);

   rst->y += rst->font->height;

#if Lth_DEBUG_FONTRUN
   printf("NEWLINE ");
#endif
}

//
// FontRenderAPr
//
static void FontRenderAPr(FontRenderState *rst)
{
   rst->asciiPrint = false;

   if(rst->font->baseName)
   {
      _Accum x = rst->x + rst->ax;
      _Accum y = rst->y + rst->ay;

#if Lth_DEBUG_FONTRUN
      printf("ASCII_PRINT[%.2k, %.2k] ", x, y);
#endif

      ACS_SetFont(rst->font->baseName);
      Lth_HudMessageEnd(rst->ctx, x, y);

      rst->x += rst->tmpx;
      rst->tmpx = 0;
   }
   else
   {
      __str s = ACS_EndStrParam();
      int len = ACS_StrLen(s);

      for(int i = 0; i < len; i++)
         FontRenderWCh(rst, s[i], true);
   }
}

//
// FontRenderASp
//
static void FontRenderASp(FontRenderState *rst, int amt)
{
   FontCheckASCII(rst);

   rst->x += rst->font->spaceWidth * amt;

#if Lth_DEBUG_FONTRUN
   printf("SPACE[%i] ", amt);
#endif
}

//
// FontRenderATa
//
static void FontRenderATa(FontRenderState *rst)
{
   FontCheckASCII(rst);

   int tabw = rst->font->spaceWidth * 8;
   rst->x = Lth_ceilk(rst->x / (_Accum)tabw) * tabw;

#if Lth_DEBUG_FONTRUN
   printf("TABULATOR ");
#endif
}

//
// FontRenderChr
//
static void FontRenderChr(FontRenderState *rst, wchar_t wc)
{
   switch(wc)
   {
   case L' ':   FontRenderASp(rst, 1);         break;
   case 0x3000: FontRenderASp(rst, 2);         break;
   case L'\t':  FontRenderATa(rst);            break;
   case L'\n':  FontRenderALn(rst);
   case L'\r':  FontRenderRLn(rst);            break;
   default:     FontRenderWCh(rst, wc, false); break;
   }
}

//
// FontRenderFin
//
static void FontRenderFin(FontRenderState *rst)
{
   FontCheckASCII(rst);

#if Lth_DEBUG_FONTRUN
   printf("DONE\n");
#endif
}

//
// FontRenderGly
//
static void FontRenderGly(FontRenderState *rst, Lth_Glyph *glyph)
{
   FontCheckASCII(rst);

   _Accum w = glyph->w;

   _Accum scale = 0;

   if(glyph->s != 0)
   {
      if(glyph->s < 0) scale = rst->font->height / (_Accum)glyph->h;
      else             scale = glyph->s;

      w *= scale;
   }

   if(scale)
      Lth_ContextScale(rst->ctx, scale);

   _Accum x = (rst->x + glyph->x) + rst->ax;
   _Accum y = (rst->y + glyph->y) + rst->ax;

#if Lth_DEBUG_FONTRUN
   printf("GLYPH[%s][%.2k, %.2k] ", glyph->mb, x, y);
#endif

   Lth_DrawSprite(rst->ctx, glyph->fname, x, y);

   if(scale)
      Lth_ContextScale(rst->ctx, 1);

   rst->x += w;
}

//
// FontRenderRLn
//
static void FontRenderRLn(FontRenderState *rst)
{
   FontCheckASCII(rst);

   rst->x = rst->origx;

#if Lth_DEBUG_FONTRUN
   printf("RET_LINE ");
#endif
}

//
// FontRenderWCh
//
static void FontRenderWCh(FontRenderState *rst, wchar_t wc, bool noascii)
{
   switch(rst->font->casing)
   {
   case Lth_Case_Both: default:                                 break;
   case Lth_Case_Uppr: if(wc >= L'a' && wc <= L'z') wc -= 0x20; break;
   case Lth_Case_Lowr: if(wc >= L'A' && wc <= L'Z') wc += 0x20; break;
   }

#if Lth_DEBUG_FONTRUN
   printf("CH ");
#endif

   Lth_Glyph        *glyph = Lth_HashMapFind(&rst->font->glyphs, wc);
   if(glyph == NULL) glyph = &FontReplacementGlyph;

   if(glyph->ch > 0x7F || noascii) FontRenderGly(rst, glyph);
   else                            FontRenderACh(rst, glyph);
}


// Extern Functions ----------------------------------------------------------|

//
// Lth_FontRunPlain
//
void Lth_FontRunPlain(Lth_Context *ctx, Lth_Font *font, int x, int y,
   int ax, int ay)
{
   if(font == NULL)
   {
      ACS_EndStrParam();
      return;
   }

   FontRenderState rst = {
      .ctx = ctx,
      .font = font,
      .x = x, .y = y,
      .origx = x, .origy = y
   };

   switch(ax)
   {
   default: case Lth_AX_Lef: rst.ax = 0.1k; break;
            case Lth_AX_Rig: rst.ax = 0.2k; break;
            case Lth_AX_Cen: rst.ax = 0.0k; break;
   }

   switch(ay)
   {
   default: case Lth_AY_Top: rst.ay = 0.1k; break;
            case Lth_AY_Bot: rst.ay = 0.2k; break;
            case Lth_AY_Cen: rst.ay = 0.0k; break;
   }

   char *str = Lth_strdup_str(ACS_EndStrParam());

   Lth_WithMbState()
      for(char const *sptr = str; *sptr;)
   {
      wchar_t wc;
      int     ret = mbrtowc(&wc, sptr, 4, &state);

#if Lth_DEBUG_FONTRUN
      printf("%i: ", ret);
#endif

      if(ret > 0) FontRenderChr(&rst, wc),                    sptr +=  ret;
      else        FontRenderGly(&rst, &FontReplacementGlyph), sptr += -ret;

#if Lth_DEBUG_FONTRUN
      printf("\n");
#endif
   }

   FontRenderFin(&rst);

   free(str);
}

// EOF
