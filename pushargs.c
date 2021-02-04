
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
extern void lua_rotate(lua_State *, int, int);
extern int lua_rawgeti(lua_State *, int, lua_Integer);
extern void luaL_checkstack(lua_State *, int, const char *);
extern lua_Integer luaL_len(lua_State *, int);
extern int luaL_error(lua_State *, const char *, ...);
extern int lua_getglobal(lua_State *, const char *);

extern int pushargs (lua_State *L) {
  int i, n;
  if (lua_getglobal(L, "arg") != 5)
    luaL_error(L, "'arg' is not a table");
  n = (int)luaL_len(L, -1);
  luaL_checkstack(L, n + 3, "too many arguments to script");
  for (i = 1; i <= n; i++)
    lua_rawgeti(L, -i, i);
  (lua_rotate(L, (-i), -1), lua_settop(L, -(1)-1));
  return n;
}