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
//
typedef struct Lth_Context
{
   struct { Lth_Rect rects[16]; int num; } clip;
   struct { int x, y; } lastmap;
   struct { Lth_LinkList *head, *tail; } map;

   int w, h;

   Lth_HIDRange hid;
   struct { int x, y; } mapspace;
} Lth_Context;


// Extern Functions ----------------------------------------------------------|

Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd);
void Lth_ContextMap(Lth_Context *ctx, struct Lth_Window *window);
void Lth_ContextDestroy(Lth_Context *ctx);
void Lth_ContextRun(Lth_Context *ctx);
void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h);
void Lth_ContextClipPop(Lth_Context *ctx);

#endif//lithos3__Lth_context_h
