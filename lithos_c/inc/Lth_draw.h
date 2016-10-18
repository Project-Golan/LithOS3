//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Drawing.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_draw_h
#define lithos3__Lth_draw_h


// Extern Functions ----------------------------------------------------------|

void Lth_DrawRectAndClip(Lth_Context *ctx, int x, int y, int w, int h, __fixed alpha);
void Lth_DrawRect(Lth_Context *ctx, int x, int y, int w, int h, __fixed alpha);

#endif//lithos3__Lth_draw_h
