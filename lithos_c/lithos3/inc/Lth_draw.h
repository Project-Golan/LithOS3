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

#define Lth_HudMessageBegin() ACS_BeginPrint()

#define Lth_TICK (0.029k) // One gametic, in seconds.

#define Lth_A_Cen (0.0k)
#define Lth_A_Lef (0.1k)
#define Lth_A_Rig (0.2k)
#define Lth_A_Top (0.1k)
#define Lth_A_Bot (0.2k)
#define Lth_A_TCe (0.4k)
#define Lth_A_TLe (0.5k)
#define Lth_A_TRi (0.6k)


// Extern Functions ----------------------------------------------------------|

Lth_OptArgs(1) void Lth_HudMessageEnd(Lth_Context *ctx, _Accum x, _Accum y, _Accum a);
Lth_OptArgs(1) void Lth_DrawSprite(Lth_Context *ctx, __str name, _Accum x, _Accum y, _Accum a);

void Lth_DrawRectAndClip(Lth_Context *ctx, int x, int y, int w, int h, _Accum alpha);
void Lth_DrawRect(Lth_Context *ctx, int x, int y, int w, int h, _Accum alpha);

#endif//lithos3__Lth_draw_h
