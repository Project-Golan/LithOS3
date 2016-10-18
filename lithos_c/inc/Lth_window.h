//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Window control.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_window_h
#define lithos3__Lth_window_h

#include "Lth_control.h"


// Type Definitions ----------------------------------------------------------|

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


// Extern Functions ----------------------------------------------------------|

Lth_Window *Lth_WindowNew(char const *title, int w, int h, int x, int y);
void Lth_WindowSetTitle(Lth_Window *ctrl, char const *title);

#endif//lithos3__Lth_window_h
