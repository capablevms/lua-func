
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



extern void lua_pushboolean(lua_State *, int);
extern int lua_getiuservalue(lua_State *, int, int);
extern void lua_pushnil(lua_State *);
extern int lua_type(lua_State *, int);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);

static int db_getuservalue (lua_State *L) {
  int n = (int)luaL_optinteger(L, 2, 1);
  if (lua_type(L, 1) != 7)
    lua_pushnil(L);
  else if (lua_getiuservalue(L, 1, n) != (-1)) {
    lua_pushboolean(L, 1);
    return 2;
  }
  return 1;
}