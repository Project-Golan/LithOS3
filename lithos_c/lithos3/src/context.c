//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Context functions.
//
//-----------------------------------------------------------------------------

#include "Lth.h"


// Extern Functions ----------------------------------------------------------|

//
// Lth_ContextNew
//
Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd)
{
   Lth_Context *ctx = calloc(1, sizeof(Lth_Context));

   ctx->scale = 1.0k;
   ctx->w = w;
   ctx->h = h;
   ctx->hid.cur = ctx->hid.base = hidBase;
   ctx->hid.end = hidEnd;

   ctx->rsrcBase = Lth_ManifestLoad_static(Lth_ManifestNew(
      Lth_Resource("Base.DefaultFont", "lithos_fs/Fonts/SmallFontJP.lthm")
   ));

   return ctx;
}

//
// Lth_ContextDestroy
//
void Lth_ContextDestroy(Lth_Context *ctx)
{
   if(ctx == NULL) return;

   Lth_ResourceMapDestroy(ctx->rsrc);
   Lth_ResourceMapDestroy(ctx->rsrcBase);

   free(ctx);
}

//
// Lth_ContextRun
//
void Lth_ContextRun(Lth_Context *ctx)
{
   Lth_Rect rect = ctx->clip.rects[ctx->clip.num];

   ACS_SetHudSize(ctx->w, ctx->h, true);
   ACS_SetHudClipRect(rect.x, rect.y, rect.w, rect.h);

   ctx->hid.cur = ctx->hid.base;
}

//
// Lth_ContextClipPush
//
void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h)
{
   Lth_Rect rect = ctx->clip.rects[ctx->clip.num++];

   if(!(rect.x == 0 && rect.y == 0 && rect.w == 0 && rect.h == 0))
   {
      if(rect.x < x)              rect.x = x;
      if(rect.y < y)              rect.y = y;
      if(rect.x + rect.w > x + w) rect.w = w;
      if(rect.y + rect.h > y + h) rect.h = h;
   }
   else
      rect = (Lth_Rect){ x, y, w, h };

   ctx->clip.rects[ctx->clip.num] = rect;
   ACS_SetHudClipRect(rect.x, rect.y, rect.w, rect.h);
}

//
// Lth_ContextClipPop
//
void Lth_ContextClipPop(Lth_Context *ctx)
{
   Lth_Rect rect = ctx->clip.rects[--ctx->clip.num];
   ACS_SetHudClipRect(rect.x, rect.y, rect.w, rect.h);
}

//
// Lth_ContextResource
//
void *Lth_ContextResource(Lth_Context *ctx, char const *key)
{
   void *p = NULL;
   if(ctx->rsrc) p = Lth_HashMapFind(&ctx->rsrc->map, key);
   if(p)         return p;
   else          return Lth_HashMapFind(&ctx->rsrcBase->map, key);
}

//
// Lth_ContextScale
//
void Lth_ContextScale(Lth_Context *ctx, _Accum s)
{
   ctx->scale = s;
   ACS_SetHudSize(ctx->w / ctx->scale, ctx->h / ctx->scale, true);
}

// EOF
