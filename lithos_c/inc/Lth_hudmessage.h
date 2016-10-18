//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// HudMessage macros.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_hudmessage_h
#define lithos3__Lth_hudmessage_h

#include <ACS_ZDoom.h>
#include <stdio.h>
#include <stdarg.h>

#define Lth_HudMessageFont(font, ...) \
   ( \
      ACS_SetFont(font), \
      Lth_HudMessage(__VA_ARGS__) \
   )

#define Lth_HudMessageParams(flags, id, tr, x, y, ...) \
   ( \
      ACS_OptHudMessage((flags) | HUDMSG_NOTWITHFULLMAP, id, tr, x, y, \
         Lth_TICK), \
      ACS_EndHudMessage(__VA_ARGS__) \
   )

#define Lth_HudMessagePlain(id, x, y) \
   ( \
      ACS_OptHudMessage(HUDMSG_PLAIN | HUDMSG_NOTWITHFULLMAP, id, \
         CR_UNTRANSLATED, x, y, Lth_TICK), \
      ACS_EndHudMessage() \
   )

#define Lth_HudMessageFade(id, x, y, fadetime) \
   ( \
      ACS_OptHudMessage(HUDMSG_FADEOUT | HUDMSG_NOTWITHFULLMAP, id, \
         CR_UNTRANSLATED, x, y, Lth_TICK), \
      ACS_EndHudMessage(fadetime) \
   )

#define Lth_DrawSprite(name, flags, id, x, y, ...) \
   ( \
      ACS_SetFont(name), \
      ACS_PrintChar('A'), \
      Lth_HudMessageParams((flags) | HUDMSG_NOTWITHFULLMAP, id, \
         CR_UNTRANSLATED, x, y, __VA_ARGS__) \
   )

#define Lth_DrawSpriteFade(name, id, x, y, fadetime) \
   ( \
      ACS_SetFont(name), \
      ACS_PrintChar('A'), \
      Lth_HudMessageFade(id, x, y, fadetime) \
   )

#define Lth_DrawSpritePlain(name, id, x, y) \
   ( \
      ACS_SetFont(name), \
      ACS_PrintChar('A'), \
      Lth_HudMessagePlain(id, x, y) \
   )

#define Lth_DrawSpriteAlpha(name, id, x, y, alpha) \
   ( \
      ACS_SetFont(name), \
      ACS_PrintChar('A'), \
      Lth_HudMessageParams(HUDMSG_ALPHA, id, CR_UNTRANSLATED, x, y, alpha) \
   )

#define Lth_TICK (0.029k) // One tick, in seconds.

#define Lth_A_Cen  (0.0k)
#define Lth_A_Lef  (0.1k)
#define Lth_A_Rig  (0.2k)
#define Lth_A_Top  (0.1k)
#define Lth_A_Bot  (0.2k)
#define Lth_A_TCen (0.4k)
#define Lth_A_TLef (0.5k)
#define Lth_A_TRig (0.6k)


// Static Functions ----------------------------------------------------------|

//
// Lth_HudMessage
//
static inline void Lth_HudMessage(char const *fmt, ...)
{
   va_list vl;
   
   ACS_BeginPrint();
   
   va_start(vl, fmt);
   __vnprintf(fmt, vl);
   va_end(vl);
   
   ACS_MoreHudMessage();
}

#endif//lithos3__Lth_hudmessage_h
