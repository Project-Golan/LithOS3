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

#include "Lth_linklist.h"
#include "Lth_types.h"
#include "Lth_callback.h"


//----------------------------------------------------------------------------|
// Type Definitions                                                           |
//

//
// Lth_Rect
//
typedef struct Lth_Rect
{
   int x, y;
   int w, h;
} Lth_Rect;

//
// Lth_HIDRange
//
// read-only
//    base: beginning of HID range (must be more than end)
//    end:  end of HID range (must be less than base)
//
// read-write
//    cur: current HID
//
typedef struct Lth_HIDRange
{
   Lth_HID base;
   Lth_HID end;
   Lth_HID cur;
} Lth_HIDRange;

//
// Lth_Context
//
// internal data
//    clip
//    map
//
// read-only
//    w: width of screen
//    h: height of screen
//
// read-write
//    hid: HUD ID range
//
typedef struct Lth_Context
{
   struct { Lth_Rect rects[16]; int num; } clip;
   Lth_LinkList *map;

   int w, h;

   Lth_HIDRange hid;
} Lth_Context;

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
   Lth_LinkList  desclink;
   Lth_LinkList *descendants;
   Lth_CallbackSet cb;

   struct Lth_Control *parent;

   void *userdata;

   Lth_Mixin(Lth_Rect);
} Lth_Control;

//
// Lth_Window
//
// Inherits Lth_Control (read-write).
//
// read-only
//    title: title of window (see also: Lth_WindowSetTitle)
//
typedef struct Lth_Window
{
   Lth_Inherits(Lth_Control);
   char *title;
} Lth_Window;


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

Lth_Context *Lth_ContextNew(int w, int h, Lth_HID hidBase, Lth_HID hidEnd);
void Lth_ContextMap(Lth_Context *ctx, Lth_Window *window);
void Lth_ContextDestroy(Lth_Context *ctx);
void Lth_ContextRun(Lth_Context *ctx);
void Lth_ContextClipPush(Lth_Context *ctx, int x, int y, int w, int h);
void Lth_ContextClipPop(Lth_Context *ctx);

void Lth_DrawRect(Lth_Context *ctx, int x, int y, int w, int h, __fixed alpha);

void Lth_ControlRun(Lth_Context *ctx, void *control_);
void Lth_ControlConnect(void *control_, Lth_Signal signal, Lth_Callback_t cb);
void Lth_ControlDestroy(void *control_);

Lth_Window *Lth_WindowNew(char const *title, int w, int h, int x, int y);
void Lth_WindowSetTitle(Lth_Window *control, char const *title);

#endif//lithos3__Lth_control_h
