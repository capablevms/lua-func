
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



extern int luaL_argerror(lua_State *, int, const char *);
extern lua_Integer luaL_checkinteger(lua_State *, int);
extern void lua_pushinteger(lua_State *, lua_Integer);
extern const char * lua_tolstring(lua_State *, int, size_t *);
extern int lua_type(lua_State *, int);
extern int lua_gettop(lua_State *);

extern int luaB_select (lua_State *L) {
  int n = lua_gettop(L);
  if (lua_type(L, 1) == 4 && *lua_tolstring(L, (1), ((void*)0)) == '#') {
    lua_pushinteger(L, n-1);
    return 1;
  }
  else {
    lua_Integer i = luaL_checkinteger(L, 1);
    if (i < 0) i = n + i;
    else if (i > n) i = n;
    ((void)((1 <= i) || luaL_argerror(L, (1), ("index out of range"))));
    return n - (int)i;
  }
}