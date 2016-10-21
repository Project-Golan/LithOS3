//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Resource manifests.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_manifest_h
#define lithos3__Lth_manifest_h

#include "Lth_hashmap.h"
#include "Lth_types.h"

#define Lth_ManifestNew(...) \
   ((Lth_Manifest[]){ \
      __VA_ARGS__, \
      Lth_Resource(NULL, 0) \
   })

#define Lth_Resource(name, val) \
   _Generic((val)+0, \
      int:          Lth_ManifestNew_Integ, \
      _Accum:       Lth_ManifestNew_Fixed, \
      char const *: Lth_ManifestNew_Strng \
   )((name), (val))


// Type Definitions ----------------------------------------------------------|

//
// Lth_ResourceType
//
typedef enum Lth_ResourceType
{
   Lth_ResourceType_Integ,
   Lth_ResourceType_Fixed,
   Lth_ResourceType_Strng,
   Lth_ResourceType_Max
} Lth_ResourceType;

//
// Lth_Manifest
//
typedef struct Lth_Manifest
{
   int type;
   size_t keyhash;
   union
   {
      int    integ;
      _Accum fixed;
      char  *strng;
   };
} Lth_Manifest;

//
// Lth_ResourceMap
//
typedef struct Lth_ResourceMap
{
   Lth_Vector(int)    vecInteg;
   Lth_Vector(_Accum) vecFixed;
   Lth_Vector(char *) vecStrng;
   Lth_HashMap map;
} Lth_ResourceMap;


// Extern Functions ----------------------------------------------------------|

void Lth_ResourceMapDestroy(Lth_ResourceMap *rsrc);

Lth_ScriptCall Lth_ResourceMap *Lth_ManifestLoad_extern(char const *fname);
Lth_ScriptCall Lth_ResourceMap *Lth_ManifestLoad_static(Lth_Manifest *manifest);

Lth_Manifest Lth_ManifestNew_Integ(char const *key, int         value);
Lth_Manifest Lth_ManifestNew_Fixed(char const *key, _Accum      value);
Lth_Manifest Lth_ManifestNew_Strng(char const *key, char const *value);

#endif//lithos3__Lth_manifest_h
