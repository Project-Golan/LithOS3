//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Button control.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_button_h
#define lithos3__Lth_button_h


// Type Definitions ----------------------------------------------------------|

//
// Lth_ButtonState
//
enum Lth_ButtonState
{
   Lth_BS_Normal,
   Lth_BS_Hover,
   Lth_BS_Depressed,
   Lth_BS_Clicked,
   Lth_BS_Max
};

//
// Lth_Button
//
typedef struct Lth_Button
{
   Lth_Inherits(Lth_Control);
   char *label;
   int state;
} Lth_Button;


// Extern Functions ----------------------------------------------------------|

Lth_Button *Lth_ButtonNew(char const *label);
void Lth_ButtonSetLabel(Lth_Button *ctrl, char const *label);

#endif//lithos3__Lth_button_h
