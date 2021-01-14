
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



extern void lua_pushinteger(lua_State *, lua_Integer);
extern int lua_gc(lua_State *, int, ...);
extern int pushmode(lua_State *, int);
extern int lua_gc(lua_State *, int, ...);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern int pushmode(lua_State *, int);
extern int lua_gc(lua_State *, int, ...);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern void lua_pushboolean(lua_State *, int);
extern int lua_gc(lua_State *, int, ...);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern int lua_gc(lua_State *, int, ...);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern void lua_pushboolean(lua_State *, int);
extern int lua_gc(lua_State *, int, ...);
extern lua_Integer luaL_optinteger(lua_State *, int, lua_Integer);
extern void lua_pushnumber(lua_State *, lua_Number);
extern int lua_gc(lua_State *, int, ...);
extern int lua_gc(lua_State *, int, ...);
extern int luaL_checkoption(lua_State *, int, const char *, const char *const *);

extern int luaB_collectgarbage (lua_State *L) {
  static const char *const opts[] = {"stop", "restart", "collect",
    "count", "step", "setpause", "setstepmul",
    "isrunning", "generational", "incremental", ((void*)0)};
  static const int optsnum[] = {0, 1, 2,
    3, 5, 6, 7,
    9, 10, 11};
  int o = optsnum[luaL_checkoption(L, 1, "collect", opts)];
  switch (o) {
    case 3: {
      int k = lua_gc(L, o);
      int b = lua_gc(L, 4);
      lua_pushnumber(L, (lua_Number)k + ((lua_Number)b/1024));
      return 1;
    }
    case 5: {
      int step = (int)luaL_optinteger(L, 2, 0);
      int res = lua_gc(L, o, step);
      lua_pushboolean(L, res);
      return 1;
    }
    case 6:
    case 7: {
      int p = (int)luaL_optinteger(L, 2, 0);
      int previous = lua_gc(L, o, p);
      lua_pushinteger(L, previous);
      return 1;
    }
    case 9: {
      int res = lua_gc(L, o);
      lua_pushboolean(L, res);
      return 1;
    }
    case 10: {
      int minormul = (int)luaL_optinteger(L, 2, 0);
      int majormul = (int)luaL_optinteger(L, 3, 0);
      return pushmode(L, lua_gc(L, o, minormul, majormul));
    }
    case 11: {
      int pause = (int)luaL_optinteger(L, 2, 0);
      int stepmul = (int)luaL_optinteger(L, 3, 0);
      int stepsize = (int)luaL_optinteger(L, 4, 0);
      return pushmode(L, lua_gc(L, o, pause, stepmul, stepsize));
    }
    default: {
      int res = lua_gc(L, o);
      lua_pushinteger(L, res);
      return 1;
    }
  }
}