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
#include "Lth_font.h"


// Type Definitions ----------------------------------------------------------|

//
// Lth_Control
//
// Has members of Lth_Rect (read-write).
//
// internal data
//    link
//    descendants
//    cb
//
// read-only
//    parent: control's parent (NULL if none)
//
// read-write
//    userdata: opaque pointer for the user to use
//    font:     default font for drawing
//    ctx:      pointer to associated context
//
//
typedef struct Lth_Control
{
   Lth_CallbackSet cb;
   Lth_LinkList    link;
   Lth_LinkList   *descendants;

   struct Lth_Control *parent;

   void        *userdata;
   Lth_Font    *font;
   Lth_Context *ctx;

   Lth_Mixin(Lth_Rect);
} Lth_Control;


// Extern Functions ----------------------------------------------------------|

Lth_Font *Lth_ControlFont(void *ctrl_);
void Lth_ControlRun(void *ctrl_);
void Lth_ControlConnect(void *ctrl_, Lth_Signal signal, Lth_Callback_t cb);
void Lth_ControlDestroy(void *ctrl_);
void Lth_ControlAttach(void *ctrlsrc_, void *ctrldst_);

#endif//lithos3__Lth_control_h
