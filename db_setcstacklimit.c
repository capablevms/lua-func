
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
extern int lua_setcstacklimit(lua_State *, unsigned int);
extern lua_Integer luaL_checkinteger(lua_State *, int);

extern int db_setcstacklimit (lua_State *L) {
  int limit = (int)luaL_checkinteger(L, 1);
  int res = lua_setcstacklimit(L, limit);
  lua_pushinteger(L, res);
  return 1;
}