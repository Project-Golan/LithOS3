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
// Lth_ControlRun
//
void Lth_ControlRun(void *ctrl_)
{
   Lth_Control *ctrl = ctrl_;

   Lth_ListForEach(Lth_Control *owner, ctrl->descHead)
      Lth_ControlRun(owner);

   Lth_Call(ctrl->cb.update,   ctrl);
   Lth_Call(ctrl->cb.draw,     ctrl);
   Lth_Call(ctrl->cb.drawpost, ctrl);
}

//
// Lth_ControlConnect
//
void Lth_ControlConnect(void *ctrl_, Lth_Signal signal, Lth_Callback_t cb)
{
   Lth_assert(signal < Lth_SIGMAX && signal >= 0);

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

   Lth_ListFor(Lth_Control *owner, ctrl->descHead)
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
void Lth_ControlAttach(void *ctrl_, void *ctrlS_)
{
   Lth_Control *ctrl = ctrl_, *ctrlS = ctrlS_;
   Lth_ListInsert(&ctrlS->link, ctrlS, &ctrl->descHead);
   ctrlS->ctx = ctrl->ctx;
   ctrlS->parent = ctrl;
}

//
// Lth_ControlAttachTail
//
void Lth_ControlAttachTail(void *ctrl_, void *ctrlS_)
{
   Lth_Control *ctrl = ctrl_, *ctrlS = ctrlS_;
   Lth_ListInsertTail(&ctrlS->link, ctrlS, &ctrl->descHead, &ctrl->descTail);
   ctrlS->ctx = ctrl->ctx;
   ctrlS->parent = ctrl;
}

//
// Lth_ControlFont
//
Lth_Font *Lth_ControlFont(void *ctrl_)
{
   Lth_Control *ctrl = ctrl_;

   if(ctrl->font || (ctrl->vtable.getFont && ctrl->vtable.getFont(ctrl)))
      return ctrl->font;
   else if(ctrl->parent)
      return Lth_ControlFont(ctrl->parent);
   else
      return NULL;
}

// EOF
