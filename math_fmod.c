
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



extern void lua_pushnumber(lua_State *, lua_Number);
extern double fmod(double, double);
extern lua_Number luaL_checknumber(lua_State *, int);
extern lua_Number luaL_checknumber(lua_State *, int);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer lua_tointegerx(lua_State *, int, int *);
extern int lua_isinteger(lua_State *, int);
extern int lua_isinteger(lua_State *, int);

static int math_fmod (lua_State *L) {
  if (lua_isinteger(L, 1) && lua_isinteger(L, 2)) {
    lua_Integer d = lua_tointegerx(L,(2),((void*)0));
    if ((lua_Unsigned)d + 1u <= 1u) {
      ((void)((d != 0) || luaL_argerror(L, (2), ("zero"))));
      lua_pushinteger(L, 0);
    }
    else
      lua_pushinteger(L, lua_tointegerx(L,(1),((void*)0)) % d);
  }
  else
    lua_pushnumber(L, fmod(luaL_checknumber(L, 1),
                                     luaL_checknumber(L, 2)));
  return 1;
}