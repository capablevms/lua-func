
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

void *luaM_shrinkvector_ (lua_State *L, void *block, int *size,
                          int final_n, int size_elem) {
  void *newblock;
  size_t oldsize = ((size_t)(((*size) * size_elem)));
  size_t newsize = ((size_t)((final_n * size_elem)));
  ((void)0);
  newblock = luaM_saferealloc_(L, block, oldsize, newsize);
  *size = final_n;
  return newblock;
}