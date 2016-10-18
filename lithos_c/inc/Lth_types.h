//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Basic type handling.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_types_h
#define lithos3__Lth_types_h

#define Lth_Inherits(name) [[__anonymous]] name _super
#define Lth_Mixin(name) [[__anonymous]] name _##name


//----------------------------------------------------------------------------|
// Type Definitions                                                           |
//

typedef int Lth_HID;

//
// Lth_Signal
//
typedef enum Lth_Signal
{
#define Lth_X(sig, name, ret, ...) \
   Lth_##sig,
#include "Lth_callback.h"
   Lth_SIGMAX
} Lth_Signal;

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

#endif//lithos3__Lth_types_h
