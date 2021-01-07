
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



extern int luaB_error(lua_State *);
extern void lua_settop(lua_State *, int);
extern const char * lua_pushstring(lua_State *, const char *);
extern void lua_settop(lua_State *, int);
extern void lua_rotate(lua_State *, int, int);
extern void luaL_checkany(lua_State *, int);
extern int lua_gettop(lua_State *);
extern int lua_toboolean(lua_State *, int);

static int luaB_assert (lua_State *L) {
  if (lua_toboolean(L, 1))
    return lua_gettop(L);
  else {
    luaL_checkany(L, 1);
    (lua_rotate(L, (1), -1), lua_settop(L, -(1)-1));
    lua_pushstring(L, "" "assertion failed!");
    lua_settop(L, 1);
    return luaB_error(L);
  }
}