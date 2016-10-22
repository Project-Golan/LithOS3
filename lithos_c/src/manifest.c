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

#include "Lth.h"

// Define fixed so it is not aliased (this breaks our code).
#define fixed
#include <stdfix.h>
#undef fixed

#include <stdbool.h>
#include <string.h>
#include <setjmp.h>

#define GenAlloc(name, type) \
   if(rsrc->vec##name.size) \
      rsrc->vec##name.data = calloc(rsrc->vec##name.size, sizeof(type)); \
   \
   size_t iter##name = 0

#define GenRsrcCase(name, var, i) \
   case Lth_ResourceType_##name: \
      rsrc->vec##name.data[iter##name] = iter->var; \
      rsrc->map.elem.data[i  ].keyhash = iter->keyhash; \
      rsrc->map.elem.data[i++].value   = &rsrc->vec##name.data[iter##name++]; \
      break

#define GenManifestValue(name, value, setexpr) \
   (Lth_Manifest){ \
      .type    = Lth_ResourceType_##name, \
      .keyhash = Lth_Hash_char(key), \
      .value   = (setexpr) \
   }

#define GenValueGetter(name, value, setexpr) \
   if(1) \
   { \
      if(repr->manifest.size + 1 > repr->manifest.bufsz) \
         repr->manifest.data = realloc(repr->manifest.data, \
            sizeof(Lth_Manifest) * (repr->manifest.bufsz += 32)); \
      \
      repr->manifest.data[repr->manifest.size++] = (Lth_Manifest){ \
         .type    = Lth_ResourceType_##name, \
         .keyhash = key, \
         .value   = (setexpr) \
      }; \
   } \
   else \
      ((void)0)

#define ManifestError(repr, str) \
   if(1) \
   { \
      fprintf(stderr, "%s (in %s): %s\n", __func__, (repr)->fname, str); \
      repr->err = true; \
      longjmp(ManifestJmpBuf, ManifestJmpBufToken); \
   } \
   else ((void)0)


// Type Definitions ----------------------------------------------------------|

//
// ManifestState
//
typedef struct ManifestState
{
   char            *block;
   char            *data;
   bool             err;
   char const      *fname;
   Lth_TokenStream *stream;
   Lth_Vector(Lth_Manifest) manifest;
} ManifestState;


// Static Objects ------------------------------------------------------------|

static jmp_buf ManifestJmpBuf;
static int const ManifestJmpBufToken = 30;


// Static Functions ----------------------------------------------------------|

//
// ManifestGetInteg
//
static void ManifestGetInteg(ManifestState *repr, size_t key, char const *str)
{
   // integer-constant
   char *end;
   int value = strtoi(str, &end, 0);

   if(*end != '\0')
      ManifestError(repr, "bad integral value");

   GenValueGetter(Integ, integ, value);
}

//
// ManifestGetFixed
//
static void ManifestGetFixed(ManifestState *repr, size_t key, char const *str)
{
   // fixed-constant
   char *end;
   _Accum value = strtofxk(str, &end);

   if(*end != '\0')
      ManifestError(repr, "bad fixed-point value");

   GenValueGetter(Fixed, fixed, value);
}

//
// ManifestGetStrng
//
static void ManifestGetStrng(ManifestState *repr, size_t key, char const *str)
{
   // string-constant
   GenValueGetter(Strng, strng, Lth_strdup(str));
}

//
// ManifestGetHeaderNameSequence
//
static void ManifestGetHeaderNameSequence(ManifestState *repr)
{
   // header-name-sequence:
   //    identifier
   //    header-name-sequence . identifier

   ACS_BeginPrint();

   do
   {
      Lth_Token const *tok = Lth_TokenStreamPeek(repr->stream);

      // identifier
      if(tok->type != Lth_TOK_Identi)
         ManifestError(repr, "expected identifier");

      Lth_PrintString(tok->str);

      Lth_TokenStreamBump(repr->stream);
   }
   Lth_pfor(Lth_TokenStreamDrop(repr->stream, Lth_TOK_Dot), ACS_PrintChar('.'));
}

//
// ManifestGetInitializer
//
static void ManifestGetInitializer(ManifestState *repr, size_t key)
{
   // initializer:
   //    integer-constant
   //    fixed-constant
   //    string-constant

   switch(Lth_TokenStreamPeek(repr->stream)->type)
   {
   case Lth_TOK_Number:
      __with(char const *str = Lth_TokenStreamBump(repr->stream)->str;)
         if(!Lth_strcontains(str, '.'))
            ManifestGetInteg(repr, key, str);
         else
            ManifestGetFixed(repr, key, str);
      break;
   case Lth_TOK_String:
      ManifestGetStrng(repr, key, Lth_TokenStreamBump(repr->stream)->str);
      break;
   case Lth_TOK_Identi:
      __with(char const *str = Lth_TokenStreamBump(repr->stream)->str;)
              if(strcmp(str, "true") == 0)  GenValueGetter(Integ, integ, 1);
         else if(strcmp(str, "false") == 0) GenValueGetter(Integ, integ, 0);
         else goto unexpect;
      break;
   unexpect:
   default:
      ManifestError(repr, "expected initializer");
      break;
   }
}

//
// ManifestGetDecl_Object
//
static void ManifestGetDecl_Object(ManifestState *repr)
{
   // object-name:
   //    identifier
   //    string-constant

   // object-decl-terminator:
   //    '\n'
   //    ;

   // object-declaration:
   //    object-name = initializer object-decl-terminator

   // identifier
   if(Lth_TokenStreamPeek(repr->stream)->type != Lth_TOK_String &&
      Lth_TokenStreamPeek(repr->stream)->type != Lth_TOK_Identi)
      ManifestError(repr, "exptected object-name");

   // Build the key name. Format is: "blockname.identifier"
   __with(char const *name = Lth_TokenStreamBump(repr->stream)->str;)
   {
      ACS_BeginPrint();

      Lth_PrintString(repr->block);
      ACS_PrintChar('.');
      Lth_PrintString(name);
   }

   size_t key = Lth_Hash_str(ACS_EndStrParam());

   repr->stream->skipeol = false;

   // =
   if(!Lth_TokenStreamDrop(repr->stream, Lth_TOK_Equals))
      ManifestError(repr, "expected '='");

   // initializer
   ManifestGetInitializer(repr, key);

   // object-decl-terminator
   if(!Lth_TokenStreamDrop(repr->stream, Lth_TOK_LnEnd) &&
      !Lth_TokenStreamDrop(repr->stream, Lth_TOK_Semico))
      ManifestError(repr, "expected newline or ';'");

   repr->stream->skipeol = true;
}

//
// ManifestGetDecl_Header
//
static void ManifestGetDecl_Header(ManifestState *repr)
{
   // header-declaration:
   //    [ header-name-sequence ]

   // [
   if(!Lth_TokenStreamDrop(repr->stream, Lth_TOK_BrackO))
      ManifestError(repr, "expected '['");

   // header-name-sequence
   ManifestGetHeaderNameSequence(repr);
   repr->block = Lth_strealoc_str(repr->block, ACS_EndStrParam());

   // ]
   if(!Lth_TokenStreamDrop(repr->stream, Lth_TOK_BrackC))
      ManifestError(repr, "expected ']'");
}

//
// ManifestGetDecl
//
Lth_ScriptCall static void ManifestGetDecl(ManifestState *repr)
{
   switch(Lth_TokenStreamPeek(repr->stream)->type)
   {
   case Lth_TOK_BrackO: ManifestGetDecl_Header(repr); break;
   default:             ManifestGetDecl_Object(repr); break;
   }
}

//
// ManifestClose
//
static void ManifestClose(ManifestState *repr)
{
   Lth_TokenStreamClose(repr->stream);
   free(repr->data);
   free(repr->block);
   free(repr->manifest.data);
}


// Extern Functions ----------------------------------------------------------|

//
// Lth_ResourceMapDestroy
//
void Lth_ResourceMapDestroy(Lth_ResourceMap *rsrc)
{
   if(rsrc == NULL) return;

   Lth_HashMapFree(&rsrc->map);

   if(rsrc->vecStrng.data)
      Lth_VectorForEach(char **, rsrc->vecStrng)
         free(*itr);

   free(rsrc->vecInteg.data);
   free(rsrc->vecFixed.data);
   free(rsrc->vecStrng.data);

   free(rsrc);
}

//
// Lth_ManifestLoad_extern
//
Lth_ScriptCall Lth_ResourceMap *Lth_ManifestLoad_extern(char const *fname)
{
   ManifestState repr = {};

   repr.fname  = fname;
   repr.data   = Lth_strdup_str(Lth_strlocal(Lth_strentdup(repr.fname)));
   repr.stream = Lth_TokenStreamOpen(repr.data, strlen(repr.data));
   repr.block  = Lth_strdup("Base");

   Lth_assert(repr.stream != NULL);

   if(strcmp(repr.data, repr.fname) == 0)
   {
      fprintf(stderr, "%s: No file named '%s'.", __func__, fname);
      ManifestClose(&repr);
      return NULL;
   }

   if(setjmp(ManifestJmpBuf) != ManifestJmpBufToken)
      for(;;)
         if(Lth_TokenStreamPeek(repr.stream)->type != Lth_TOK_EOF)
            ManifestGetDecl(&repr);
         else
            break;

   Lth_ResourceMap *rsrc = NULL;

   if(!repr.err)
      rsrc = Lth_ManifestLoad_static(repr.manifest.data);

   ManifestClose(&repr);

   return rsrc;
}

//
// Lth_ManifestLoad_static
//
Lth_ScriptCall Lth_ResourceMap *Lth_ManifestLoad_static(Lth_Manifest *manifest)
{
   Lth_ResourceMap *rsrc = calloc(1, sizeof(Lth_ResourceMap));
   Lth_assert(rsrc != NULL);

   size_t count = 0;

   // If keyhash is 0, it was a NULL string, thus a terminator for this list.

   // Get the size of each vector and the total size for the map.
   for(Lth_Manifest *iter = manifest; iter->keyhash; iter++, count++)
      switch(iter->type)
   {
   case Lth_ResourceType_Integ: rsrc->vecInteg.size++; break;
   case Lth_ResourceType_Fixed: rsrc->vecFixed.size++; break;
   case Lth_ResourceType_Strng: rsrc->vecStrng.size++; break;
   default: break;
   }

   // Allocate each data vector and make an iterator for it.
   GenAlloc(Integ, int);
   GenAlloc(Fixed, _Accum);
   GenAlloc(Strng, char *);

   // Allocate the hash map.
   Lth_HashMapAlloc(&rsrc->map, count);

   // Iterate over all of the data vectors, adding them to the map, and
   // adding data to them.
   __with(size_t i = 0;)
      for(Lth_Manifest *iter = manifest; iter->keyhash; iter++)
         switch(iter->type)
   {
      GenRsrcCase(Integ, integ, i);
      GenRsrcCase(Fixed, fixed, i);
      GenRsrcCase(Strng, strng, i);
   }

   // Build the map.
   Lth_HashMapBuild(&rsrc->map);
   return rsrc;
}

//
// Lth_ManifestNew_Integ
//
Lth_Manifest Lth_ManifestNew_Integ(char const *key, int value)
{
   return GenManifestValue(Integ, integ, value);
}

//
// Lth_ManifestNew_Fixed
//
Lth_Manifest Lth_ManifestNew_Fixed(char const *key, _Accum value)
{
   return GenManifestValue(Fixed, fixed, value);
}

//
// Lth_ManifestNew_Strng
//
Lth_Manifest Lth_ManifestNew_Strng(char const *key, char const *value)
{
   return GenManifestValue(Strng, strng, Lth_strdup(value));
}

// EOF
