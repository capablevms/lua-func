
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



extern void lua_pushnil(lua_State *);
extern int lua_setiuservalue(lua_State *, int, int);
extern void lua_settop(lua_State *, int);
extern void luaL_checkany(lua_State *, int);
extern void luaL_checktype(lua_State *, int, int);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);

extern int db_setuservalue (lua_State *L) {
  int n = (int)luaL_optinteger(L, 3, 1);
  luaL_checktype(L, 1, 7);
  luaL_checkany(L, 2);
  lua_settop(L, 2);
  if (!lua_setiuservalue(L, 1, n))
    lua_pushnil(L);
  return 1;
}