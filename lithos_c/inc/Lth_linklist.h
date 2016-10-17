//-----------------------------------------------------------------------------
//
// Copyright © 2016 Project Golan
//
// See "LICENSE" for more information.
//
//-----------------------------------------------------------------------------
//
// Doubly linked list structure.
//
//-----------------------------------------------------------------------------

#ifndef lithos3__Lth_linklist_h
#define lithos3__Lth_linklist_h

#include "Lth_assert.h"

#include <stddef.h>

#define Lth_ListForEach(tmpv, lst) \
   for(Lth_LinkList *list = (lst); list; list = list->next) \
      __with(tmpv = list->owner;)
#define Lth_ListFor(tmpv, lst) \
   for(Lth_LinkList *list = (lst); list;) \
      __with(Lth_LinkList *next = list->next, **prev = list->prev; \
         tmpv = list->owner;)


//----------------------------------------------------------------------------|
// Type Definitions                                                           |
//

//
// Lth_LinkList
//
typedef struct Lth_LinkList
{
   struct Lth_LinkList *next, **prev;
   void *owner;
} Lth_LinkList;


//----------------------------------------------------------------------------|
// Static Functions                                                           |
//

//
// Lth_LinkListInsert
//
static inline void Lth_LinkListInsert(Lth_LinkList *list, void *object,
   Lth_LinkList **head)
{
   Lth_assert(list != NULL);
   Lth_assert(head != NULL);
   Lth_assert(*head != NULL);

   Lth_LinkList *next = *head;

   if((list->next = next))
      next->prev = &list->next;

   list->prev = head;
   *head = list;

   list->owner = object;
}

//
// Lth_LinkListRemove
//
static inline void Lth_LinkListRemove(Lth_LinkList *list)
{
   Lth_assert(list != NULL);

   Lth_LinkList *next = list->next, **prev = list->prev;

   if(prev && (*prev = next))
      next->prev = prev;

   list->next = NULL;
   list->prev = NULL;
}

#endif//lithos3__Lth_linklist_h
