
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
extern int luaL_error(lua_State *, const char *, ...);
extern int luaL_error(lua_State *, const char *, ...);
extern int luaL_error(lua_State *, const char *, ...);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern int lua_getfield(lua_State *, int, const char *);

extern int getfield (lua_State *L, const char *key, int d, int delta) {
  int isnum;
  int t = lua_getfield(L, -1, key);
  lua_Integer res = lua_tointegerx(L, -1, &isnum);
  if (!isnum) {
    if (t != 0)
      return luaL_error(L, "field '%s' is not an integer", key);
    else if (d < 0)
      return luaL_error(L, "field '%s' missing in date table", key);
    res = d;
  }
  else {

    if (!(res >= 0 ? (lua_Unsigned)res <= (lua_Unsigned)2147483647 + delta
                   : (lua_Integer)(-2147483647 -1) + delta <= res))
      return luaL_error(L, "field '%s' is out-of-bound", key);
    res -= delta;
  }
  lua_settop(L, -(1)-1);
  return (int)res;
}