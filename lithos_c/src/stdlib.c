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

#include <GDCC.h> // OH GOD

#include <string.h>
#include <stdlib.h>


// Extern Functions ----------------------------------------------------------|

//
// Lth_fpeekc
//
int Lth_fpeekc(FILE *fp)
{
   int ret = fgetc(fp);
   ungetc(ret, fp);
   return ret;
}

//
// Lth_strdup
//
// Duplicates a string, allocating a new one.
//
char *Lth_strdup(char const *s)
{
   size_t len = strlen(s);
   char *ret = malloc(len + 1);
   memcpy(ret, s, len);
   ret[len] = '\0';
   return ret;
}

//
// Lth_strdup_str
//
// Duplicates a string entity, allocating a new string.
//
char *Lth_strdup_str(__str s)
{
   size_t len = ACS_StrLen(s);
   char *ret = malloc(len + 1);
   ACS_StrArsCpyToGlobalCharRange((int)ret, __GDCC__Sta, 0, len, s);
   ret[len] = '\0';
   return ret;
}

//
// Lth_strentdup
//
// Duplicates a string into a new string entity.
//
__str Lth_strentdup(char const *s)
{
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
// Lth_strealoc
//
// Reallocates a string and replaces its contents.
//
char *Lth_strealoc(char *p, char const *s)
{
   size_t len = strlen(s);
   p = realloc(p, len + 1);
   memcpy(p, s, len);
   p[len] = '\0';
   return p;
}

//
// Lth_strealoc_str
//
char *Lth_strealoc_str(char *p, __str s)
{
   size_t len = ACS_StrLen(s);
   p = realloc(p, len + 1);
   ACS_StrArsCpyToGlobalCharRange((int)p, __GDCC__Sta, 0, len, s);
   p[len] = '\0';
   return p;
}

//
// Lth_strcontains
//
bool Lth_strcontains(char const *s, char ch)
{
   for(; *s; s++) if(*s == ch) return true;
   return false;
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

//
// Lth_Hash_char
//
size_t Lth_Hash_char(char const *s)
{
   if(s == NULL) return 0;

   size_t ret = 0;

   while(*s)
      ret = ret * 101 + (unsigned char)(*s++);

   return ret;
}

//
// Lth_Hash_str
//
size_t Lth_Hash_str(__str s)
{
   if(s == NULL) return 0;

   size_t ret = 0;
   size_t len = ACS_StrLen(s);

   for(size_t i = 0; i < len; i++)
      ret = ret * 101 + (unsigned char)(s[i]);

   return ret;
}

// EOF
