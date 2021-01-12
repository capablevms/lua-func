
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
extern void lua_pushvalue(lua_State *, int);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void luaL_checkany(lua_State *, int);

extern int ipairsaux (lua_State *);

static int luaB_ipairs (lua_State *L) {
  luaL_checkany(L, 1);
  lua_pushcclosure(L, (ipairsaux), 0);
  lua_pushvalue(L, 1);
  lua_pushinteger(L, 0);
  return 3;
}