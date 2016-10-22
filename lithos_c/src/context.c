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

#include <ACS_ZDoom.h>
#include <stdlib.h>
#include <stdbool.h>


// Static Functions ----------------------------------------------------------|

//
// Lth_ContextSetup
//
static void Lth_ContextSetup(Lth_Context *ctx, void *ctrl_)
{
   Lth_Control *ctrl = ctrl_;

   Lth_ListForEach(Lth_Control *owner, ctrl->descendants)
      Lth_ContextSetup(ctx, owner);

   ctrl->ctx = ctx;
}


// Extern Functions ----------------------------------------------------------|

//
// Lth_ContextNew
//
Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd)
{
   Lth_Context *ctx = calloc(1, sizeof(Lth_Context));
   Lth_assert(ctx != NULL);

   ctx->w = w;
   ctx->h = h;
   ctx->lastmap.x = ctx->lastmap.y = -1;
   ctx->hid.cur = ctx->hid.base = hidBase;
   ctx->hid.end = hidEnd;
   ctx->mapspace.x = 24;
   ctx->mapspace.y = 16;

   ctx->rsrcBase = Lth_ManifestLoad_static(Lth_ManifestNew(
      Lth_Resource("Base.Resource1", 999)
   ));

   return ctx;
}

//
// Lth_ContextDestroy
//
void Lth_ContextDestroy(Lth_Context *ctx)
{
   if(ctx == NULL)
      return;

   if(ctx->map.head)
   {
      Lth_ListFor(Lth_Control *owner, ctx->map.head)
      {
         Lth_ListRemove(list);
         if(owner) Lth_ControlDestroy(owner);
         list = next;
      }
   }

   Lth_ResourceMapDestroy(ctx->rsrc);
   Lth_ResourceMapDestroy(ctx->rsrcBase);

   free(ctx);
}

//
// Lth_ContextRun
//
void Lth_ContextRun(Lth_Context *ctx)
{
   Lth_assert(ctx != NULL);

   ACS_SetHudSize(ctx->w, ctx->h, true);
   ctx->hid.cur = ctx->hid.base;

   if(ctx->map.head)
      Lth_ListForEach(Lth_Control *owner, ctx->map.head)
         Lth_ControlRun(owner);
}

//
// Lth_ContextMap
//
void Lth_ContextMap(Lth_Context *ctx, Lth_Window *ctrl)
{
   Lth_assert(ctx != NULL);
   Lth_assert(ctrl != NULL);

   if(ctrl->x == -1) ctrl->x = ctx->lastmap.x += ctx->mapspace.x;
   else              ctx->lastmap.x = ctrl->x;

   if(ctrl->y == -1) ctrl->y = ctx->lastmap.y += ctx->mapspace.y;
   else              ctx->lastmap.y = ctrl->y;

   Lth_ContextSetup(ctx, ctrl);
   Lth_ListInsertTail(&ctrl->link, ctrl, &ctx->map.head, &ctx->map.tail);
}

//
// Lth_ContextClipPush
//
void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h)
{
   Lth_assert(ctx != NULL);

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
   Lth_assert(ctx != NULL);

   Lth_Rect rect = ctx->clip.rects[--ctx->clip.num];
   ACS_SetHudClipRect(rect.x, rect.y, rect.w, rect.h);
}

//
// Lth_ContextResource
//
void *Lth_ContextResource(Lth_Context *ctx, char const *key)
{
   void *p = Lth_HashMapFind(&ctx->rsrc->map, key);
   if(p) return p;
   else  return Lth_HashMapFind(&ctx->rsrcBase->map, key);
}

// EOF
