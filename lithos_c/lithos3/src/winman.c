//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Window management.
//
//-----------------------------------------------------------------------------

#include "Lth.h"


// Static Functions ----------------------------------------------------------|

//
// WMFont
//
static Lth_Font *WMFont(Lth_Control *ctrl)
{
   Lth_WindowManager *wm = Lth_VirtControl;

   if(wm->font == NULL)
   {
      char const **name = Lth_ContextResource(wm->ctx, "Base.DefaultFont");
      if(name != NULL)
         wm->font = Lth_FontNew(*name);
   }

   return wm->font;
}


// Extern Functions ----------------------------------------------------------|

//
// Lth_WMNew
//
Lth_WindowManager *Lth_WMNew(Lth_Context *ctx)
{
   Lth_ControlInit(Lth_WindowManager);

   ctrl->vtable.getFont = WMFont;

   ctrl->lastmap.x  = ctrl->lastmap.y = -1;
   ctrl->mapspace.x = 24;
   ctrl->mapspace.y = 16;

   return ctrl;
}

//
// Lth_WMMap
//
void Lth_WMMap(Lth_WindowManager *wm, Lth_Window *ctrl)
{
   if(ctrl->x == -1) ctrl->x = wm->lastmap.x += wm->mapspace.x;
   else              wm->lastmap.x = ctrl->x;

   if(ctrl->y == -1) ctrl->y = wm->lastmap.y += wm->mapspace.y;
   else              wm->lastmap.y = ctrl->y;

   Lth_ControlAttachTail(wm, ctrl);
}

// EOF
