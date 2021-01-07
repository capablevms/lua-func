
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
extern void lua_pushinteger(lua_State *, lua_Integer);

static void pushnumint (lua_State *L, lua_Number d) {
  lua_Integer n;
  if (((d) >= (double)((-9223372036854775807LL -1LL)) && (d) < -(double)((-9223372036854775807LL -1LL)) && (*(&n) = (long long)(d), 1)))
    lua_pushinteger(L, n);
  else
    lua_pushnumber(L, d);
}