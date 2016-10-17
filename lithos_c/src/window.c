//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Window functions.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <stdlib.h>


//----------------------------------------------------------------------------|
// Static Functions                                                           |
//

//
// Lth_WindowDraw
//
static void Lth_WindowDraw(Lth_Context *ctx, Lth_Window *ctrl)
{
   ACS_SetFont(s"CONFONT");
   Lth_PrintString(ctrl->title);
   Lth_HudMessagePlain(ctx->hid.cur--, ctrl->x - 8 + Lth_A_Lef,
      ctrl->y - 8 + Lth_A_Top);
   Lth_DrawRectAndClip(ctx, ctrl->x, ctrl->y, ctrl->w, ctrl->h, 0.5k);
}

//
// Lth_WindowPostDraw
//
static void Lth_WindowPostDraw(Lth_Context *ctx, Lth_Window *ctrl)
{
   Lth_ContextClipPop(ctx);
}

//
// Lth_WindowDestroy
//
static void Lth_WindowDestroy(Lth_Window *ctrl)
{
   if(ctrl->title)
      free(ctrl->title);
}


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_WindowNew
//
Lth_Window *Lth_WindowNew(char const *title, int w, int h, int x, int y)
{
   Lth_Window *ctrl = calloc(1, sizeof(Lth_Window));
   Lth_assert(ctrl != NULL);

   ctrl->w = w;
   ctrl->h = h;
   ctrl->x = x;
   ctrl->y = y;

   Lth_WindowSetTitle(ctrl, title);
   Lth_ControlConnect(ctrl, Lth_SIGDRAW, Lth_Callback(Lth_WindowDraw));
   Lth_ControlConnect(ctrl, Lth_SIGPSTDRAW, Lth_Callback(Lth_WindowPostDraw));
   Lth_ControlConnect(ctrl, Lth_SIGDESTROY, Lth_Callback(Lth_WindowDestroy));

   return ctrl;
}

//
// Lth_WindowSetTitle
//
void Lth_WindowSetTitle(Lth_Window *ctrl, char const *title)
{
   Lth_assert(ctrl != NULL);

   if(title != NULL)
      ctrl->title = Lth_strdup(title);
   else
      ctrl->title = Lth_strdup("<untitled>");
}

// EOF
