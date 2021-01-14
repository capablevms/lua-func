
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



extern int luaL_error(lua_State *, const char *, ...);

extern size_t newbuffsize (luaL_Buffer *B, size_t sz) {
  size_t newsize = B->size * 2;
  if (((size_t)(~(size_t)0)) - sz < B->n)
    return luaL_error(B->L, "buffer too large");
  if (newsize < B->n + sz)
    newsize = B->n + sz;
  return newsize;
}