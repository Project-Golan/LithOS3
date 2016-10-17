//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Miscallaneous library functions.
//
//-----------------------------------------------------------------------------

#include "Lth.h"

#include <string.h>
#include <stdlib.h>


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

//
// Lth_strdup
//
// Duplicates a string, allocating a new one.
//
char *Lth_strdup(char const *s)
{
   Lth_assert(s != NULL);
   size_t len = strlen(s);
   char *ret = calloc(len + 1, 1);
   Lth_assert(ret != NULL);
   memcpy(ret, s, len);
   return ret;
}

//
// Lth_PrintString
//
// Print a C string into the ACS print buffer.
//
void Lth_PrintString(char const *s)
{
   if(s == NULL) return;
   for(char const *p = s; *p;) ACS_PrintChar(*p++);
}

// EOF
