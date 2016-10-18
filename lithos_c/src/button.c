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
// Lth_ButtonDraw
//
static void Lth_ButtonDraw(Lth_Context *ctx, Lth_Button *ctrl)
{
   ACS_SetFont(s"CONFONT");
   Lth_PrintString(ctrl->label);
   Lth_HudMessagePlain(ctx->hid.cur--, ctrl->x - 8 + Lth_A_Lef,
      ctrl->y - 8 + Lth_A_Top);
   Lth_DrawRect(ctx, ctrl->x, ctrl->y, ctrl->w, ctrl->h, 0.5k);
}

//
// Lth_ButtonDestroy
//
static void Lth_ButtonDestroy(Lth_Button *ctrl)
{
   if(ctrl->label)
      free(ctrl->label);
}


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_ButtonNew
//
Lth_Button *Lth_ButtonNew(char const *label)
{
   Lth_Button *ctrl = calloc(1, sizeof(Lth_Button));
   Lth_assert(ctrl != NULL);

   Lth_ButtonSetLabel(ctrl, label);
   Lth_ControlConnect(ctrl, Lth_SIGDRAW, Lth_Callback(Lth_ButtonDraw));
   Lth_ControlConnect(ctrl, Lth_SIGDESTROY, Lth_Callback(Lth_ButtonDestroy));

   return ctrl;
}

//
// Lth_ButtonSetLabel
//
void Lth_ButtonSetLabel(Lth_Button *ctrl, char const *title)
{
   Lth_assert(ctrl != NULL);

   if(title != NULL)
      ctrl->label = Lth_strdup(title);
   else
      ctrl->label = Lth_strdup("");
}

// EOF
