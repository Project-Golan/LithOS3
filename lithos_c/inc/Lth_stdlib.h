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


// Extern Functions ----------------------------------------------------------|

// str
char *Lth_strdup(char const *s);
char *Lth_strdup_str(__str s);
__str Lth_strentdup(char const *s);
__str Lth_strlocal(__str s);

// Print
void Lth_PrintString(char const *s);

#endif//lithos3__Lth_stdlib_h
