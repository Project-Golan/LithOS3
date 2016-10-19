//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Control functions.
//
// # of rewrites because of DavidPH: 2
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <stdlib.h>


// Extern Functions ----------------------------------------------------------|

//
// Lth_ControlFont
//
Lth_Font *Lth_ControlFont(void *ctrl_)
{
   Lth_Control *ctrl = ctrl_;

   if(ctrl->font)
      return ctrl->font;
   else
   {
      for(Lth_Control *p = ctrl->parent; p; p = p->parent)
      {
         if(p->font)
            return p->font;
      }
   }

   return ctrl->ctx->font;
}

//
// Lth_ControlRun
//
void Lth_ControlRun(void *ctrl_)
{
   Lth_Control *ctrl = ctrl_;

   Lth_assert(ctrl != NULL);

   Lth_ControlCall(ctrl, update,   ctrl);
   Lth_ControlCall(ctrl, draw,     ctrl);
   Lth_ControlCall(ctrl, postdraw, ctrl);
}

//
// Lth_ControlConnect
//
void Lth_ControlConnect(void *ctrl_, Lth_Signal signal, Lth_Callback_t cb)
{
   Lth_assert(ctrl_ != NULL);
   Lth_assert(signal < Lth_SIGMAX && signal >= 0);
   Lth_assert(cb != NULL);

   Lth_Control *ctrl = ctrl_;

   switch(signal)
   {
#define Lth_X(sig, name, ret, ...) \
   case Lth_##sig: \
      ctrl->cb.name.data = realloc(ctrl->cb.name.data, \
            sizeof(Lth_##sig##_t) * (ctrl->cb.name.size + 1)); \
      ctrl->cb.name.data[ctrl->cb.name.size++] = (Lth_##sig##_t)cb; \
      break;
#include "Lth_callback.h"
   }
}

//
// Lth_ControlDestroy
//
void Lth_ControlDestroy(void *ctrl_)
{
   if(ctrl_ == NULL) return;

   Lth_Control *ctrl = ctrl_;

   Lth_ListFor(Lth_Control *owner, ctrl->descendants)
   {
      Lth_ControlDestroy(owner);
      list = next;
   }

   Lth_CallReverse(ctrl->cb.destroy, ctrl);
   Lth_ListRemove(&ctrl->link);

#define Lth_X(sig, name, ret, ...) \
   free(ctrl->cb.name.data);
#include "Lth_callback.h"

   free(ctrl);
}

//
// Lth_ControlAttach
//
void Lth_ControlAttach(void *ctrlsrc_, void *ctrldst_)
{
   Lth_assert(ctrlsrc_ != NULL);
   Lth_assert(ctrldst_ != NULL);

   Lth_Control *ctrlsrc = ctrlsrc_, *ctrldst = ctrldst_;
   Lth_ListInsert(&ctrlsrc->link, ctrlsrc, &ctrldst->descendants);
   ctrlsrc->ctx = ctrldst->ctx;
}

// EOF
