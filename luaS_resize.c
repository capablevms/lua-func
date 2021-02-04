
#include <time.h>
#include <setjmp.h>
#include <ctype.h>

#include "lapi.h"
#include "lauxlib.h"
#include "lcode.h"
#include "lctype.h"
#include "ldebug.h"
#include "ldo.h"
#include "lfunc.h"
#include "lgc.h"
#include "llex.h"
#include "llimits.h"
#include "lmem.h"
#include "lobject.h"
#include "lopcodes.h"
#include "lopnames.h"
#include "lparser.h"
#include "lprefix.h"
#include "lstate.h"
#include "lstring.h"
#include "ltable.h"
#include "ltm.h"
#include "luaconf.h"
#include "lua.h"
#include "lualib.h"
#include "lundump.h"
#include "lvm.h"
#include "lzio.h"



extern void tablerehash(TString **, int, int);
extern void tablerehash(TString **, int, int);
extern long __builtin_expect(long, long);
extern void * luaM_realloc_(lua_State *, void *, size_t, size_t);
extern void tablerehash(TString **, int, int);

void luaS_resize (lua_State *L, int nsize) {
  stringtable *tb = &(L->l_G)->strt;
  int osize = tb->size;
  TString **newvect;
  if (nsize < osize)
    tablerehash(tb->hash, osize, nsize);
  newvect = (((TString* *)(luaM_realloc_(L, tb->hash, ((size_t)((osize))) * sizeof(TString*), ((size_t)((nsize))) * sizeof(TString*)))));
  if ((__builtin_expect(((newvect == ((void*)0)) != 0), 0))) {
    if (nsize < osize)
      tablerehash(tb->hash, nsize, osize);

  }
  else {
    tb->hash = newvect;
    tb->size = nsize;
    if (nsize > osize)
      tablerehash(newvect, osize, nsize);
  }
}