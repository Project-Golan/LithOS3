//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Program entry point.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <ACS_ZDoom.h>
#include <stdlib.h>


// Static Functions ----------------------------------------------------------|

[[__call("ScriptS"), __script("Enter")]]
static void main()
{
   Lth_Context *ctx = Lth_ContextNew(320, 200, 0x5000, 0x1000);
   Lth_Window *window[2] = {
      Lth_WindowNew("test window", 50, 100, 30, 30),
      Lth_WindowNew("test window 2", 100, 100, -1, -1)
   };

   for(int i = 0; i < 2; i++)
      Lth_ContextMap(ctx, window[i]);

   ACS_Delay(1);

   for(;;)
   {
      Lth_ContextRun(ctx);
      ACS_Delay(1);
   }

   Lth_ContextDestroy(ctx);
}

// EOF
