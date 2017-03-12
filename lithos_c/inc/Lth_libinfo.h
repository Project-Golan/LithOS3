//-----------------------------------------------------------------------------
//
// Copyright © 2017 Project Golan
//
// See "LICENSE.lithos3" for more information.
//
//-----------------------------------------------------------------------------
//
// Library setup.
//
//-----------------------------------------------------------------------------

#if LITHOS3_NO_STDLIB
# define LITHOS3_NO_HASHMAP 1
# define LITHOS3_NO_TOKEN 1
# define LITHOS3_NO_TOKENSTREAM 1
# define LITHOS3_NO_MANIFEST 1
#endif

#if LITHOS3_NO_HASHMAP
# define LITHOS3_NO_MANIFEST 1
#endif

#if LITHOS3_NO_TOKEN
# define LITHOS3_NO_TOKENSTREAM 1
#endif

#if LITHOS3_NO_TOKENSTREAM
# define LITHOS3_NO_MANIFEST 1
#endif

// EOF
