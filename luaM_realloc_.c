
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



extern void * tryagain(lua_State *, void *, size_t, size_t);
extern long __builtin_expect(long, long);

void *luaM_realloc_ (lua_State *L, void *block, size_t osize, size_t nsize) {
  void *newblock;
  global_State *g = (L->l_G);
  ((void)0);
  newblock = ((*g->frealloc)(g->ud, block, osize, nsize));
  if ((__builtin_expect(((newblock == ((void*)0) && nsize > 0) != 0), 0))) {
    if (nsize > osize)
      newblock = tryagain(L, block, osize, nsize);
    if (newblock == ((void*)0))
      return ((void*)0);
  }
  ((void)0);
  g->GCdebt = (g->GCdebt + nsize) - osize;
  return newblock;
}