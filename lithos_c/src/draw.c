//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Context drawing functions.
//
//-----------------------------------------------------------------------------

#include "Lth.h"


// Extern Functions ----------------------------------------------------------|

//
// Lth_HudMessageEnd
//
void Lth_HudMessageEnd(Lth_Context *ctx, _Accum x, _Accum y, _Accum a)
{
   int flags = HUDMSG_PLAIN | HUDMSG_NOTWITHFULLMAP;

   if(ctx->scale != 1)
   {
      long _Accum xn = (int)x / (long _Accum)ctx->w;
      long _Accum yn = (int)y / (long _Accum)ctx->h;
      x = (xn * (ctx->w / ctx->scale)) + Lth_fractk(x);
      y = (yn * (ctx->h / ctx->scale)) + Lth_fractk(y);
   }

   if(a) flags |= HUDMSG_ALPHA;

   ACS_MoreHudMessage();
   ACS_OptHudMessage(flags, ctx->hid.cur--, CR_UNTRANSLATED, x, y, Lth_TICK);
   if(a) ACS_EndHudMessage(a);
   else  ACS_EndHudMessage();
}

//
// Lth_DrawSprite
//
void Lth_DrawSprite(Lth_Context *ctx, __str name, _Accum x, _Accum y, _Accum a)
{
   ACS_SetFont(name);

   Lth_HudMessageBegin();
   ACS_PrintChar('A');
   Lth_HudMessageEnd(ctx, x, y, a);
}

//
// Lth_DrawRectAndClip
//
void Lth_DrawRectAndClip(Lth_Context *ctx, int x, int y, int w, int h,
   _Accum alpha)
{
   Lth_ContextClipPush(ctx, x, y, w, h);

   for(int ix = 0; ix < w; ix += 128)
      for(int iy = 0; iy < h; iy += 128)
         Lth_DrawSprite(ctx, s"lithos_gfx/Base/Black128.png",
            x + ix + Lth_A_Lef, y + iy + Lth_A_Top, alpha);
}

//
// Lth_DrawRect
//
void Lth_DrawRect(Lth_Context *ctx, int x, int y, int w, int h, _Accum alpha)
{
   Lth_DrawRectAndClip(ctx, x, y, w, h, alpha);
   Lth_ContextClipPop(ctx);
}

// EOF
