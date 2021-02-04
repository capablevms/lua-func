
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



extern void lua_upvaluejoin(lua_State *, int, int, int, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_iscfunction(lua_State *, int);
extern int luaL_argerror(lua_State *, int, const char *);
extern int lua_iscfunction(lua_State *, int);
extern void * checkupval(lua_State *, int, int, int *);
extern void * checkupval(lua_State *, int, int, int *);

extern int db_upvaluejoin (lua_State *L) {
  int n1, n2;
  checkupval(L, 1, 2, &n1);
  checkupval(L, 3, 4, &n2);
  ((void)((!lua_iscfunction(L, 1)) || luaL_argerror(L, (1), ("Lua function expected"))));
  ((void)((!lua_iscfunction(L, 3)) || luaL_argerror(L, (3), ("Lua function expected"))));
  lua_upvaluejoin(L, 1, n1, 3, n2);
  return 0;
}