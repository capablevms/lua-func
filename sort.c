
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

typedef unsigned int IdxT;

extern void auxsort(lua_State *, IdxT, IdxT, unsigned int);
extern void lua_settop(lua_State *, int);
extern void luaL_checktype(lua_State *, int, int);
extern int lua_type(lua_State *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_len(lua_State *, int);
extern void checktab(lua_State *, int, int);

static int sort (lua_State *L) {
  lua_Integer n = (checktab(L, 1, ((1 | 2)) | 4), luaL_len(L, 1));
  if (n > 1) {
    ((void)((n < 2147483647) || luaL_argerror(L, (1), ("array too big"))));
    if (!(lua_type(L, (2)) <= 0))
      luaL_checktype(L, 2, 6);
    lua_settop(L, 2);
    auxsort(L, 1, (IdxT)n, 0);
  }
  return 0;
}