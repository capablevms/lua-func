
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



extern void * luaM_saferealloc_(lua_State *, void *, size_t, size_t);
extern void luaG_runerror(lua_State *, const char *, ...);
extern long __builtin_expect(long, long);

void *luaM_growaux_ (lua_State *L, void *block, int nelems, int *psize,
                     int size_elems, int limit, const char *what) {
  void *newblock;
  int size = *psize;
  if (nelems + 1 <= size)
    return block;
  if (size >= limit / 2) {
    if ((__builtin_expect(((size >= limit) != 0), 0)))
      luaG_runerror(L, "too many %s (limit is %d)", what, limit);
    size = limit;
  }
  else {
    size *= 2;
    if (size < 4)
      size = 4;
  }
  ((void)0);

  newblock = luaM_saferealloc_(L, block, ((size_t)((*psize))) * size_elems,
                                         ((size_t)((size))) * size_elems);
  *psize = size;
  return newblock;
}