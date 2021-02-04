
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

static const char *const CLIBS = "_CLIBS";

extern int lua_setmetatable(lua_State *, int);
extern void lua_setfield(lua_State *, int, const char *);
extern void lua_pushcclosure(lua_State *, lua_CFunction, int);
extern void lua_createtable(lua_State *, int, int);
extern int luaL_getsubtable(lua_State *, int, const char *);
extern int gctm (lua_State *L);

extern void createclibstable (lua_State *L) {
  luaL_getsubtable(L, (-1000000 - 1000), CLIBS);
  lua_createtable(L, 0, 1);
  lua_pushcclosure(L, (gctm), 0);
  lua_setfield(L, -2, "__gc");
  lua_setmetatable(L, -2);
}