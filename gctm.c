
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



extern void lua_settop(lua_State *, int);
extern void lsys_unloadlib(void *);
extern void * lua_touserdata(lua_State *, int);
extern int lua_rawgeti(lua_State *, int, lua_Integer);
extern lua_Integer luaL_len(lua_State *, int);

static int gctm (lua_State *L) {
  lua_Integer n = luaL_len(L, 1);
  for (; n >= 1; n--) {
    lua_rawgeti(L, 1, n);
    lsys_unloadlib(lua_touserdata(L, -1));
    lua_settop(L, -(1)-1);
  }
  return 0;
}