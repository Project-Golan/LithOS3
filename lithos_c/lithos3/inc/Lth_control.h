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

#define Lth_ControlFontRunPlain(ctrl, ...) \
   Lth_FontRunPlain((ctrl)->ctx, Lth_ControlFont((ctrl)), __VA_ARGS__)

#define Lth_ControlInit(type) \
   type *ctrl = calloc(1, sizeof(type)); \
   Lth_assert(ctrl != NULL); \
   \
   ctrl->ctx = ctx

#define Lth_VirtControl (void *)ctrl


// Type Definitions ----------------------------------------------------------|

//
// Lth_Control
//
// Has members of Lth_Rect (read-write).
//
// internal data
//    cb
//    descHead
//    descTail
//    link
//
// read-only
//    vtable: virtual functions for overrides
//    parent: control's parent (NULL if none)
//
// read-write
//    ctx:      pointer to associated context
//    font:     default font for drawing
//    userdata: opaque pointer for the user to use
//
//
typedef struct Lth_Control
{
   Lth_CallbackSet cb;

   struct
   {
      Lth_Font *(*getFont)(struct Lth_Control *);
   } vtable;

   Lth_LinkList *descHead, *descTail, link;

   struct Lth_Control *parent;

   Lth_Context *ctx;
   Lth_Font    *font;
   void        *userdata;

   Lth_Mixin(Lth_Rect);
} Lth_Control;


// Extern Functions ----------------------------------------------------------|

void Lth_ControlRun(void *ctrl_);
void Lth_ControlConnect(void *ctrl_, Lth_Signal signal, Lth_Callback_t cb);
void Lth_ControlDestroy(void *ctrl_);
void Lth_ControlAttach(void *ctrl_, void *ctrlS_);
void Lth_ControlAttachTail(void *ctrl_, void *ctrlS_);

Lth_Font *Lth_ControlFont(void *ctrl_);

#endif//lithos3__Lth_control_h
