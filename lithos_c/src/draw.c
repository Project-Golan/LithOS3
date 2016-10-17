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


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

void Lth_DrawRect(Lth_Context *ctx, int x, int y, int w, int h, __fixed alpha)
{
   Lth_assert(ctx != NULL);

   Lth_ContextClipPush(ctx, x, y, w, h);

   for(int ix = 0; ix < w; ix += 128)
      for(int iy = 0; iy < h; iy += 128)
         Lth_DrawSpriteAlpha(s"lithos_gfx/Base/Black128.png", ctx->hid.cur--,
            x + ix, y + iy, alpha);

   Lth_ContextClipPop(ctx);
}

// EOF
