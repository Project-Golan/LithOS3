//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Controls.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_control_h
#define lithos3__Lth_control_h

#include "Lth_callback.h"
#include "Lth_linklist.h"
#include "Lth_types.h"
#include "Lth_context.h"


//----------------------------------------------------------------------------|
// Type Definitions                                                           |
//

//
// Lth_Control
//
// Has members of Lth_Rect (read-write).
//
// internal data
//    desclink
//    descendants
//    cb
//
// read-only
//    parent: control's parent (NULL if none)
//
// read-write
//    userdata: opaque pointer to associate with this control
//
//
typedef struct Lth_Control
{
   Lth_CallbackSet cb;
   Lth_LinkList  desclink;
   Lth_LinkList *descendants;

   struct Lth_Control *parent;
   int lx, ly;

   void *userdata;

   Lth_Mixin(Lth_Rect);
} Lth_Control;

//
// Lth_LayoutControl
//
// read-only
//    lx:     layout x
//    ly:     layout y
//
typedef struct Lth_LayoutControl
{
   Lth_Inherits(Lth_Control);
   int lx, ly;
} Lth_LayoutControl;


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

void Lth_ControlRun(Lth_Context *ctx, void *ctrl_);
void Lth_ControlConnect(void *ctrl_, Lth_Signal signal, Lth_Callback_t cb);
void Lth_ControlDestroy(void *ctrl_);

#endif//lithos3__Lth_control_h
