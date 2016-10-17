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
static void Lth_WindowDraw(Lth_Context *ctx, Lth_Window *window)
{
   Lth_DrawRect(ctx, window->x, window->y, window->w, window->h, 0.5k);
   ACS_SetFont(s"CONFONT");
   Lth_PrintString(window->title);
   Lth_HudMessagePlain(ctx->hid.cur--, window->x - 8 + Lth_A_Lef,
      window->y - 8 + Lth_A_Top);
}


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_WindowNew
//
Lth_Window *Lth_WindowNew(char const *title, int w, int h, int x, int y)
{
   Lth_Window *control = calloc(1, sizeof(Lth_Window));
   Lth_assert(control != NULL);

   control->w = w;
   control->h = h;
   control->x = x;
   control->y = y;

   Lth_WindowSetTitle(control, title);
   Lth_ControlConnect(control, Lth_SIGDRAW, Lth_Callback(Lth_WindowDraw));

   return control;
}

//
// Lth_WindowSetTitle
//
void Lth_WindowSetTitle(Lth_Window *control, char const *title)
{
   Lth_assert(control != NULL);

   if(title != NULL)
      control->title = Lth_strdup(title);
   else
      control->title = Lth_strdup("<untitled>");
}

// EOF
