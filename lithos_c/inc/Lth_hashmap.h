//-----------------------------------------------------------------------------
//
// Copyright © 2016 Team Doominati & Project Golan
//
// This file contains material copyrighted by Team Doominati, licensed under
// the same GPLv2 license as Project Golan's code.
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Fixed-size (runtime) hash map.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_hashmap_h
#define lithos3__Lth_hashmap_h

#include "Lth_assert.h"
#include "Lth_stdlib.h"

#include <stdlib.h>


// Type Definitions ----------------------------------------------------------|

//
// Lth_HashMapElem
//
typedef struct Lth_HashMapElem
{
   size_t keyhash;
   void  *value;
   struct Lth_HashMapElem *next;
} Lth_HashMapElem;

//
// Lth_HashMap
//
// internal data
//    table
//
// read-only
//    elements
//
typedef struct Lth_HashMap
{
   Lth_HashMapElem           **table;
   Lth_Vector(Lth_HashMapElem) elem;
} Lth_HashMap;


// Static Functions ----------------------------------------------------------|

//
// Lth_HashMapFree
//
static inline void Lth_HashMapFree(Lth_HashMap *map)
{
   if(map == NULL) return;

   free(map->elem.data);

   map->table     = NULL;
   map->elem.data = NULL;
   map->elem.size = 0;
}

//
// Lth_HashMapAlloc
//
static inline void Lth_HashMapAlloc(Lth_HashMap *map, size_t count)
{
   Lth_assert(map != NULL);

   if(map->elem.data)
      Lth_HashMapFree(map);

   size_t size =
      sizeof(Lth_HashMapElem) * count + sizeof(Lth_HashMapElem *) * count;

   map->elem.size = count;
   map->elem.data = calloc(1, size);
}

//
// Lth_HashMapBuild
//
static inline void Lth_HashMapBuild(Lth_HashMap *map)
{
   Lth_assert(map != NULL);

   map->table = (Lth_HashMapElem **)(map->elem.data + map->elem.size);

   for(Lth_HashMapElem **elem = map->table + map->elem.size;
      elem != map->table;)
      *--elem = NULL;

   for(size_t i = 0; i < map->elem.size; i++)
   {
      Lth_HashMapElem *elem = &map->elem.data[i];
      size_t hash = elem->keyhash % map->elem.size;
      elem->next = map->table[hash];
      map->table[hash] = elem;
   }
}

//
// Lth_HashMapFindItr
//
static inline Lth_HashMapElem *Lth_HashFindItr(Lth_HashMap *map, size_t hash)
{
   if(map->table == NULL) return NULL;

   for(Lth_HashMapElem *elem = map->table[hash % map->elem.size]; elem;
      elem = elem->next)
   {
      if(elem->keyhash == hash)
         return elem;
   }

   return NULL;
}

//
// Lth_HashMapFind
//
static inline void *Lth_HashMapFind(Lth_HashMap *map, char const *key)
{
   Lth_HashMapElem *elem = Lth_HashFindItr(map, Lth_Hash_char(key));
   if(elem == NULL) return NULL;
   return elem->value;
}

#endif//lithos3__Lth_hashmap_h
