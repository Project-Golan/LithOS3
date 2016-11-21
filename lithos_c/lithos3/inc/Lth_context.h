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
//    rsrcBase
//    rsrc
//
// read-only
//    scale: current draw scale
//    w:     width of screen
//    h:     height of screen
//
// read-write
//    hid:      HUD ID range
//
typedef struct Lth_Context
{
   struct { Lth_Rect rects[16]; size_t num; } clip;
   Lth_ResourceMap *rsrcBase, *rsrc;

   _Accum scale;
   int w, h;

   Lth_HIDRange hid;
} Lth_Context;


// Extern Functions ----------------------------------------------------------|

Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd);
void Lth_ContextDestroy(Lth_Context *ctx);
void Lth_ContextRun(Lth_Context *ctx);

void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h);
void Lth_ContextClipPop(Lth_Context *ctx);

void *Lth_ContextResource(Lth_Context *ctx, char const *key);

void Lth_ContextScale(Lth_Context *ctx, _Accum s);

#endif//lithos3__Lth_context_h
