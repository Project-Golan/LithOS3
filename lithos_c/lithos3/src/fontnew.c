//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Font creation.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <stdlib.h>
#include <string.h>
#include <setjmp.h>

#define GenFontData() \
   char const **base       = Lth_HashMapFind(&rsrc->map, "Font.Base"); \
   char const **casing     = Lth_HashMapFind(&rsrc->map, "Font.Case"); \
   char const **extraDir   = Lth_HashMapFind(&rsrc->map, "Font.ExtraDir"); \
   char const **glyphList  = Lth_HashMapFind(&rsrc->map, "Font.Glyphs"); \
   int  const  *height     = Lth_HashMapFind(&rsrc->map, "Font.Height"); \
   char const **prefix     = Lth_HashMapFind(&rsrc->map, "Font.Prefix"); \
   int  const  *spaceWidth = Lth_HashMapFind(&rsrc->map, "Font.SpaceWidth"); \
   char const **suffix     = Lth_HashMapFind(&rsrc->map, "Font.Suffix"); \
   char const **typeStr    = Lth_HashMapFind(&rsrc->map, "Font.Type");

#define FontError(err) \
   if(1) \
   { \
      fprintf(stderr, "%s: %s\n", __func__, err); \
      longjmp(FontJmpBuf, FontJmpBufToken); \
   } \
   else ((void)0)


// Static Objects ------------------------------------------------------------|

static jmp_buf FontJmpBuf;
static int const FontJmpBufToken = 31;


// Static Functions ----------------------------------------------------------|

//
// FontValidate
//
static void FontValidate(Lth_ResourceMap *rsrc)
{
   GenFontData();

   if(!glyphList)         FontError("Font definition must have a glyph list.");
   if(!base && !extraDir) FontError("Font definition doesn't have a font.");
   if(!height)            FontError("Font definition doesn't have a height.");
}

//
// FontLoadGlyphs
//
static void FontLoadGlyphs(Lth_Font volatile *font, Lth_ResourceMap *rsrc,
   int type)
{
   char const **glyphList = Lth_HashMapFind(&rsrc->map, "Font.Glyphs");

   wchar_t *tmpkey = Lth_wcsdup(L"Font.GlyphData. _ ");
   wchar_t *keyl =  wcschr(tmpkey, ' ');
   wchar_t *keyr = wcsrchr(tmpkey, ' ');

   __with(mbstate_t   state; size_t i = 0; memset(&state, 0, sizeof(state));)
      for(char const *sptr = *glyphList; *sptr; i++)
   {
      wchar_t wc;
      int     ret = mbrtowc(&wc, sptr, 4, &state);
      if(ret <= 0) FontError("Error parsing Unicode sequence.");

      Lth_Glyph glyph = { .ch = wc };
      memmove(glyph.mb, sptr, ret);

                  (*keyl = wc);
      int    *x = (*keyr = 'x', Lth_HashMapFind(&rsrc->map, tmpkey));
      int    *y = (*keyr = 'y', Lth_HashMapFind(&rsrc->map, tmpkey));
      int    *w = (*keyr = 'w', Lth_HashMapFind(&rsrc->map, tmpkey));
      int    *h = (*keyr = 'h', Lth_HashMapFind(&rsrc->map, tmpkey));
      _Accum *s = (*keyr = 's', Lth_HashMapFind(&rsrc->map, tmpkey));

      if(x) glyph.x = *x;
      if(y) glyph.y = *y;
      if(w) glyph.w = *w;
      if(h) glyph.h = *h;
      if(s) glyph.s = *s;

      if(wc > 0x7F)
      {
         ACS_BeginPrint();

         ACS_PrintString(font->fnamePref);

         switch(type)
         {
         case Lth_GT_Chara: Lth_PrintString(glyph.mb); break;
         case Lth_GT_Codep:    ACS_PrintHex(glyph.ch); break;
         case Lth_GT_Digit:    ACS_PrintInt(glyph.ch); break;
         }

         ACS_PrintString(font->fnameSuff);

         glyph.fname = ACS_EndStrParam();
      }

      font->glyphV.data[i]              = glyph;
      font->glyphs.elem.data[i].keyhash = (size_t)wc;
      font->glyphs.elem.data[i].value   = &font->glyphV.data[i];

      sptr += ret;
   }

   free(tmpkey);

   Lth_HashMapBuild((Lth_HashMap *)&font->glyphs);
}

//
// FontSetup
//
static void FontSetup(Lth_Font volatile *font, Lth_ResourceMap *rsrc)
{
   GenFontData();

   int type;

   if(typeStr)
           if(Lth_stricmp(*typeStr, "Character") == 0) type = Lth_GT_Chara;
      else if(Lth_stricmp(*typeStr, "Codepoint") == 0) type = Lth_GT_Codep;
      else if(Lth_stricmp(*typeStr, "Digit")     == 0) type = Lth_GT_Digit;
      else FontError("Invalid Font.Type");
   else
      type = Lth_GT_Chara;

   font->height = *height;

   if(base)
      font->baseName = Lth_strentdup(*base);

   if(extraDir)
   {
      ACS_BeginPrint();

      Lth_PrintString(*extraDir);

      if((*extraDir)[strlen(*extraDir)] != '/')
         ACS_PrintChar('/');

      if(prefix)
         Lth_PrintString(*prefix);

      font->fnamePref = ACS_EndStrParam();

      if(suffix) font->fnameSuff = Lth_strentdup(*suffix);
      else       font->fnameSuff = s".png";
   }

   if(spaceWidth) font->spaceWidth = *spaceWidth;
   else           font->spaceWidth = 4;

   if(casing)
      if(Lth_stricmp(*casing, "Both") == 0)
         font->casing = Lth_Case_Both;
      else if(Lth_stricmp(*casing, "UpperOnly") == 0)
         font->casing = Lth_Case_Uppr;
      else if(Lth_stricmp(*casing, "LowerOnly") == 0)
         font->casing = Lth_Case_Lowr;
      else
         FontError("Invalid Font.Case");
   else
      font->casing = Lth_Case_Both;

   font->glyphV.size = Lth_mbslen(*glyphList);
   Lth_HashMapAlloc((Lth_HashMap *)&font->glyphs, font->glyphV.size);
   Lth_VectorAlloc(Lth_Glyph, font->glyphV);

   FontLoadGlyphs(font, rsrc, type);
}

//
// FontPrint
//
// [debug] Print characters out.
//
Lth_ScriptCall static void FontPrint(Lth_Font *font)
{
   for(size_t i = 0; i < font->glyphs.elem.size; i++)
      __with(Lth_Glyph *glyph = font->glyphs.elem.data[i].value;)
         printf("glyph %X (%s)\t\tx: %i\ty: %i\tw: %i\n",
            glyph->ch, glyph->mb, glyph->x, glyph->y, glyph->w);
}


// Extern Functions ----------------------------------------------------------|

//
// Lth_FontNew
//
Lth_ScriptCall Lth_Font *Lth_FontNew(char const *fname)
{
   Lth_Font volatile *font = NULL;
   Lth_ResourceMap   *rsrc = NULL;

   // Set up error handler.
   if(setjmp(FontJmpBuf) == FontJmpBufToken)
   {
      if(font) Lth_FontDestroy((Lth_Font *)font);
      if(rsrc) Lth_ResourceMapDestroy(rsrc);

      return NULL;
   }

   rsrc = Lth_ManifestLoad_extern(fname);

   if(rsrc == NULL)
      FontError("Couldn't load resource manifest.");

   FontValidate(rsrc);

   font = calloc(1, sizeof(Lth_Font));

   if(font == NULL)
      FontError("Failed to allocate font.");

   FontSetup(font, rsrc);

   Lth_ResourceMapDestroy(rsrc);

   return (Lth_Font *)font;
}

//
// Lth_FontDestroy
//
void Lth_FontDestroy(Lth_Font *font)
{
   if(font == NULL) return;

   Lth_HashMapDestroy(&font->glyphs);
   free(font->glyphV.data);
   free(font);
}

// EOF
