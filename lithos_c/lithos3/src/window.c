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


// Static Functions ----------------------------------------------------------|

//
// Lth_WindowDraw
//
static void Lth_WindowDraw(Lth_Window *ctrl)
{
   Lth_DrawRectAndClip(ctrl->ctx, ctrl->x, ctrl->y, ctrl->w, 8, 0.35k);

   Lth_FontRunBegin();
   Lth_PrintString(ctrl->title);
   Lth_ControlFontRunPlain(ctrl, ctrl->x, ctrl->y);

   Lth_ContextClipPop(ctrl->ctx);

   Lth_DrawRectAndClip(ctrl->ctx, ctrl->x, ctrl->y + 8, ctrl->w, ctrl->h, 0.5k);
}

//
// Lth_WindowDrawPost
//
static void Lth_WindowDrawPost(Lth_Window *ctrl)
{
   Lth_ContextClipPop(ctrl->ctx);
}

//
// Lth_WindowDestroy
//
static void Lth_WindowDestroy(Lth_Window *ctrl)
{
   if(ctrl->title)
      free(ctrl->title);
}


// Extern Functions ----------------------------------------------------------|

//
// Lth_WindowNew
//
Lth_Window *Lth_WindowNew(Lth_Context *ctx, char const *title, int x, int y, int w, int h)
{
   Lth_ControlInit(Lth_Window);

   ctrl->x = x;
   ctrl->y = y;
   ctrl->w = w;
   ctrl->h = h;

   Lth_WindowSetTitle(ctrl, title);
   Lth_ControlConnect(ctrl, Lth_SigDraw,    Lth_Callback(Lth_WindowDraw));
   Lth_ControlConnect(ctrl, Lth_SigDrawPst, Lth_Callback(Lth_WindowDrawPost));
   Lth_ControlConnect(ctrl, Lth_SigDestroy, Lth_Callback(Lth_WindowDestroy));

   return ctrl;
}

//
// Lth_WindowSetTitle
//
void Lth_WindowSetTitle(Lth_Window *ctrl, char const *title)
{
   if(title != NULL)
      ctrl->title = Lth_strdup(title);
   else
      ctrl->title = Lth_strdup("<untitled>");
}

// EOF
