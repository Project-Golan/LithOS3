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


// Extern Functions ----------------------------------------------------------|

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
// Lth_strdup_str
//
// Duplicates a string entity, allocating a new string.
//
char *Lth_strdup_str(__str s)
{
   Lth_assert(s != NULL);
   size_t len = ACS_StrLen(s);
   char *ret = calloc(len + 1, 1);
   Lth_assert(ret != NULL);
   for(size_t i = 0; i < len; i++) ret[i] = s[i];
   return ret;
}

//
// Lth_strentdup
//
// Duplicates a string into a new string entity.
//
__str Lth_strentdup(char const *s)
{
   Lth_assert(s != NULL);
   size_t len = strlen(s);
   ACS_BeginPrint();
   Lth_PrintString(s);
   return ACS_EndStrParam();
}

//
// Lth_strlocal
//
__str Lth_strlocal(__str s)
{
   ACS_BeginPrint();
   ACS_PrintLocalized(s);
   return ACS_EndStrParam();
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
