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


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_ContextNew
//
Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd)
{
   Lth_Context *ctx = calloc(1, sizeof(Lth_Context));
   Lth_assert(ctx != NULL);

   ctx->w = w;
   ctx->h = h;
   ctx->hid.cur = ctx->hid.base = hidBase;
   ctx->hid.end = hidEnd;

   return ctx;
}

//
// Lth_ContextMap
//
void Lth_ContextMap(Lth_Context *ctx, Lth_Window *window)
{
   Lth_assert(ctx != NULL);
   Lth_assert(window != NULL);

   // TODO: should use last window's position + some divisor of screenspace
   if(window->x == -1) window->x = ctx->w / 2;
   if(window->y == -1) window->y = ctx->h / 2;

   if(ctx->map)
      Lth_LinkListInsert(&window->desclink, window, &ctx->map);
   else
   {
      ctx->map = &window->desclink;
      ctx->map->owner = window;
   }
}

//
// Lth_ContextDestroy
//
void Lth_ContextDestroy(Lth_Context *ctx)
{
   if(ctx == NULL)
      return;

   if(ctx->map)
   {
      for(Lth_LinkList *list = ctx->map; list;)
      {
         Lth_LinkList *next = list->next;
         Lth_Control *owner = list->owner;
         Lth_LinkListRemove(list);
         if(owner) Lth_ControlDestroy(owner);
         list = next;
      }
   }

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

   if(ctx->map)
      for(Lth_LinkList *list = ctx->map; list; list = list->next)
         Lth_ControlRun(ctx, list->owner);
}

//
// Lth_ContextClipPush
//
void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h)
{
   Lth_assert(ctx != NULL);

   ctx->clip.rects[++ctx->clip.num] = (Lth_Rect){ x, y, w, h };
   ACS_SetHudClipRect(x, y, w, h);
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

// EOF
