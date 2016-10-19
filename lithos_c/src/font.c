//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Font layout handling.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <stdlib.h>


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_FontNew
//
Lth_Font *Lth_FontNew(char const *name)
{
   Lth_Font *font = calloc(1, sizeof(Lth_Font));
   Lth_assert(font != NULL);

   font->name = Lth_strentdup(name);

   return font;
}

// EOF
