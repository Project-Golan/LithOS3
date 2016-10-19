//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Context for drawing.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_context_h
#define lithos3__Lth_context_h

#include "Lth_types.h"
#include "Lth_font.h"


// Type Definitions ----------------------------------------------------------|

//
// Lth_Context
//
// internal data
//    clip
//    lastmap
//    map
//
// read-only
//    w: width of screen
//    h: height of screen
//
// read-write
//    hid:      HUD ID range
//    mapspace: space between newly mapped windows that are auto-positioned
//    font:     default font for drawing
//
typedef struct Lth_Context
{
   struct { Lth_Rect rects[16]; int num; } clip;
   struct { Lth_LinkList *head, *tail; } map;
   Lth_IVec2 lastmap;

   int w, h;

   Lth_HIDRange hid;
   Lth_IVec2    mapspace;
   Lth_Font    *font;
} Lth_Context;


// Extern Functions ----------------------------------------------------------|

Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd);
void Lth_ContextMap(Lth_Context *ctx, struct Lth_Window *window);
void Lth_ContextDestroy(Lth_Context *ctx);
void Lth_ContextRun(Lth_Context *ctx);
void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h);
void Lth_ContextClipPop(Lth_Context *ctx);

#endif//lithos3__Lth_context_h
