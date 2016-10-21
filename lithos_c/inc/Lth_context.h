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
#include "Lth_manifest.h"

#define Lth_ContextResource(ctx, type, key) \
   ((type *)Lth_ContextResourceFind((ctx), (key)))

#define Lth_ContextManifestLoad_extern(ctx, ...) \
   ( \
      ((ctx)->rsrc ? (Lth_ResourceMapDestroy((ctx)->rsrc)) : (void)0), \
      (ctx)->rsrc = Lth_ManifestLoad_extern(__VA_ARGS__) \
   )

#define Lth_ContextManifestLoad_static(ctx, ...) \
   ( \
      ((ctx)->rsrc ? (Lth_ResourceMapDestroy((ctx)->rsrc)) : (void)0), \
      (ctx)->rsrc = Lth_ManifestLoad_static(__VA_ARGS__) \
   )


// Type Definitions ----------------------------------------------------------|

//
// Lth_Context
//
// internal data
//    clip
//    map
//    rsrcBase
//    rsrc
//    lastmap
//
// read-only
//    w:    width of screen
//    h:    height of screen
//
// read-write
//    hid:      HUD ID range
//    mapspace: space between newly mapped windows that are auto-positioned
//    font:     default font for drawing
//
typedef struct Lth_Context
{
   struct { Lth_Rect rects[16]; int num; } clip;
   struct { Lth_LinkList *head, *tail; }   map;
   Lth_ResourceMap *rsrcBase, *rsrc;
   Lth_IVec2 lastmap;

   int w, h;

   Lth_HIDRange hid;
   Lth_IVec2    mapspace;
   Lth_Font    *font;
} Lth_Context;


// Extern Functions ----------------------------------------------------------|

Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd);
void Lth_ContextDestroy(Lth_Context *ctx);
void Lth_ContextRun(Lth_Context *ctx);

void Lth_ContextMap(Lth_Context *ctx, struct Lth_Window *window);

void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h);
void Lth_ContextClipPop(Lth_Context *ctx);

void *Lth_ContextResourceFind(Lth_Context *ctx, char const *key);

#endif//lithos3__Lth_context_h
