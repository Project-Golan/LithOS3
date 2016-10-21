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

#ifndef lithos3__Lth_stdlib_h
#define lithos3__Lth_stdlib_h

#include <stdio.h>
#include <stdbool.h>

#define Lth_isidenti(ch) \
   (isalpha(ch) || isdigit(ch) || ch == '_' || ch == '$' || ch == '\'' || \
      ch >= 0x80)

// Post-for. Sort of.
#define Lth_pfor(cond, expr) while((cond) && ((expr), true))


// Extern Functions ----------------------------------------------------------|

// file
int Lth_fpeekc(FILE *fp);

// str
char *Lth_strdup(char const *s);
char *Lth_strdup_str(__str s);
__str Lth_strentdup(char const *s);
__str Lth_strlocal(__str s);
char *Lth_strealoc(char *p, char const *s);
char *Lth_strealoc_str(char *p, __str s);
bool  Lth_strcontains(char const *s, char ch);

// Print
void Lth_PrintString(char const *s);

// Hash
size_t Lth_Hash_char(char const *s);
size_t Lth_Hash_str(char __str_ars const *s);

#endif//lithos3__Lth_stdlib_h
