
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



extern void pushnumint(lua_State *, lua_Number);
extern double floor(double);
extern lua_Number luaL_checknumber(lua_State *, int);
extern void lua_settop(lua_State *, int);
extern int lua_isinteger(lua_State *, int);

extern int math_floor (lua_State *L) {
  if (lua_isinteger(L, 1))
    lua_settop(L, 1);
  else {
    lua_Number d = floor(luaL_checknumber(L, 1));
    pushnumint(L, d);
  }
  return 1;
}