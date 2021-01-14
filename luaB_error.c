
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



extern int lua_error(lua_State *);
extern void lua_concat(lua_State *, int);
extern void lua_pushvalue(lua_State *, int);
extern void luaL_where(lua_State *, int);
extern int lua_type(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);

extern int luaB_error (lua_State *L) {
  int level = (int)luaL_optinteger(L, 2, 1);
  lua_settop(L, 1);
  if (lua_type(L, 1) == 4 && level > 0) {
    luaL_where(L, level);
    lua_pushvalue(L, 1);
    lua_concat(L, 2);
  }
  return lua_error(L);
}