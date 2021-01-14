
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



extern int lua_setmetatable(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int luaL_getmetafield(lua_State *, int, const char *);
extern int luaL_typeerror(lua_State *, int, const char *);
extern void luaL_checktype(lua_State *, int, int);
extern int lua_type(lua_State *, int);

extern int luaB_setmetatable (lua_State *L) {
  int t = lua_type(L, 2);
  luaL_checktype(L, 1, 5);
  ((void)((t == 0 || t == 5) || luaL_typeerror(L, (2), ("nil or table"))));
  if (luaL_getmetafield(L, 1, "__metatable") != 0)
    return luaL_error(L, "cannot change a protected metatable");
  lua_settop(L, 2);
  lua_setmetatable(L, 1);
  return 1;
}