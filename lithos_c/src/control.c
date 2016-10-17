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
// # of rewrites because of DavidPH: 1
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
void Lth_ControlRun(Lth_Context *ctx, void *control_)
{
   Lth_assert(ctx != NULL);
   Lth_assert(control_ != NULL);

   Lth_Control *control = control_;

   Lth_Call(control->cb.update, ctx, control);
   Lth_Call(control->cb.draw,   ctx, control);
}

//
// Lth_ControlConnect
//
void Lth_ControlConnect(void *control_, Lth_Signal signal, Lth_Callback_t cb)
{
   Lth_assert(control_ != NULL);
   Lth_assert(signal < Lth_SIGMAX && signal >= 0);
   Lth_assert(cb != NULL);

   Lth_Control *control = control_;

   switch(signal)
   {
#define vec(name) control->cb.name
#define Lth_X(sig, name, ret, ...) \
   case Lth_##sig: \
      vec(name).data = \
         realloc(vec(name).data, \
            sizeof(Lth_##sig##_t) * (vec(name).size + 1)); \
      vec(name).data[vec(name).size++] = (Lth_##sig##_t)cb; \
      break;
#include "Lth_callback.h"
#undef vec
   }
}

//
// Lth_ControlDestroy
//
void Lth_ControlDestroy(void *control_)
{
   Lth_assert(control_ != NULL);

   Lth_Control *control = control_;

   for(Lth_LinkList *list = control->descendants; list;)
   {
      Lth_LinkList *next = list->next;
      Lth_Control *owner = list->owner;

      Lth_ControlDestroy(owner);

      list = next;
   }

   Lth_CallReverse(control->cb.destroy, control);
   Lth_LinkListRemove(&control->desclink);

   free(control);
}


// EOF
