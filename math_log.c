
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
extern double log(double);
extern double log(double);
extern double log10(double);
extern double log2(double);
extern lua_Number luaL_checknumber(lua_State *, int);
extern double log(double);
extern int lua_type(lua_State *, int);
extern lua_Number luaL_checknumber(lua_State *, int);

static int math_log (lua_State *L) {
  lua_Number x = luaL_checknumber(L, 1);
  lua_Number res;
  if ((lua_type(L, (2)) <= 0))
    res = log(x);
  else {
    lua_Number base = luaL_checknumber(L, 2);

    if (base == 2.0)
      res = log2(x); else

    if (base == 10.0)
      res = log10(x);
    else
      res = log(x)/log(base);
  }
  lua_pushnumber(L, res);
  return 1;
}