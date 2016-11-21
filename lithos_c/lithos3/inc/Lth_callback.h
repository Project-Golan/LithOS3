//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Callbacks.
//
// If an x-macro is defined, this file will give info about callback types.
//    Format: (sig, name, ret, arguments...)
//    sig       - Signal name.
//    name      - Identifier.
//    ret       - Return value of callback.
//    arguments - Arguments of callback (vararg).
//
//-----------------------------------------------------------------------------

#if defined(Lth_X)

Lth_X(SigDestroy, destroy,  void, struct Lth_Control *)
Lth_X(SigClicked, click,    void, struct Lth_Control *)
Lth_X(SigDraw   , draw,     void, struct Lth_Control *)
Lth_X(SigDrawPst, drawpost, void, struct Lth_Control *)
Lth_X(SigUpdate , update,   void, struct Lth_Control *)

#undef Lth_X

#elif !defined(lithos3__Lth_callback_h)
#define lithos3__Lth_callback_h

#define Lth_Callback(name) ((Lth_Callback_t)(name))

#define Lth_Call(name, ...) \
   do \
   { \
      if((name).data != NULL) \
         for(size_t cbIter = 0; cbIter < (name).size; cbIter++) \
            (name).data[cbIter](__VA_ARGS__); \
   } \
   while(0)

#define Lth_CallReverse(name, ...) \
   do \
   { \
      if((name).data != NULL) \
         for(size_t cbIter = (name).size; cbIter > 0; cbIter--) \
            (name).data[cbIter - 1](__VA_ARGS__); \
   } \
   while(0)


// Type Definitions ----------------------------------------------------------|

struct Lth_Control;

typedef void (*Lth_Callback_t)(void);

#define Lth_X(sig, name, ret, ...) \
   typedef ret (*Lth_##sig##_t)(__VA_ARGS__);
#include "Lth_callback.h"

//
// Lth_CallbackSet
//
typedef struct Lth_CallbackSet
{
#define Lth_X(sig, name, ret, ...) \
   Lth_Vector(Lth_##sig##_t) name;
#include "Lth_callback.h"
} Lth_CallbackSet;

#endif//lithos3__Lth_callback_h
