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

[[__optional_args(2)]]
Lth_Window *Lth_WindowNew(char const *title, int x, int y, int w, int h);
void Lth_WindowSetTitle(Lth_Window *ctrl, char const *title);

#endif//lithos3__Lth_window_h
