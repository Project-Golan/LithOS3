//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Window management.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_winman_h
#define lithos3__Lth_winman_h


// Type Definitions ----------------------------------------------------------|

//
// Lth_WindowManager
//
// Inherits Lth_Control (read-write)
//
// internal data
//    lastmap
//
// read-write
//    mapspace: space between newly mapped windows that are auto-positioned
//
typedef struct Lth_WindowManager
{
   Lth_Inherits(Lth_Control);

   Lth_IVec2 lastmap;

   Lth_IVec2 mapspace;
} Lth_WindowManager;


// Extern Functions ----------------------------------------------------------|

Lth_WindowManager *Lth_WMNew(Lth_Context *ctx);
void Lth_WMMap(Lth_WindowManager *wm, Lth_Window *window);

#endif//lithos3__Lth_winman_h
