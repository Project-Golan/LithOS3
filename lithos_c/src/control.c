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


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_ControlRun
//
void Lth_ControlRun(Lth_Context *ctx, void *ctrl_)
{
   Lth_assert(ctx != NULL);
   Lth_assert(ctrl_ != NULL);

   Lth_Control *ctrl = ctrl_;

   Lth_ControlCall(ctrl, update,   ctx, ctrl);
   Lth_ControlCall(ctrl, draw,     ctx, ctrl);
   Lth_ControlCall(ctrl, postdraw, ctx, ctrl);
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
   Lth_LinkListRemove(&ctrl->desclink);

#define Lth_X(sig, name, ret, ...) \
   free(ctrl->cb.name.data);
#include "Lth_callback.h"

   free(ctrl);
}


// EOF
